#include "common.hpp"
using namespace test;
using namespace tofupilot;

TEST(RunsList, ReturnsData) {
    auto uid_val = uid(); create_test_run(uid_val);
    ASSERT_FALSE(client().runs().list().part_numbers({"PART-" + uid_val}).send().data.empty());
}

TEST(RunsList, Pagination) {
    auto uid_val = uid(); auto part = "PART-PG-" + uid_val;
    for (int i = 0; i < 3; ++i) { auto ts = iso_now(); client().runs().create().serial_number("SN-PG-" + std::to_string(i) + "-" + uid_val).procedure_id(procedure_id()).part_number(part).outcome(Outcome::Pass).started_at(ts).ended_at(ts).send(); }
    auto page1 = client().runs().list().part_numbers({part}).limit(1).send();
    EXPECT_EQ(1, page1.data.size());
    ASSERT_TRUE(page1.meta.has_more);
    auto page2 = client().runs().list().part_numbers({part}).limit(1).cursor(page1.meta.next_cursor.value()).send();
    EXPECT_NE(page1.data[0].id, page2.data[0].id);
}

TEST(RunsList, FilterByOutcome) {
    auto uid_val = uid();
    auto ts = iso_now();
    auto part = "PART-OUT-" + uid_val;
    auto pass_run = client().runs().create().serial_number("SN-P-" + uid_val).procedure_id(procedure_id()).part_number(part).started_at(ts).ended_at(ts).outcome(Outcome::Pass).send();
    client().runs().create().serial_number("SN-F-" + uid_val).procedure_id(procedure_id()).part_number(part).started_at(ts).ended_at(ts).outcome(Outcome::Fail).send();
    auto result = client().runs().list().outcomes({Outcome::Pass}).part_numbers({part}).send();
    ASSERT_FALSE(result.data.empty());
    for (const auto& r : result.data) EXPECT_EQ(Outcome::Pass, r.outcome);
}

TEST(RunsList, FilterBySerialNumber) {
    auto uid_val = uid();
    auto serial = "SN-FILT-" + uid_val;
    auto ts = iso_now();
    client().runs().create().serial_number(serial).procedure_id(procedure_id()).part_number("PART-" + uid_val).started_at(ts).ended_at(ts).outcome(Outcome::Pass).send();
    auto result = client().runs().list().serial_numbers({serial}).send();
    ASSERT_FALSE(result.data.empty());
}

TEST(RunsList, FilterByProcedureId) {
    auto uid_val = uid();
    auto proc = client().procedures().create().name("Proc FPI " + uid_val).send();
    auto ts = iso_now();
    client().runs().create().serial_number("SN-FPI-" + uid_val).procedure_id(proc.id).part_number("PART-FPI-" + uid_val).started_at(ts).ended_at(ts).outcome(Outcome::Pass).send();
    auto result = client().runs().list().procedure_ids({proc.id}).send();
    ASSERT_FALSE(result.data.empty());
    for (const auto& r : result.data) EXPECT_EQ(proc.id, r.procedure.id);
}

TEST(RunsList, FilterByPartNumber) {
    auto uid_val = uid();
    create_test_run(uid_val);
    auto result = client().runs().list().part_numbers({"PART-" + uid_val}).send();
    ASSERT_FALSE(result.data.empty());
}

TEST(RunsList, FilterByDateRange) {
    auto uid_val = uid();
    auto before = iso_now(-2);
    create_test_run(uid_val);
    auto after = iso_now(2);
    auto result = client().runs().list().part_numbers({"PART-" + uid_val}).created_after(before).created_before(after).send();
    ASSERT_FALSE(result.data.empty());
}

TEST(RunsList, SortOrder) {
    auto uid_val = uid();
    auto part = "PART-SORT-" + uid_val;
    auto ts = iso_now();
    for (int i = 0; i < 2; ++i)
        client().runs().create().serial_number("SN-SORT-" + std::to_string(i) + "-" + uid_val).procedure_id(procedure_id()).part_number(part).started_at(ts).ended_at(ts).outcome(Outcome::Pass).send();
    auto desc = client().runs().list().part_numbers({part}).sort_by(RunListSortBy::StartedAt).sort_order(ListSortOrder::Desc).send();
    auto asc = client().runs().list().part_numbers({part}).sort_by(RunListSortBy::StartedAt).sort_order(ListSortOrder::Asc).send();
    ASSERT_GE(desc.data.size(), 2);
    ASSERT_GE(asc.data.size(), 2);
}

