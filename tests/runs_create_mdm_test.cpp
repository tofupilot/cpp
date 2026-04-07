#include "common.hpp"
using namespace test;
using namespace tofupilot;

TEST(RunsCreateMdm, BasicXAxisYAxis) {
    auto uid_val = uid(); auto ts = iso_now();
    RunCreateXAxis x; x.data = {100, 1000, 10000}; x.units = std::string("Hz");
    RunCreateYAxis y; y.data = {-3.0, 0.0, -6.0}; y.units = std::string("dB"); y.description = std::string("Gain");
    RunCreateMeasurements m; m.name = "frequency_response"; m.outcome = ValidatorsOutcome::Pass; m.x_axis = x; m.y_axis = {y};
    RunCreatePhases p; p.name = "mdm_basic"; p.outcome = PhasesOutcome::Pass; p.started_at = ts; p.ended_at = ts; p.measurements = {m};
    auto created = client().runs().create().serial_number("SN-MDM1-" + uid_val).procedure_id(procedure_id()).part_number("PART-MDM1-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({p}).send();
    auto fetched = client().runs().get().id(created.id).send();
    ASSERT_TRUE(fetched.phases.has_value());
    auto& meas = fetched.phases.value()[0].measurements[0];
    ASSERT_TRUE(meas.data_series.has_value());
    EXPECT_GE(meas.data_series.value().size(), 1);
}

TEST(RunsCreateMdm, MultipleYAxisSeries) {
    auto uid_val = uid(); auto ts = iso_now();
    RunCreateXAxis x; x.data = {0, 1, 2, 3, 4, 5}; x.units = std::string("V"); x.description = std::string("Voltage");
    RunCreateYAxis y1; y1.data = {0, 0.1, 0.2, 0.3, 0.4, 0.5}; y1.units = std::string("A"); y1.description = std::string("Current");
    RunCreateYAxis y2; y2.data = {0, 0.1, 0.4, 0.9, 1.6, 2.5}; y2.units = std::string("W"); y2.description = std::string("Power");
    RunCreateMeasurements m; m.name = "iv_curve"; m.outcome = ValidatorsOutcome::Pass; m.x_axis = x; m.y_axis = {y1, y2};
    RunCreatePhases p; p.name = "multi_y"; p.outcome = PhasesOutcome::Pass; p.started_at = ts; p.ended_at = ts; p.measurements = {m};
    auto created = client().runs().create().serial_number("SN-MDM2-" + uid_val).procedure_id(procedure_id()).part_number("PART-MDM2-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({p}).send();
    auto fetched = client().runs().get().id(created.id).send();
    auto& meas = fetched.phases.value()[0].measurements[0];
    ASSERT_TRUE(meas.data_series.has_value());
    EXPECT_GE(meas.data_series.value().size(), 2);
}

TEST(RunsCreateMdm, YAxisWithValidators) {
    auto uid_val = uid(); auto ts = iso_now();
    RunCreateYAxisValidators v1; v1.operator_ = std::string(">="); v1.expected_value = nlohmann::json(2.5); v1.outcome = std::string("PASS");
    RunCreateYAxisValidators v2; v2.operator_ = std::string("<="); v2.expected_value = nlohmann::json(4.0); v2.outcome = std::string("PASS");
    RunCreateXAxis x; x.data = {1, 2, 3}; x.units = std::string("s");
    RunCreateYAxis y; y.data = {3.0, 3.3, 3.1}; y.units = std::string("V"); y.description = std::string("Voltage"); y.validators = {v1, v2};
    RunCreateMeasurements m; m.name = "output_signal"; m.outcome = ValidatorsOutcome::Pass; m.x_axis = x; m.y_axis = {y};
    RunCreatePhases p; p.name = "y_validators"; p.outcome = PhasesOutcome::Pass; p.started_at = ts; p.ended_at = ts; p.measurements = {m};
    auto created = client().runs().create().serial_number("SN-MDM3-" + uid_val).procedure_id(procedure_id()).part_number("PART-MDM3-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({p}).send();
    auto fetched = client().runs().get().id(created.id).send();
    ASSERT_TRUE(fetched.phases.value()[0].measurements[0].data_series.has_value());
}

TEST(RunsCreateMdm, YAxisWithAggregations) {
    auto uid_val = uid(); auto ts = iso_now();
    RunCreateYAxisAggregations a1; a1.type = "avg"; a1.value = NullableField<nlohmann::json>::value(nlohmann::json(23.3)); a1.outcome = std::string("PASS");
    RunCreateYAxisAggregations a2; a2.type = "max"; a2.value = NullableField<nlohmann::json>::value(nlohmann::json(24.0));
    RunCreateXAxis x; x.data = {0, 10, 20, 30, 40}; x.units = std::string("min");
    RunCreateYAxis y; y.data = {22.0, 23.5, 24.0, 23.8, 23.2}; y.units = std::string("C"); y.description = std::string("Temperature"); y.aggregations = {a1, a2};
    RunCreateMeasurements m; m.name = "temperature_sweep"; m.outcome = ValidatorsOutcome::Pass; m.x_axis = x; m.y_axis = {y};
    RunCreatePhases p; p.name = "y_aggs"; p.outcome = PhasesOutcome::Pass; p.started_at = ts; p.ended_at = ts; p.measurements = {m};
    auto created = client().runs().create().serial_number("SN-MDM4-" + uid_val).procedure_id(procedure_id()).part_number("PART-MDM4-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({p}).send();
    auto fetched = client().runs().get().id(created.id).send();
    ASSERT_TRUE(fetched.phases.value()[0].measurements[0].data_series.has_value());
}

TEST(RunsCreateMdm, YAxisAggregationsWithValidators) {
    auto uid_val = uid(); auto ts = iso_now();
    RunCreateYAxisAggregationsValidators v; v.operator_ = std::string(">="); v.expected_value = nlohmann::json(90.0); v.outcome = std::string("PASS");
    RunCreateYAxisAggregations agg; agg.type = "avg"; agg.value = NullableField<nlohmann::json>::value(nlohmann::json(95.17)); agg.outcome = std::string("PASS"); agg.validators = {v};
    RunCreateXAxis x; x.data = {1, 2, 3}; x.units = std::string("s");
    RunCreateYAxis y; y.data = {95.0, 96.0, 94.5}; y.units = std::string("%"); y.description = std::string("Quality"); y.aggregations = {agg};
    RunCreateMeasurements m; m.name = "signal_quality"; m.outcome = ValidatorsOutcome::Pass; m.x_axis = x; m.y_axis = {y};
    RunCreatePhases p; p.name = "y_agg_val"; p.outcome = PhasesOutcome::Pass; p.started_at = ts; p.ended_at = ts; p.measurements = {m};
    auto created = client().runs().create().serial_number("SN-MDM5-" + uid_val).procedure_id(procedure_id()).part_number("PART-MDM5-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({p}).send();
    ASSERT_FALSE(created.id.empty());
}

TEST(RunsCreateMdm, XAxisWithValidators) {
    auto uid_val = uid(); auto ts = iso_now();
    RunCreateValidators xv; xv.operator_ = std::string(">="); xv.expected_value = nlohmann::json(0); xv.outcome = std::string("PASS");
    RunCreateXAxis x; x.data = {0, 1, 2, 3}; x.units = std::string("s"); x.validators = {xv};
    RunCreateYAxis y; y.data = {10, 20, 30, 40}; y.units = std::string("mV");
    RunCreateMeasurements m; m.name = "time_series"; m.outcome = ValidatorsOutcome::Pass; m.x_axis = x; m.y_axis = {y};
    RunCreatePhases p; p.name = "x_validators"; p.outcome = PhasesOutcome::Pass; p.started_at = ts; p.ended_at = ts; p.measurements = {m};
    auto created = client().runs().create().serial_number("SN-MDM6-" + uid_val).procedure_id(procedure_id()).part_number("PART-MDM6-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({p}).send();
    ASSERT_FALSE(created.id.empty());
}

TEST(RunsCreateMdm, XAxisWithAggregations) {
    auto uid_val = uid(); auto ts = iso_now();
    RunCreateAggregations xa; xa.type = "max"; xa.value = NullableField<nlohmann::json>::value(nlohmann::json(2.0));
    RunCreateXAxis x; x.data = {0, 0.5, 1.0, 1.5, 2.0}; x.units = std::string("s"); x.aggregations = {xa};
    RunCreateYAxis y; y.data = {1, 2, 3, 4, 5}; y.units = std::string("V");
    RunCreateMeasurements m; m.name = "sampling"; m.outcome = ValidatorsOutcome::Pass; m.x_axis = x; m.y_axis = {y};
    RunCreatePhases p; p.name = "x_aggs"; p.outcome = PhasesOutcome::Pass; p.started_at = ts; p.ended_at = ts; p.measurements = {m};
    auto created = client().runs().create().serial_number("SN-MDM7-" + uid_val).procedure_id(procedure_id()).part_number("PART-MDM7-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({p}).send();
    ASSERT_FALSE(created.id.empty());
}

TEST(RunsCreateMdm, Comprehensive) {
    auto uid_val = uid(); auto ts = iso_now();
    RunCreateYAxisValidators yv; yv.operator_ = std::string(">="); yv.expected_value = nlohmann::json(-6.0); yv.outcome = std::string("PASS");
    RunCreateYAxisAggregationsValidators yav; yav.operator_ = std::string(">="); yav.expected_value = nlohmann::json(-6.0); yav.outcome = std::string("PASS");
    RunCreateYAxisAggregations ya; ya.type = "min"; ya.value = NullableField<nlohmann::json>::value(nlohmann::json(-3.0)); ya.outcome = std::string("PASS"); ya.validators = {yav};
    RunCreateXAxis x; x.data = {100, 1000, 10000}; x.units = std::string("Hz"); x.description = std::string("Frequency");
    RunCreateYAxis y1; y1.data = {-1.0, 0.0, -3.0}; y1.units = std::string("dB"); y1.description = std::string("Gain"); y1.validators = {yv}; y1.aggregations = {ya};
    RunCreateYAxis y2; y2.data = {-5.0, -10.0, -45.0}; y2.units = std::string("deg"); y2.description = std::string("Phase");
    RunCreateMeasurements m; m.name = "full_sweep"; m.outcome = ValidatorsOutcome::Pass; m.x_axis = x; m.y_axis = {y1, y2};
    RunCreatePhases p; p.name = "comprehensive_mdm"; p.outcome = PhasesOutcome::Pass; p.started_at = ts; p.ended_at = ts; p.measurements = {m};
    auto created = client().runs().create().serial_number("SN-MDM8-" + uid_val).procedure_id(procedure_id()).part_number("PART-MDM8-" + uid_val).outcome(Outcome::Pass).started_at(ts).ended_at(ts).phases({p}).send();
    auto fetched = client().runs().get().id(created.id).send();
    ASSERT_TRUE(fetched.phases.has_value());
    auto& meas = fetched.phases.value()[0].measurements[0];
    ASSERT_TRUE(meas.data_series.has_value());
    EXPECT_GE(meas.data_series.value().size(), 2);
}
