#pragma once

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <random>
#include <string>
#include <tofupilot/tofupilot.hpp>
#include <gtest/gtest.h>

namespace test {

// Marks every name this run creates as belonging to this CI run. The suites
// share one org, so clients/e2e-cleanup.py deletes by tag rather than by age:
// untagged entities are never touched, which puts a concurrent job's data and
// anything a human seeded out of reach by construction.
inline const std::string& tag() {
    static const std::string value = [] {
        const char* env = std::getenv("E2E_TAG");
        if (env && *env) return std::string(env);
        // Local runs need a tag of their own: with a counter, a fixed tag would
        // make two runs in a row produce exactly the same names. Ten characters,
        // like CI's, so a fragment costs the same either way.
        std::mt19937 rng(std::random_device{}());
        static const char hex[] = "0123456789abcdef";
        std::string local = "e2el";
        for (int i = 0; i < 6; ++i) local += hex[rng() % 16];
        return local;
    }();
    return value;
}

// THIS SUITE RUNS ONE PROCESS PER TEST — KEEP IT THAT WAY
// -------------------------------------------------------
// tests/CMakeLists.txt uses gtest_discover_tests(), so ctest registers each
// test case as a ctest test of its own and relaunches this binary once per
// test with a --gtest_filter. That is deliberate, and costs ~155 s of the
// C++ job's 270 s of test time (190 tests at ~0.6 s each is ~114 s; the rest
// is process startup). Do not collapse it into a single add_test() to buy
// that time back — three of the four properties below have no equivalent
// inside one process, and the first one matters far more in C++ than in the
// python, Rust and C# suites, which really do run single-process:
//
//   * Crash isolation. A segfault or abort() cannot be caught in C++, it
//     ends the process. One process per test loses that one test; a single
//     process would lose the RESULTS of every test after it — you would not
//     even learn whether they passed.
//   * Per-test timeout. ctest can kill one hung test. In a single process a
//     hang burns the whole job's clock.
//   * No global-state leakage between tests: each starts from a fresh
//     process, including the client() and procedure_id() singletons below.
//   * ctest -j stays available (unused today).
//
// A name fragment no other run — and no other name in this run — produces.
//
// The "c" marks the C++ suite; python, Rust and C# use "p", "r" and "s". See
// clients/python-speakeasy/tests/e2e_tag.py for why uniqueness inside a run is
// a counter and not a uuid, and for the 60-character budget the suites share.
// The budget is not tight here: the longest prefix in this suite is
// "Station-Updated-" at 16, so the worst name lands at 30 of the 60. It is
// python, whose longest prefix is 43, that forces a 14-character fragment.
//
// A BARE PROCESS-STATIC COUNTER DOES NOT WORK HERE, and did not: it restarts
// at 0 in every process, so every test's first uid() returned <tag>c000 and
// the 12 tests sharing a literal prefix with another test — PART-, PART-GET-,
// PART-RV- and so on — collided on a 409 every single run. That is the price
// of the isolation above, and it is paid here rather than by giving it up.
//
// So the counter strides by the number of registered tests, offset by the
// current test's index among them: test i yields i, i+N, i+2N, … Since the
// offset is always < N and the stride count increases on every call, no two
// calls can produce the same value — whether ctest gives each test its own
// process, or a developer runs ./tofupilot_tests directly and all 190 tests
// share one. Uniqueness is exact, not merely unlikely.
//
// Widens past three characters rather than wrapping: past 46 656 names a
// fragment grows, which is visible, instead of repeating one, which is not.
// A direct single-process run reaches four characters, which is why the
// budget headroom above is worth having.
// The current test's index among every test registered in this binary, and
// their total. Both are identical in every process: registration happens at
// static-initialisation time, and --gtest_filter only decides which of the
// registered tests actually runs — it does not unregister the others.
inline unsigned test_slot(unsigned& total) {
    const auto* unit = ::testing::UnitTest::GetInstance();
    total = static_cast<unsigned>(unit->total_test_count());
    if (total == 0) total = 1;  // no test running; keeps the stride non-zero
    const auto* info = unit->current_test_info();
    if (!info) return 0;
    unsigned index = 0;
    for (int s = 0; s < unit->total_test_suite_count(); ++s) {
        const auto* suite = unit->GetTestSuite(s);
        for (int t = 0; t < suite->total_test_count(); ++t) {
            if (suite->GetTestInfo(t) == info) return index;
            ++index;
        }
    }
    return 0;
}

inline std::string uid() {
    static std::atomic<unsigned> counter{0};
    static const char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    unsigned total = 1;
    unsigned n = test_slot(total) + counter.fetch_add(1) * total;
    std::string out;
    while (n > 0) {
        out.push_back(digits[n % 36]);
        n /= 36;
    }
    while (out.size() < 3) out.push_back('0');
    std::reverse(out.begin(), out.end());
    return tag() + "c" + out;
}

inline tofupilot::TofuPilot& client() {
    static tofupilot::TofuPilot instance = []() {
        const char* key = std::getenv("TOFUPILOT_API_KEY_USER");
        if (!key) throw std::runtime_error("TOFUPILOT_API_KEY_USER must be set");
        const char* url = std::getenv("TOFUPILOT_URL");
        std::string base_url = url ? std::string(url) : "http://localhost:3000";
        return tofupilot::TofuPilot(
            tofupilot::ClientConfig::with_api_key(key).set_base_url(base_url + "/api"));
    }();
    return instance;
}

inline std::string& procedure_id() {
    static std::string id;
    if (id.empty()) id = client().procedures().create().name("Cpp Test " + uid()).send().id;
    return id;
}

inline std::string iso_now(int offset_seconds = 0) {
    auto now = std::chrono::system_clock::now() + std::chrono::seconds(offset_seconds);
    auto t = std::chrono::system_clock::to_time_t(now);
    std::tm tm{};
#ifdef _WIN32
    gmtime_s(&tm, &t);
#else
    gmtime_r(&t, &tm);
#endif
    char buf[32];
    std::strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%SZ", &tm);
    return buf;
}

inline tofupilot::RunCreateResponse create_test_run(const std::string& uid_val) {
    auto ts = iso_now();
    return client().runs().create()
        .serial_number("SN-" + uid_val)
        .procedure_id(procedure_id())
        .part_number("PART-" + uid_val)
        .outcome(tofupilot::LogGetOutcome::Pass)
        .started_at(ts)
        .ended_at(ts)
        .send();
}

} // namespace test
