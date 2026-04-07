#include "common.hpp"
using namespace test;
using namespace tofupilot;

TEST(RunsGet, ReturnsMatchingId) {
    auto created = create_test_run(uid());
    EXPECT_EQ(created.id, client().runs().get().id(created.id).send().id);
}

TEST(RunsGet, NonexistentReturnsNotFound) {
    EXPECT_THROW(client().runs().get().id("550e8400-e29b-41d4-a716-446655440000").send(), NotFoundError);
}

TEST(RunsGet, IncludesPhasesAndMeasurements) {
    auto uid_val = uid();
    auto ts = iso_now();
    RunCreateMeasurements m1; m1.name = "boot_time_ms"; m1.outcome = ValidatorsOutcome::Pass; m1.measured_value = nlohmann::json(120.5);
    RunCreateMeasurements m2; m2.name = "memory_mb"; m2.outcome = ValidatorsOutcome::Pass; m2.measured_value = nlohmann::json(256);
    RunCreatePhases p1; p1.name = "init_phase"; p1.outcome = PhasesOutcome::Pass; p1.started_at = ts; p1.ended_at = ts; p1.measurements = {m1, m2};
    RunCreateMeasurements m3; m3.name = "cpu_temp"; m3.outcome = ValidatorsOutcome::Pass; m3.measured_value = nlohmann::json(65.2);
    RunCreatePhases p2; p2.name = "stress_phase"; p2.outcome = PhasesOutcome::Pass; p2.started_at = ts; p2.ended_at = ts; p2.measurements = {m3};
    auto created = client().runs().create().serial_number("SN-" + uid_val).procedure_id(procedure_id()).part_number("PART-" + uid_val).started_at(ts).ended_at(ts).outcome(Outcome::Pass).phases({p1, p2}).send();
    auto fetched = client().runs().get().id(created.id).send();
    ASSERT_TRUE(fetched.phases.has_value());
    auto& phases = fetched.phases.value();
    EXPECT_EQ(2, phases.size());
}

TEST(RunsGet, IncludesLogs) {
    auto uid_val = uid();
    auto ts = iso_now();
    RunCreateLogs log1; log1.level = Level::Info; log1.timestamp = ts; log1.message = "Initializing device"; log1.source_file = "device.cpp"; log1.line_number = 10.0;
    RunCreateLogs log2; log2.level = Level::Error; log2.timestamp = ts; log2.message = "Recovered from transient fault"; log2.source_file = "fault_handler.cpp"; log2.line_number = 55.0;
    auto created = client().runs().create().serial_number("SN-" + uid_val).procedure_id(procedure_id()).part_number("PART-" + uid_val).started_at(ts).ended_at(ts).outcome(Outcome::Pass).logs({log1, log2}).send();
    auto fetched = client().runs().get().id(created.id).send();
    ASSERT_TRUE(fetched.logs.has_value());
    EXPECT_EQ(2, fetched.logs.value().size());
}
