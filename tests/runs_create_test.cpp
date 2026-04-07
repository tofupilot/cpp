#include "common.hpp"
using namespace test;
using namespace tofupilot;

TEST(RunsCreate, ReturnsId) { ASSERT_FALSE(create_test_run(uid()).id.empty()); }

TEST(RunsCreate, WithPhases) {
    auto ts = iso_now();
    RunCreateMeasurements m; m.name = "output_voltage"; m.outcome = ValidatorsOutcome::Pass; m.measured_value = nlohmann::json(3.3);
    RunCreatePhases p; p.name = "voltage_check"; p.outcome = PhasesOutcome::Pass; p.started_at = ts; p.ended_at = ts; p.measurements = {m};
    auto created = client().runs().create().serial_number("SN-" + uid()).procedure_id(procedure_id()).part_number("PART-" + uid()).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({p}).send();
    auto fetched = client().runs().get().id(created.id).send();
    ASSERT_TRUE(fetched.phases.has_value());
    EXPECT_EQ("voltage_check", fetched.phases.value()[0].name);
}

TEST(RunsCreate, EmptySerialNumberFails) {
    auto ts = iso_now();
    EXPECT_THROW(client().runs().create().serial_number("").procedure_id(procedure_id()).part_number("PART-" + uid()).outcome(Outcome::Pass).started_at(ts).ended_at(ts).send(), BadRequestError);
}

TEST(RunsCreate, InvalidProcedureIdFails) {
    auto ts = iso_now();
    EXPECT_THROW(client().runs().create().serial_number("SN-" + uid()).procedure_id("550e8400-e29b-41d4-a716-446655440000").part_number("PART-" + uid()).outcome(Outcome::Pass).started_at(ts).ended_at(ts).send(), NotFoundError);
}

TEST(RunsCreate, WithProcedureVersion) {
    auto uid_val = uid();
    auto ts = iso_now();
    auto created = client().runs().create().serial_number("SN-" + uid_val).procedure_id(procedure_id()).part_number("PART-" + uid_val).started_at(ts).ended_at(ts).outcome(Outcome::Pass).procedure_version("1.2.3").send();
    auto fetched = client().runs().get().id(created.id).send();
    ASSERT_TRUE(fetched.procedure.version.has_value());
    EXPECT_EQ("1.2.3", fetched.procedure.version.value().tag);
}

TEST(RunsCreate, WithDocstring) {
    auto uid_val = uid();
    auto ts = iso_now();
    auto created = client().runs().create().serial_number("SN-" + uid_val).procedure_id(procedure_id()).part_number("PART-" + uid_val).started_at(ts).ended_at(ts).outcome(Outcome::Pass).docstring("Test docstring for verification").send();
    auto fetched = client().runs().get().id(created.id).send();
    ASSERT_TRUE(fetched.docstring.has_value());
    EXPECT_EQ("Test docstring for verification", fetched.docstring.get());
}

TEST(RunsCreate, WithLogs) {
    auto uid_val = uid();
    auto ts = iso_now();
    RunCreateLogs log1; log1.level = Level::Info; log1.timestamp = ts; log1.message = "Test started successfully"; log1.source_file = "test_runner.cpp"; log1.line_number = 42.0;
    RunCreateLogs log2; log2.level = Level::Warning; log2.timestamp = ts; log2.message = "Voltage slightly above nominal"; log2.source_file = "test_runner.cpp"; log2.line_number = 88.0;
    auto created = client().runs().create().serial_number("SN-" + uid_val).procedure_id(procedure_id()).part_number("PART-" + uid_val).started_at(ts).ended_at(ts).outcome(Outcome::Pass).logs({log1, log2}).send();
    auto fetched = client().runs().get().id(created.id).send();
    ASSERT_TRUE(fetched.logs.has_value());
    EXPECT_EQ(2, fetched.logs.value().size());
}

