#include "common.hpp"
using namespace test;
using namespace tofupilot;

namespace {
RunCreatePhases make_agg_phase(const std::string& name, const RunCreateMeasurements& m) {
    RunCreatePhases p;
    p.name = "agg_phase";
    p.outcome = PhasesOutcome::Pass;
    p.started_at = iso_now(-300);
    p.ended_at = iso_now(-180);
    p.measurements = {m};
    return p;
}
}

TEST(RunsCreateAggregations, TypeAvg) {
    auto uid_val = uid(); auto ts = iso_now();
    RunCreateMeasurementsAggregations agg; agg.type = "avg"; agg.value = NullableField<nlohmann::json>::value(nlohmann::json(42.0)); agg.outcome = std::string("PASS");
    RunCreateMeasurements m; m.name = "test_avg"; m.outcome = ValidatorsOutcome::Pass; m.measured_value = nlohmann::json(50.0); m.aggregations = {agg};
    auto created = client().runs().create().serial_number("SN-AAVG-" + uid_val).procedure_id(procedure_id()).part_number("PART-AAVG-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({make_agg_phase("agg_phase", m)}).send();
    auto fetched = client().runs().get().id(created.id).send();
    ASSERT_TRUE(fetched.phases.value()[0].measurements[0].aggregations.has_value());
    EXPECT_EQ(1, fetched.phases.value()[0].measurements[0].aggregations.get().size());
}

TEST(RunsCreateAggregations, TypeMin) {
    auto uid_val = uid(); auto ts = iso_now();
    RunCreateMeasurementsAggregations agg; agg.type = "min"; agg.value = NullableField<nlohmann::json>::value(nlohmann::json(42.0)); agg.outcome = std::string("PASS");
    RunCreateMeasurements m; m.name = "test_min"; m.outcome = ValidatorsOutcome::Pass; m.measured_value = nlohmann::json(50.0); m.aggregations = {agg};
    auto created = client().runs().create().serial_number("SN-AMIN-" + uid_val).procedure_id(procedure_id()).part_number("PART-AMIN-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({make_agg_phase("agg_phase", m)}).send();
    auto fetched = client().runs().get().id(created.id).send();
    ASSERT_TRUE(fetched.phases.value()[0].measurements[0].aggregations.has_value());
}

TEST(RunsCreateAggregations, TypeMax) {
    auto uid_val = uid(); auto ts = iso_now();
    RunCreateMeasurementsAggregations agg; agg.type = "max"; agg.value = NullableField<nlohmann::json>::value(nlohmann::json(42.0));
    RunCreateMeasurements m; m.name = "test_max"; m.outcome = ValidatorsOutcome::Pass; m.measured_value = nlohmann::json(50.0); m.aggregations = {agg};
    auto created = client().runs().create().serial_number("SN-AMAX-" + uid_val).procedure_id(procedure_id()).part_number("PART-AMAX-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({make_agg_phase("agg_phase", m)}).send();
    ASSERT_FALSE(created.id.empty());
}

TEST(RunsCreateAggregations, TypeSum) {
    auto uid_val = uid(); auto ts = iso_now();
    RunCreateMeasurementsAggregations agg; agg.type = "sum"; agg.value = NullableField<nlohmann::json>::value(nlohmann::json(42.0)); agg.outcome = std::string("PASS");
    RunCreateMeasurements m; m.name = "test_sum"; m.outcome = ValidatorsOutcome::Pass; m.measured_value = nlohmann::json(50.0); m.aggregations = {agg};
    auto created = client().runs().create().serial_number("SN-ASUM-" + uid_val).procedure_id(procedure_id()).part_number("PART-ASUM-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({make_agg_phase("agg_phase", m)}).send();
    ASSERT_FALSE(created.id.empty());
}

TEST(RunsCreateAggregations, TypeCount) {
    auto uid_val = uid(); auto ts = iso_now();
    RunCreateMeasurementsAggregations agg; agg.type = "count"; agg.value = NullableField<nlohmann::json>::value(nlohmann::json(42.0)); agg.outcome = std::string("PASS");
    RunCreateMeasurements m; m.name = "test_count"; m.outcome = ValidatorsOutcome::Pass; m.measured_value = nlohmann::json(50.0); m.aggregations = {agg};
    auto created = client().runs().create().serial_number("SN-ACNT-" + uid_val).procedure_id(procedure_id()).part_number("PART-ACNT-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({make_agg_phase("agg_phase", m)}).send();
    ASSERT_FALSE(created.id.empty());
}

TEST(RunsCreateAggregations, TypeStd) {
    auto uid_val = uid(); auto ts = iso_now();
    RunCreateMeasurementsAggregations agg; agg.type = "std"; agg.value = NullableField<nlohmann::json>::value(nlohmann::json(42.0)); agg.outcome = std::string("PASS");
    RunCreateMeasurements m; m.name = "test_std"; m.outcome = ValidatorsOutcome::Pass; m.measured_value = nlohmann::json(50.0); m.aggregations = {agg};
    auto created = client().runs().create().serial_number("SN-ASTD-" + uid_val).procedure_id(procedure_id()).part_number("PART-ASTD-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({make_agg_phase("agg_phase", m)}).send();
    ASSERT_FALSE(created.id.empty());
}

TEST(RunsCreateAggregations, TypeMedian) {
    auto uid_val = uid(); auto ts = iso_now();
    RunCreateMeasurementsAggregations agg; agg.type = "median"; agg.value = NullableField<nlohmann::json>::value(nlohmann::json(42.0)); agg.outcome = std::string("PASS");
    RunCreateMeasurements m; m.name = "test_median"; m.outcome = ValidatorsOutcome::Pass; m.measured_value = nlohmann::json(50.0); m.aggregations = {agg};
    auto created = client().runs().create().serial_number("SN-AMED-" + uid_val).procedure_id(procedure_id()).part_number("PART-AMED-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({make_agg_phase("agg_phase", m)}).send();
    ASSERT_FALSE(created.id.empty());
}

TEST(RunsCreateAggregations, MultipleOnSingleMeasurement) {
    auto uid_val = uid(); auto ts = iso_now();
    RunCreateMeasurementsAggregations a1; a1.type = "avg"; a1.value = NullableField<nlohmann::json>::value(nlohmann::json(72.3)); a1.outcome = std::string("PASS");
    RunCreateMeasurementsAggregations a2; a2.type = "max"; a2.value = NullableField<nlohmann::json>::value(nlohmann::json(80.1));
    RunCreateMeasurementsAggregations a3; a3.type = "min"; a3.value = NullableField<nlohmann::json>::value(nlohmann::json(65.0));
    RunCreateMeasurements m; m.name = "multi_agg"; m.outcome = ValidatorsOutcome::Pass; m.measured_value = nlohmann::json(75.5); m.aggregations = {a1, a2, a3};
    auto created = client().runs().create().serial_number("SN-AML-" + uid_val).procedure_id(procedure_id()).part_number("PART-AML-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({make_agg_phase("agg_phase", m)}).send();
    auto fetched = client().runs().get().id(created.id).send();
    EXPECT_EQ(3, fetched.phases.value()[0].measurements[0].aggregations.get().size());
}

TEST(RunsCreateAggregations, StringValue) {
    auto uid_val = uid(); auto ts = iso_now();
    RunCreateMeasurementsAggregations agg; agg.type = "mode"; agg.value = NullableField<nlohmann::json>::value(nlohmann::json("nominal"));
    RunCreateMeasurements m; m.name = "status_mode"; m.outcome = ValidatorsOutcome::Pass; m.measured_value = nlohmann::json("nominal"); m.aggregations = {agg};
    auto created = client().runs().create().serial_number("SN-ASV-" + uid_val).procedure_id(procedure_id()).part_number("PART-ASV-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({make_agg_phase("str_agg_phase", m)}).send();
    ASSERT_FALSE(created.id.empty());
}

TEST(RunsCreateAggregations, BooleanValue) {
    auto uid_val = uid(); auto ts = iso_now();
    RunCreateMeasurementsAggregations agg; agg.type = "all"; agg.value = NullableField<nlohmann::json>::value(nlohmann::json(true));
    RunCreateMeasurements m; m.name = "all_pass"; m.outcome = ValidatorsOutcome::Pass; m.measured_value = nlohmann::json(true); m.aggregations = {agg};
    auto created = client().runs().create().serial_number("SN-ABV-" + uid_val).procedure_id(procedure_id()).part_number("PART-ABV-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({make_agg_phase("bool_agg_phase", m)}).send();
    ASSERT_FALSE(created.id.empty());
}

TEST(RunsCreateAggregations, WithValidators) {
    auto uid_val = uid(); auto ts = iso_now();
    RunCreateMeasurementsAggregationsValidators v1; v1.operator_ = std::string(">="); v1.expected_value = nlohmann::json(60.0); v1.outcome = std::string("PASS");
    RunCreateMeasurementsAggregationsValidators v2; v2.operator_ = std::string("<="); v2.expected_value = nlohmann::json(90.0); v2.outcome = std::string("PASS");
    RunCreateMeasurementsAggregations agg; agg.type = "avg"; agg.value = NullableField<nlohmann::json>::value(nlohmann::json(72.3)); agg.outcome = std::string("PASS"); agg.validators = {v1, v2};
    RunCreateMeasurements m; m.name = "agg_with_val"; m.outcome = ValidatorsOutcome::Pass; m.measured_value = nlohmann::json(75.0); m.aggregations = {agg};
    auto created = client().runs().create().serial_number("SN-AWV-" + uid_val).procedure_id(procedure_id()).part_number("PART-AWV-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({make_agg_phase("agg_phase", m)}).send();
    auto fetched = client().runs().get().id(created.id).send();
    auto& agg_resp = fetched.phases.value()[0].measurements[0].aggregations.get()[0];
    ASSERT_TRUE(agg_resp.validators.has_value());
    EXPECT_EQ(2, agg_resp.validators.get().size());
}

TEST(RunsCreateAggregations, OutcomePass) {
    auto uid_val = uid(); auto ts = iso_now();
    RunCreateMeasurementsAggregations agg; agg.type = "avg"; agg.value = NullableField<nlohmann::json>::value(nlohmann::json(50.0)); agg.outcome = std::string("PASS");
    RunCreateMeasurements m; m.name = "agg_pass"; m.outcome = ValidatorsOutcome::Pass; m.measured_value = nlohmann::json(50.0); m.aggregations = {agg};
    auto created = client().runs().create().serial_number("SN-AOP-" + uid_val).procedure_id(procedure_id()).part_number("PART-AOP-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({make_agg_phase("agg_phase", m)}).send();
    auto fetched = client().runs().get().id(created.id).send();
    ASSERT_TRUE(fetched.phases.value()[0].measurements[0].aggregations.get()[0].outcome.has_value());
    EXPECT_EQ("PASS", fetched.phases.value()[0].measurements[0].aggregations.get()[0].outcome.value());
}

TEST(RunsCreateAggregations, OutcomeFail) {
    auto uid_val = uid(); auto ts = iso_now();
    RunCreateMeasurementsAggregations agg; agg.type = "avg"; agg.value = NullableField<nlohmann::json>::value(nlohmann::json(50.0)); agg.outcome = std::string("FAIL");
    RunCreateMeasurements m; m.name = "agg_fail"; m.outcome = ValidatorsOutcome::Fail; m.measured_value = nlohmann::json(50.0); m.aggregations = {agg};
    RunCreatePhases p; p.name = "fail_agg"; p.outcome = PhasesOutcome::Fail; p.started_at = ts; p.ended_at = ts; p.measurements = {m};
    auto created = client().runs().create().serial_number("SN-AOF-" + uid_val).procedure_id(procedure_id()).part_number("PART-AOF-" + uid_val).outcome(Outcome::Fail).started_at(ts).ended_at(ts).phases({p}).send();
    auto fetched = client().runs().get().id(created.id).send();
    EXPECT_EQ("FAIL", fetched.phases.value()[0].measurements[0].aggregations.get()[0].outcome.value());
}

TEST(RunsCreateAggregations, SpecialCharType) {
    auto uid_val = uid(); auto ts = iso_now();
    RunCreateMeasurementsAggregations agg; agg.type = "percentile_95"; agg.value = NullableField<nlohmann::json>::value(nlohmann::json(95.0));
    RunCreateMeasurements m; m.name = "special_type"; m.outcome = ValidatorsOutcome::Pass; m.measured_value = nlohmann::json(90.0); m.aggregations = {agg};
    auto created = client().runs().create().serial_number("SN-AST-" + uid_val).procedure_id(procedure_id()).part_number("PART-AST-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({make_agg_phase("agg_phase", m)}).send();
    auto fetched = client().runs().get().id(created.id).send();
    // Type may be stored uppercased
    auto type_str = fetched.phases.value()[0].measurements[0].aggregations.get()[0].type;
    // Case-insensitive compare
    std::string lower_type; lower_type.resize(type_str.size());
    std::transform(type_str.begin(), type_str.end(), lower_type.begin(), ::tolower);
    EXPECT_EQ("percentile_95", lower_type);
}

TEST(RunsCreateAggregations, NegativeValue) {
    auto uid_val = uid(); auto ts = iso_now();
    RunCreateMeasurementsAggregations agg; agg.type = "min"; agg.value = NullableField<nlohmann::json>::value(nlohmann::json(-15.5));
    RunCreateMeasurements m; m.name = "neg_agg"; m.outcome = ValidatorsOutcome::Pass; m.measured_value = nlohmann::json(-10.0); m.aggregations = {agg};
    auto created = client().runs().create().serial_number("SN-ANV-" + uid_val).procedure_id(procedure_id()).part_number("PART-ANV-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({make_agg_phase("agg_phase", m)}).send();
    ASSERT_FALSE(created.id.empty());
}

TEST(RunsCreateAggregations, ValidatorWithIsDecisive) {
    auto uid_val = uid(); auto ts = iso_now();
    RunCreateMeasurementsAggregationsValidators v; v.operator_ = std::string(">="); v.expected_value = nlohmann::json(80.0); v.outcome = std::string("FAIL"); v.is_decisive = false;
    RunCreateMeasurementsAggregations agg; agg.type = "avg"; agg.value = NullableField<nlohmann::json>::value(nlohmann::json(72.0)); agg.outcome = std::string("FAIL"); agg.validators = {v};
    RunCreateMeasurements m; m.name = "agg_decisive"; m.outcome = ValidatorsOutcome::Pass; m.measured_value = nlohmann::json(72.0); m.aggregations = {agg};
    auto created = client().runs().create().serial_number("SN-AVID-" + uid_val).procedure_id(procedure_id()).part_number("PART-AVID-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({make_agg_phase("agg_phase", m)}).send();
    ASSERT_FALSE(created.id.empty());
}
