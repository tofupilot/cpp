#pragma once

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <random>
#include <string>
#include <tofupilot/tofupilot.hpp>
#include <gtest/gtest.h>

namespace test {

inline std::string uid() {
    static std::mt19937 rng(std::random_device{}());
    static const char chars[] = "0123456789abcdef";
    std::string result(8, ' ');
    for (auto& c : result) c = chars[rng() % 16];
    return result;
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
        .outcome(tofupilot::Outcome::Pass)
        .started_at(ts)
        .ended_at(ts)
        .send();
}

} // namespace test