TEST(RunsCreate, WithLegacyLimits) {
    auto uid_val = uid();
    auto ts = iso_now();
    RunCreateMeasurements m; m.name = "temperature"; m.outcome = ValidatorsOutcome::Pass; m.measured_value = nlohmann::json(25.0); m.lower_limit = 10.0; m.upper_limit = 40.0;
    RunCreatePhases p; p.name = "limit_phase"; p.outcome = PhasesOutcome::Pass; p.started_at = ts; p.ended_at = ts; p.measurements = {m};
    auto created = client().runs().create().serial_number("SN-" + uid_val).procedure_id(procedure_id()).part_number("PART-" + uid_val).started_at(ts).ended_at(ts).outcome(Outcome::Pass).phases({p}).send();
    ASSERT_FALSE(created.id.empty());
    auto fetched = client().runs().get().id(created.id).send();
    ASSERT_TRUE(fetched.phases.has_value());
    EXPECT_EQ(1, fetched.phases.value().size());
}

TEST(RunsCreate, WithAggregations) {
    auto uid_val = uid();
    auto ts = iso_now();
    RunCreateMeasurementsAggregations agg; agg.type = "avg"; agg.value = NullableField<nlohmann::json>::value(nlohmann::json(72.3));
    RunCreateMeasurements m; m.name = "signal_strength"; m.outcome = ValidatorsOutcome::Pass; m.measured_value = nlohmann::json(75.5); m.aggregations = {agg};
    RunCreatePhases p; p.name = "agg_phase"; p.outcome = PhasesOutcome::Pass; p.started_at = ts; p.ended_at = ts; p.measurements = {m};
    auto created = client().runs().create().serial_number("SN-" + uid_val).procedure_id(procedure_id()).part_number("PART-" + uid_val).started_at(ts).ended_at(ts).outcome(Outcome::Pass).phases({p}).send();
    ASSERT_FALSE(created.id.empty());
}

TEST(RunsCreate, WithSubUnits) {
    auto uid_val = uid();
    auto ts = iso_now();
    auto sub1 = "SUB1-" + uid_val;
    auto sub2 = "SUB2-" + uid_val;
    for (const auto& sub : {sub1, sub2})
        client().runs().create().serial_number(sub).procedure_id(procedure_id()).part_number("SUB-PART-" + uid_val).started_at(ts).ended_at(ts).outcome(Outcome::Pass).send();
    auto created = client().runs().create().serial_number("SN-" + uid_val).procedure_id(procedure_id()).part_number("PART-" + uid_val).started_at(ts).ended_at(ts).outcome(Outcome::Pass).sub_units({sub1, sub2}).send();
    auto fetched = client().runs().get().id(created.id).send();
    ASSERT_TRUE(fetched.sub_units.has_value());
    EXPECT_EQ(2, fetched.sub_units.value().size());
}

