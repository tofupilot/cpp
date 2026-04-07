#include "common.hpp"
using namespace test;
using namespace tofupilot;

namespace {
nlohmann::json make_validator(const std::string& op, nlohmann::json expected, const std::string& outcome) {
    return {{"operator", op}, {"expected_value", expected}, {"outcome", outcome}};
}

RunCreatePhases make_phase(const std::string& name, const RunCreateMeasurements& m) {
    RunCreatePhases p;
    p.name = name;
    p.outcome = PhasesOutcome::Pass;
    p.started_at = iso_now(-300);
    p.ended_at = iso_now(-180);
    p.measurements = {m};
    return p;
}
}

TEST(RunsCreateValidators, OperatorGe) {
    auto uid_val = uid(); auto ts = iso_now();
    RunCreateMeasurements m; m.name = "test_ge"; m.outcome = ValidatorsOutcome::Pass; m.measured_value = nlohmann::json(10.0);
    m.validators = nlohmann::json::array({make_validator(">=", 5.0, "PASS")});
    auto created = client().runs().create().serial_number("SN-VGE-" + uid_val).procedure_id(procedure_id()).part_number("PART-VGE-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({make_phase("validation_phase", m)}).send();
    auto fetched = client().runs().get().id(created.id).send();
    ASSERT_TRUE(fetched.phases.has_value());
    ASSERT_TRUE(fetched.phases.value()[0].measurements[0].validators.has_value());
    EXPECT_EQ(">=", fetched.phases.value()[0].measurements[0].validators.value()[0].operator_.value());
}

TEST(RunsCreateValidators, OperatorLe) {
    auto uid_val = uid(); auto ts = iso_now();
    RunCreateMeasurements m; m.name = "test_le"; m.outcome = ValidatorsOutcome::Pass; m.measured_value = nlohmann::json(10.0);
    m.validators = nlohmann::json::array({make_validator("<=", 15.0, "PASS")});
    auto created = client().runs().create().serial_number("SN-VLE-" + uid_val).procedure_id(procedure_id()).part_number("PART-VLE-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({make_phase("validation_phase", m)}).send();
    auto fetched = client().runs().get().id(created.id).send();
    ASSERT_TRUE(fetched.phases.has_value());
    EXPECT_EQ("<=", fetched.phases.value()[0].measurements[0].validators.value()[0].operator_.value());
}

TEST(RunsCreateValidators, OperatorGt) {
    auto uid_val = uid(); auto ts = iso_now();
    RunCreateMeasurements m; m.name = "test_gt"; m.outcome = ValidatorsOutcome::Pass; m.measured_value = nlohmann::json(10.0);
    m.validators = nlohmann::json::array({make_validator(">", 5.0, "PASS")});
    auto created = client().runs().create().serial_number("SN-VGT-" + uid_val).procedure_id(procedure_id()).part_number("PART-VGT-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({make_phase("validation_phase", m)}).send();
    auto fetched = client().runs().get().id(created.id).send();
    EXPECT_EQ(">", fetched.phases.value()[0].measurements[0].validators.value()[0].operator_.value());
}

TEST(RunsCreateValidators, OperatorLt) {
    auto uid_val = uid(); auto ts = iso_now();
    RunCreateMeasurements m; m.name = "test_lt"; m.outcome = ValidatorsOutcome::Pass; m.measured_value = nlohmann::json(10.0);
    m.validators = nlohmann::json::array({make_validator("<", 15.0, "PASS")});
    auto created = client().runs().create().serial_number("SN-VLT-" + uid_val).procedure_id(procedure_id()).part_number("PART-VLT-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({make_phase("validation_phase", m)}).send();
    auto fetched = client().runs().get().id(created.id).send();
    EXPECT_EQ("<", fetched.phases.value()[0].measurements[0].validators.value()[0].operator_.value());
}

TEST(RunsCreateValidators, OperatorEq) {
    auto uid_val = uid(); auto ts = iso_now();
    RunCreateMeasurements m; m.name = "test_eq"; m.outcome = ValidatorsOutcome::Pass; m.measured_value = nlohmann::json(10.0);
    m.validators = nlohmann::json::array({make_validator("==", 10.0, "PASS")});
    auto created = client().runs().create().serial_number("SN-VEQ-" + uid_val).procedure_id(procedure_id()).part_number("PART-VEQ-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({make_phase("validation_phase", m)}).send();
    auto fetched = client().runs().get().id(created.id).send();
    EXPECT_EQ("==", fetched.phases.value()[0].measurements[0].validators.value()[0].operator_.value());
}

TEST(RunsCreateValidators, OperatorNe) {
    auto uid_val = uid(); auto ts = iso_now();
    RunCreateMeasurements m; m.name = "test_ne"; m.outcome = ValidatorsOutcome::Pass; m.measured_value = nlohmann::json(10.0);
    m.validators = nlohmann::json::array({make_validator("!=", 5.0, "PASS")});
    auto created = client().runs().create().serial_number("SN-VNE-" + uid_val).procedure_id(procedure_id()).part_number("PART-VNE-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({make_phase("validation_phase", m)}).send();
    auto fetched = client().runs().get().id(created.id).send();
    EXPECT_EQ("!=", fetched.phases.value()[0].measurements[0].validators.value()[0].operator_.value());
}

TEST(RunsCreateValidators, StringExpectedValue) {
    auto uid_val = uid(); auto ts = iso_now();
    RunCreateMeasurements m; m.name = "status"; m.outcome = ValidatorsOutcome::Pass; m.measured_value = nlohmann::json("PASS");
    m.validators = nlohmann::json::array({make_validator("==", "PASS", "PASS")});
    auto created = client().runs().create().serial_number("SN-VSTR-" + uid_val).procedure_id(procedure_id()).part_number("PART-VSTR-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({make_phase("string_check", m)}).send();
    auto fetched = client().runs().get().id(created.id).send();
    ASSERT_TRUE(fetched.phases.has_value());
    ASSERT_TRUE(fetched.phases.value()[0].measurements[0].validators.has_value());
}

TEST(RunsCreateValidators, BooleanExpectedValue) {
    auto uid_val = uid(); auto ts = iso_now();
    RunCreateMeasurements m; m.name = "is_calibrated"; m.outcome = ValidatorsOutcome::Pass; m.measured_value = nlohmann::json(true);
    m.validators = nlohmann::json::array({make_validator("==", true, "PASS")});
    auto created = client().runs().create().serial_number("SN-VBOOL-" + uid_val).procedure_id(procedure_id()).part_number("PART-VBOOL-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({make_phase("bool_check", m)}).send();
    ASSERT_FALSE(created.id.empty());
}

TEST(RunsCreateValidators, MultipleValidatorsRangeCheck) {
    auto uid_val = uid(); auto ts = iso_now();
    RunCreateMeasurements m; m.name = "range_value"; m.outcome = ValidatorsOutcome::Pass; m.measured_value = nlohmann::json(50.0);
    m.validators = nlohmann::json::array({make_validator(">=", 0, "PASS"), make_validator("<=", 100, "PASS")});
    auto created = client().runs().create().serial_number("SN-VMR-" + uid_val).procedure_id(procedure_id()).part_number("PART-VMR-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({make_phase("validation_phase", m)}).send();
    auto fetched = client().runs().get().id(created.id).send();
    ASSERT_TRUE(fetched.phases.value()[0].measurements[0].validators.has_value());
    EXPECT_EQ(2, fetched.phases.value()[0].measurements[0].validators.value().size());
}

TEST(RunsCreateValidators, IsDecisiveFalse) {
    auto uid_val = uid(); auto ts = iso_now();
    nlohmann::json v = {{"operator", ">="}, {"expected_value", 90}, {"outcome", "FAIL"}, {"is_decisive", false}};
    RunCreateMeasurements m; m.name = "marginal_check"; m.outcome = ValidatorsOutcome::Pass; m.measured_value = nlohmann::json(85.0);
    m.validators = nlohmann::json::array({v});
    auto created = client().runs().create().serial_number("SN-VIDF-" + uid_val).procedure_id(procedure_id()).part_number("PART-VIDF-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({make_phase("validation_phase", m)}).send();
    auto fetched = client().runs().get().id(created.id).send();
    auto& validator = fetched.phases.value()[0].measurements[0].validators.value()[0];
    ASSERT_TRUE(validator.is_decisive.has_value());
    EXPECT_FALSE(validator.is_decisive.value());
}

TEST(RunsCreateValidators, IsDecisiveTrue) {
    auto uid_val = uid(); auto ts = iso_now();
    nlohmann::json v = {{"operator", ">="}, {"expected_value", 0}, {"outcome", "PASS"}, {"is_decisive", true}};
    RunCreateMeasurements m; m.name = "decisive_check"; m.outcome = ValidatorsOutcome::Pass; m.measured_value = nlohmann::json(50.0);
    m.validators = nlohmann::json::array({v});
    auto created = client().runs().create().serial_number("SN-VIDT-" + uid_val).procedure_id(procedure_id()).part_number("PART-VIDT-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({make_phase("validation_phase", m)}).send();
    auto fetched = client().runs().get().id(created.id).send();
    auto& validator = fetched.phases.value()[0].measurements[0].validators.value()[0];
    ASSERT_TRUE(validator.is_decisive.has_value());
    EXPECT_TRUE(validator.is_decisive.value());
}

TEST(RunsCreateValidators, ExpressionOnly) {
    auto uid_val = uid(); auto ts = iso_now();
    nlohmann::json v = {{"expression", "value > threshold && value < max_threshold"}, {"outcome", "PASS"}};
    RunCreateMeasurements m; m.name = "expr_check"; m.outcome = ValidatorsOutcome::Pass; m.measured_value = nlohmann::json(50.0);
    m.validators = nlohmann::json::array({v});
    auto created = client().runs().create().serial_number("SN-VEXPR-" + uid_val).procedure_id(procedure_id()).part_number("PART-VEXPR-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({make_phase("validation_phase", m)}).send();
    auto fetched = client().runs().get().id(created.id).send();
    auto& validator = fetched.phases.value()[0].measurements[0].validators.value()[0];
    EXPECT_TRUE(validator.is_expression_only);
    EXPECT_NE(std::string::npos, validator.expression.find("threshold"));
}

TEST(RunsCreateValidators, CustomExpression) {
    auto uid_val = uid(); auto ts = iso_now();
    nlohmann::json v = {{"operator", ">="}, {"expected_value", 0}, {"expression", "voltage within safe range"}, {"outcome", "PASS"}};
    RunCreateMeasurements m; m.name = "custom_expr"; m.outcome = ValidatorsOutcome::Pass; m.measured_value = nlohmann::json(3.3);
    m.validators = nlohmann::json::array({v});
    auto created = client().runs().create().serial_number("SN-VCE-" + uid_val).procedure_id(procedure_id()).part_number("PART-VCE-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({make_phase("validation_phase", m)}).send();
    auto fetched = client().runs().get().id(created.id).send();
    auto& validator = fetched.phases.value()[0].measurements[0].validators.value()[0];
    EXPECT_TRUE(validator.has_custom_expression);
    EXPECT_EQ("voltage within safe range", validator.expression);
}

TEST(RunsCreateValidators, FailOutcome) {
    auto uid_val = uid(); auto ts = iso_now();
    RunCreateMeasurements m; m.name = "over_limit"; m.outcome = ValidatorsOutcome::Fail; m.measured_value = nlohmann::json(10.0);
    m.validators = nlohmann::json::array({make_validator("<=", 5, "FAIL")});
    RunCreatePhases p; p.name = "fail_phase"; p.outcome = PhasesOutcome::Fail; p.started_at = ts; p.ended_at = ts; p.measurements = {m};
    auto created = client().runs().create().serial_number("SN-VFAIL-" + uid_val).procedure_id(procedure_id()).part_number("PART-VFAIL-" + uid_val).outcome(Outcome::Fail).started_at(ts).ended_at(ts).phases({p}).send();
    auto fetched = client().runs().get().id(created.id).send();
    EXPECT_EQ(ValidatorsOutcome::Fail, fetched.phases.value()[0].measurements[0].validators.value()[0].outcome);
}

TEST(RunsCreateValidators, InOperatorStringList) {
    auto uid_val = uid(); auto ts = iso_now();
    nlohmann::json v = {{"operator", "in"}, {"expected_value", {"A", "B", "C"}}, {"outcome", "PASS"}};
    RunCreateMeasurements m; m.name = "grade"; m.outcome = ValidatorsOutcome::Pass; m.measured_value = nlohmann::json("A");
    m.validators = nlohmann::json::array({v});
    auto created = client().runs().create().serial_number("SN-VIN-" + uid_val).procedure_id(procedure_id()).part_number("PART-VIN-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({make_phase("in_check", m)}).send();
    auto fetched = client().runs().get().id(created.id).send();
    EXPECT_EQ("in", fetched.phases.value()[0].measurements[0].validators.value()[0].operator_.value());
}

TEST(RunsCreateValidators, RangeOperator) {
    auto uid_val = uid(); auto ts = iso_now();
    nlohmann::json v = {{"operator", "range"}, {"expected_value", {10.0, 50.0}}, {"outcome", "PASS"}};
    RunCreateMeasurements m; m.name = "range_check"; m.outcome = ValidatorsOutcome::Pass; m.measured_value = nlohmann::json(25.0);
    m.validators = nlohmann::json::array({v});
    auto created = client().runs().create().serial_number("SN-VRNG-" + uid_val).procedure_id(procedure_id()).part_number("PART-VRNG-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({make_phase("validation_phase", m)}).send();
    auto fetched = client().runs().get().id(created.id).send();
    ASSERT_TRUE(fetched.phases.value()[0].measurements[0].validators.has_value());
    EXPECT_FALSE(fetched.phases.value()[0].measurements[0].validators.value().empty());
}

TEST(RunsCreateValidators, MultipleMeasurementsWithValidators) {
    auto uid_val = uid(); auto ts = iso_now();
    RunCreateMeasurements m1; m1.name = "voltage"; m1.outcome = ValidatorsOutcome::Pass; m1.measured_value = nlohmann::json(3.3);
    m1.validators = nlohmann::json::array({make_validator(">=", 3.0, "PASS"), make_validator("<=", 3.6, "PASS")});
    RunCreateMeasurements m2; m2.name = "current"; m2.outcome = ValidatorsOutcome::Pass; m2.measured_value = nlohmann::json(0.5);
    m2.validators = nlohmann::json::array({make_validator("<", 1.0, "PASS")});
    RunCreatePhases p; p.name = "multi_meas"; p.outcome = PhasesOutcome::Pass; p.started_at = ts; p.ended_at = ts; p.measurements = {m1, m2};
    auto created = client().runs().create().serial_number("SN-VMM-" + uid_val).procedure_id(procedure_id()).part_number("PART-VMM-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({p}).send();
    auto fetched = client().runs().get().id(created.id).send();
    EXPECT_EQ(2, fetched.phases.value()[0].measurements.size());
    ASSERT_TRUE(fetched.phases.value()[0].measurements[0].validators.has_value());
    EXPECT_FALSE(fetched.phases.value()[0].measurements[0].validators.value().empty());
    ASSERT_TRUE(fetched.phases.value()[0].measurements[1].validators.has_value());
    EXPECT_FALSE(fetched.phases.value()[0].measurements[1].validators.value().empty());
}