TEST(RunsList, FilterByIds) {
    auto run1 = create_test_run(uid());
    auto run2 = create_test_run(uid());
    auto result = client().runs().list().ids({run1.id, run2.id}).send();
    EXPECT_EQ(2, result.data.size());
}

TEST(RunsList, EmptyResult) {
    EXPECT_TRUE(client().runs().list().serial_numbers({"NONEXISTENT-" + uid()}).send().data.empty());
}

TEST(RunsList, FilterByDurationRange) {
    auto uid_val = uid();
    auto part = "PART-DUR-" + uid_val;
    auto started = iso_now(-300);
    auto ended = iso_now(-180);
    client().runs().create().serial_number("SN-DUR-" + uid_val).procedure_id(procedure_id()).part_number(part).started_at(started).ended_at(ended).outcome(Outcome::Pass).send();
    auto result = client().runs().list().part_numbers({part}).duration_min("PT1M").duration_max("PT5M").send();
    ASSERT_FALSE(result.data.empty());
}

TEST(RunsList, FilterByEndedAt) {
    auto uid_val = uid();
    auto part = "PART-END-" + uid_val;
    auto before = iso_now(-600);
    auto started = iso_now(-300);
    auto ended = iso_now(-180);
    auto after = iso_now(300);
    client().runs().create().serial_number("SN-END-" + uid_val).procedure_id(procedure_id()).part_number(part).started_at(started).ended_at(ended).outcome(Outcome::Pass).send();
    auto result = client().runs().list().part_numbers({part}).ended_after(before).ended_before(after).send();
    ASSERT_FALSE(result.data.empty());
}

TEST(RunsList, FilterByCreatedAt) {
    auto uid_val = uid();
    auto part = "PART-CRT-" + uid_val;
    auto before = iso_now(-2);
    create_test_run(uid_val);
    auto after = iso_now(2);
    // create_test_run uses "PART-" prefix, so use that
    auto result = client().runs().list().part_numbers({"PART-" + uid_val}).created_after(before).created_before(after).send();
    ASSERT_FALSE(result.data.empty());
}

TEST(RunsList, FilterByRevisionNumbers) {
    auto uid_val = uid();
    auto part = "PART-REV-" + uid_val;
    auto rev = "REV-" + uid_val;
    auto ts = iso_now();
    client().parts().create().number(part).name("Part " + uid_val).send();
    client().revisions().create().part_number(part).number(rev).send();
    client().runs().create().serial_number("SN-REV-" + uid_val).procedure_id(procedure_id()).part_number(part).revision_number(rev).started_at(ts).ended_at(ts).outcome(Outcome::Pass).send();
    auto result = client().runs().list().part_numbers({part}).revision_numbers({rev}).send();
    ASSERT_FALSE(result.data.empty());
}

TEST(RunsList, FilterByProcedureVersions) {
    auto uid_val = uid();
    auto part = "PART-PV-" + uid_val;
    auto version = "1.0." + uid_val.substr(0, 4);
    auto ts = iso_now();
    client().runs().create().serial_number("SN-PV-" + uid_val).procedure_id(procedure_id()).part_number(part).procedure_version(version).started_at(ts).ended_at(ts).outcome(Outcome::Pass).send();
    auto result = client().runs().list().part_numbers({part}).procedure_versions({version}).send();
    ASSERT_FALSE(result.data.empty());
}

TEST(RunsList, FilterByBatchNumbers) {
    auto uid_val = uid();
    auto part = "PART-BN-" + uid_val;
    auto batch = "BATCH-" + uid_val;
    auto ts = iso_now();
    client().runs().create().serial_number("SN-BN-" + uid_val).procedure_id(procedure_id()).part_number(part).batch_number(batch).started_at(ts).ended_at(ts).outcome(Outcome::Pass).send();
    auto result = client().runs().list().part_numbers({part}).batch_numbers({batch}).send();
    ASSERT_FALSE(result.data.empty());
}