TEST(RunsCreate, WithRetryCount) {
    auto uid_val = uid(); auto ts = iso_now();
    RunCreateMeasurements m1; m1.name = "voltage"; m1.outcome = ValidatorsOutcome::Fail; m1.measured_value = nlohmann::json(2.0);
    RunCreatePhases p1; p1.name = "retried_phase"; p1.outcome = PhasesOutcome::Fail; p1.started_at = iso_now(-600); p1.ended_at = iso_now(-480); p1.retry_count = 0; p1.measurements = {m1};
    RunCreateMeasurements m2; m2.name = "voltage"; m2.outcome = ValidatorsOutcome::Pass; m2.measured_value = nlohmann::json(3.3);
    RunCreatePhases p2; p2.name = "retried_phase"; p2.outcome = PhasesOutcome::Pass; p2.started_at = iso_now(-420); p2.ended_at = iso_now(-300); p2.retry_count = 1; p2.measurements = {m2};
    auto created = client().runs().create().serial_number("SN-RC-" + uid_val).procedure_id(procedure_id()).part_number("PART-RC-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({p1, p2}).send();
    auto fetched = client().runs().get().id(created.id).send();
    ASSERT_EQ(2, fetched.phases.value().size());
    EXPECT_EQ(0, fetched.phases.value()[0].retry_count);
    EXPECT_EQ(1, fetched.phases.value()[1].retry_count);
}

TEST(RunsCreate, RetryCountDefaultsToZero) {
    auto uid_val = uid(); auto ts = iso_now();
    RunCreateMeasurements m; m.name = "test_val"; m.outcome = ValidatorsOutcome::Pass; m.measured_value = nlohmann::json(1.0);
    RunCreatePhases p; p.name = "no_retry"; p.outcome = PhasesOutcome::Pass; p.started_at = ts; p.ended_at = ts; p.measurements = {m};
    auto created = client().runs().create().serial_number("SN-RCD-" + uid_val).procedure_id(procedure_id()).part_number("PART-RCD-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({p}).send();
    auto fetched = client().runs().get().id(created.id).send();
    EXPECT_EQ(0, fetched.phases.value()[0].retry_count);
}

TEST(RunsCreate, LegacyLimitsBothBounds) {
    auto uid_val = uid(); auto ts = iso_now();
    RunCreateMeasurements m; m.name = "temp"; m.outcome = ValidatorsOutcome::Pass; m.measured_value = nlohmann::json(25.0); m.lower_limit = 10.0; m.upper_limit = 40.0;
    RunCreatePhases p; p.name = "both_limits"; p.outcome = PhasesOutcome::Pass; p.started_at = ts; p.ended_at = ts; p.measurements = {m};
    auto created = client().runs().create().serial_number("SN-LBB-" + uid_val).procedure_id(procedure_id()).part_number("PART-LBB-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({p}).send();
    auto fetched = client().runs().get().id(created.id).send();
    ASSERT_TRUE(fetched.phases.value()[0].measurements[0].validators.has_value());
    EXPECT_EQ(2, fetched.phases.value()[0].measurements[0].validators.value().size());
}

TEST(RunsCreate, LegacyLimitsOnlyLower) {
    auto uid_val = uid(); auto ts = iso_now();
    RunCreateMeasurements m; m.name = "current"; m.outcome = ValidatorsOutcome::Pass; m.measured_value = nlohmann::json(0.5); m.lower_limit = 0.0;
    RunCreatePhases p; p.name = "lower_only"; p.outcome = PhasesOutcome::Pass; p.started_at = ts; p.ended_at = ts; p.measurements = {m};
    auto created = client().runs().create().serial_number("SN-LLO-" + uid_val).procedure_id(procedure_id()).part_number("PART-LLO-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({p}).send();
    auto fetched = client().runs().get().id(created.id).send();
    ASSERT_TRUE(fetched.phases.value()[0].measurements[0].validators.has_value());
    EXPECT_EQ(1, fetched.phases.value()[0].measurements[0].validators.value().size());
}

TEST(RunsCreate, LegacyLimitsOnlyUpper) {
    auto uid_val = uid(); auto ts = iso_now();
    RunCreateMeasurements m; m.name = "power"; m.outcome = ValidatorsOutcome::Pass; m.measured_value = nlohmann::json(3.0); m.upper_limit = 5.0;
    RunCreatePhases p; p.name = "upper_only"; p.outcome = PhasesOutcome::Pass; p.started_at = ts; p.ended_at = ts; p.measurements = {m};
    auto created = client().runs().create().serial_number("SN-LUO-" + uid_val).procedure_id(procedure_id()).part_number("PART-LUO-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({p}).send();
    auto fetched = client().runs().get().id(created.id).send();
    ASSERT_TRUE(fetched.phases.value()[0].measurements[0].validators.has_value());
    EXPECT_EQ(1, fetched.phases.value()[0].measurements[0].validators.value().size());
}

TEST(RunsCreate, LegacyLimitsFailure) {
    auto uid_val = uid(); auto ts = iso_now();
    RunCreateMeasurements m; m.name = "voltage"; m.outcome = ValidatorsOutcome::Fail; m.measured_value = nlohmann::json(50.0); m.lower_limit = 0.0; m.upper_limit = 10.0;
    RunCreatePhases p; p.name = "fail_limit"; p.outcome = PhasesOutcome::Fail; p.started_at = ts; p.ended_at = ts; p.measurements = {m};
    auto created = client().runs().create().serial_number("SN-LLF-" + uid_val).procedure_id(procedure_id()).part_number("PART-LLF-" + uid_val).outcome(Outcome::Fail).started_at(ts).ended_at(ts).phases({p}).send();
    auto fetched = client().runs().get().id(created.id).send();
    ASSERT_TRUE(fetched.phases.value()[0].measurements[0].validators.has_value());
}

TEST(RunsCreate, LegacyLimitsNegativeValues) {
    auto uid_val = uid(); auto ts = iso_now();
    RunCreateMeasurements m; m.name = "offset"; m.outcome = ValidatorsOutcome::Pass; m.measured_value = nlohmann::json(-5.0); m.lower_limit = -10.0; m.upper_limit = 0.0;
    RunCreatePhases p; p.name = "neg_limits"; p.outcome = PhasesOutcome::Pass; p.started_at = ts; p.ended_at = ts; p.measurements = {m};
    auto created = client().runs().create().serial_number("SN-LNV-" + uid_val).procedure_id(procedure_id()).part_number("PART-LNV-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({p}).send();
    ASSERT_FALSE(created.id.empty());
}

TEST(RunsCreate, SubUnitsWithoutSubUnits) {
    auto uid_val = uid(); auto ts = iso_now();
    auto created = client().runs().create().serial_number("SN-NSUB-" + uid_val).procedure_id(procedure_id()).part_number("PART-NSUB-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).send();
    auto fetched = client().runs().get().id(created.id).send();
    EXPECT_TRUE(!fetched.sub_units.has_value() || fetched.sub_units.value().empty());
}

TEST(RunsCreate, SubUnitsSingle) {
    auto uid_val = uid(); auto ts = iso_now();
    auto sub = "SUB-" + uid_val;
    client().runs().create().serial_number(sub).procedure_id(procedure_id()).part_number("SUB-PART-" + uid_val).started_at(ts).ended_at(ts).outcome(Outcome::Pass).send();
    auto created = client().runs().create().serial_number("SN-SSUB-" + uid_val).procedure_id(procedure_id()).part_number("PART-SSUB-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).sub_units({sub}).send();
    auto fetched = client().runs().get().id(created.id).send();
    ASSERT_TRUE(fetched.sub_units.has_value());
    EXPECT_EQ(1, fetched.sub_units.value().size());
}

TEST(RunsCreate, SubUnitsEmptyList) {
    auto uid_val = uid(); auto ts = iso_now();
    auto created = client().runs().create().serial_number("SN-ESUB-" + uid_val).procedure_id(procedure_id()).part_number("PART-ESUB-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).sub_units({}).send();
    auto fetched = client().runs().get().id(created.id).send();
    EXPECT_TRUE(!fetched.sub_units.has_value() || fetched.sub_units.value().empty());
}

TEST(RunsCreate, MultiplePhasesMeasurements) {
    auto uid_val = uid(); auto ts = iso_now();
    RunCreateMeasurements m1; m1.name = "v1"; m1.outcome = ValidatorsOutcome::Pass; m1.measured_value = nlohmann::json(3.3);
    RunCreateMeasurements m2; m2.name = "v2"; m2.outcome = ValidatorsOutcome::Pass; m2.measured_value = nlohmann::json(5.0);
    RunCreatePhases pa; pa.name = "phase_a"; pa.outcome = PhasesOutcome::Pass; pa.started_at = iso_now(-600); pa.ended_at = iso_now(-420); pa.measurements = {m1, m2};
    RunCreateMeasurements m3; m3.name = "temp"; m3.outcome = ValidatorsOutcome::Pass; m3.measured_value = nlohmann::json(25.0);
    RunCreatePhases pb; pb.name = "phase_b"; pb.outcome = PhasesOutcome::Pass; pb.started_at = iso_now(-360); pb.ended_at = iso_now(-180); pb.measurements = {m3};
    auto created = client().runs().create().serial_number("SN-MPM-" + uid_val).procedure_id(procedure_id()).part_number("PART-MPM-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({pa, pb}).send();
    auto fetched = client().runs().get().id(created.id).send();
    ASSERT_EQ(2, fetched.phases.value().size());
    EXPECT_EQ(2, fetched.phases.value()[0].measurements.size());
    EXPECT_EQ(1, fetched.phases.value()[1].measurements.size());
}
