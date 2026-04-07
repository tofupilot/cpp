#include "common.hpp"
using namespace test;
using namespace tofupilot;

namespace {
struct PartAndUnit { std::string part_number, serial; };
PartAndUnit create_part_and_unit(const std::string& prefix) {
    auto uid_val = uid(); auto pn = "PART-" + prefix + "-" + uid_val; auto sn = "SN-" + prefix + "-" + uid_val; auto rn = "REV-" + prefix + "-" + uid_val;
    client().parts().create().number(pn).name("Part " + uid_val).send();
    client().revisions().create().part_number(pn).number(rn).send();
    client().units().create().serial_number(sn).part_number(pn).revision_number(rn).send();
    return {pn, sn};
}
}

TEST(Units, CreateReturnsId) {
    auto uid_val = uid(); auto pn = "PART-CRE-" + uid_val; auto rn = "REV-CRE-" + uid_val;
    client().parts().create().number(pn).name("Part " + uid_val).send();
    client().revisions().create().part_number(pn).number(rn).send();
    ASSERT_FALSE(client().units().create().serial_number("SN-CRE-" + uid_val).part_number(pn).revision_number(rn).send().id.empty());
}

TEST(Units, GetReturnsMatchingData) {
    auto [pn, sn] = create_part_and_unit("GET");
    auto fetched = client().units().get().serial_number(sn).send();
    EXPECT_EQ(sn, fetched.serial_number);
    EXPECT_EQ(pn, fetched.part.number);
}

TEST(Units, GetNonexistentReturnsNotFound) {
    EXPECT_THROW(client().units().get().serial_number("NONEXISTENT-" + uid()).send(), NotFoundError);
}

TEST(Units, ListReturnsList) { create_part_and_unit("LST"); ASSERT_FALSE(client().units().list().send().data.empty()); }

TEST(Units, ListFilterBySerialNumber) {
    auto [_, serial] = create_part_and_unit("FSN");
    auto result = client().units().list().serial_numbers({serial}).send();
    EXPECT_EQ(1, result.data.size());
    EXPECT_EQ(serial, result.data[0].serial_number);
}

TEST(Units, ListFilterByPartNumber) {
    auto [part_number, _] = create_part_and_unit("FPN");
    auto result = client().units().list().part_numbers({part_number}).send();
    ASSERT_FALSE(result.data.empty());
    for (const auto& u : result.data) EXPECT_EQ(part_number, u.part.number);
}

TEST(Units, ListPagination) {
    for (int i = 0; i < 3; ++i) create_part_and_unit("PAG" + std::to_string(i));
    auto page1 = client().units().list().limit(1).send();
    EXPECT_EQ(1, page1.data.size());
    ASSERT_TRUE(page1.meta.has_more);
    auto page2 = client().units().list().limit(1).cursor(page1.meta.next_cursor.value()).send();
    EXPECT_EQ(1, page2.data.size());
    EXPECT_NE(page1.data[0].id, page2.data[0].id);
}

TEST(Units, DeleteReturnsIds) {
    auto [_, sn] = create_part_and_unit("DEL");
    ASSERT_FALSE(client().units().delete_().serial_numbers({sn}).send().id.empty());
}

TEST(Units, DeleteNonexistentReturnsNotFound) {
    EXPECT_THROW(client().units().delete_().serial_numbers({"NONEXISTENT-" + uid()}).send(), NotFoundError);
}

TEST(Units, UpdateSerialNumber) {
    auto [_, serial] = create_part_and_unit("UPD");
    auto new_serial = "SN-UPNEW-" + uid();
    client().units().update().serial_number(serial).new_serial_number(new_serial).send();
    auto fetched = client().units().get().serial_number(new_serial).send();
    EXPECT_EQ(new_serial, fetched.serial_number);
}

TEST(Units, ListWithSearchQuery) {
    auto [_, serial] = create_part_and_unit("SRQ");
    auto result = client().units().list().search_query(serial).send();
    ASSERT_FALSE(result.data.empty());
    bool found = false;
    for (const auto& u : result.data) if (u.serial_number == serial) found = true;
    EXPECT_TRUE(found);
}

TEST(Units, ListSortOrder) {
    for (int i = 0; i < 2; ++i) create_part_and_unit("SRT" + std::to_string(i));
    auto desc = client().units().list().sort_order(ListSortOrder::Desc).limit(2).send();
    auto asc = client().units().list().sort_order(ListSortOrder::Asc).limit(2).send();
    if (desc.data.size() >= 2 && asc.data.size() >= 2) {
        EXPECT_GE(desc.data[0].created_at, desc.data[1].created_at);
        EXPECT_LE(asc.data[0].created_at, asc.data[1].created_at);
    }
}

TEST(Units, ListFilterByIds) {
    auto [_, serial] = create_part_and_unit("FID");
    auto unit = client().units().get().serial_number(serial).send();
    auto result = client().units().list().ids({unit.id}).send();
    EXPECT_EQ(1, result.data.size());
    EXPECT_EQ(unit.id, result.data[0].id);
}

TEST(Units, UpdatePartRevision) {
    auto uid_val = uid();
    auto [_, serial] = create_part_and_unit("UPR");
    auto new_part = "PART-UPRNEW-" + uid_val;
    auto new_rev = "REV-UPRNEW-" + uid_val;
    client().parts().create().number(new_part).name("New Part " + uid_val).send();
    client().revisions().create().part_number(new_part).number(new_rev).send();
    client().units().update().serial_number(serial).part_number(new_part).revision_number(new_rev).send();
    auto fetched = client().units().get().serial_number(serial).send();
    EXPECT_EQ(new_part, fetched.part.number);
}

TEST(Units, UpdateDuplicateSerialReturnsConflict) {
    auto [_, serial1] = create_part_and_unit("DUS1");
    auto [_2, serial2] = create_part_and_unit("DUS2");
    EXPECT_THROW(client().units().update().serial_number(serial2).new_serial_number(serial1).send(), ConflictError);
}

TEST(Units, CreateDuplicateSerialReturnsConflict) {
    auto [part_number, serial] = create_part_and_unit("DUCS");
    auto rev = "REV-DUCS2-" + uid();
    client().revisions().create().part_number(part_number).number(rev).send();
    EXPECT_THROW(client().units().create().serial_number(serial).part_number(part_number).revision_number(rev).send(), ConflictError);
}

TEST(Units, ListFilterByRevisionNumbers) {
    auto uid_val = uid();
    auto pn = "PART-RV-" + uid_val;
    auto rn = "REV-RV-" + uid_val;
    auto sn = "SN-RV-" + uid_val;
    client().parts().create().number(pn).name("Part " + uid_val).send();
    client().revisions().create().part_number(pn).number(rn).send();
    client().units().create().serial_number(sn).part_number(pn).revision_number(rn).send();
    auto result = client().units().list().part_numbers({pn}).revision_numbers({rn}).send();
    ASSERT_FALSE(result.data.empty());
    for (const auto& u : result.data) EXPECT_EQ(pn, u.part.number);
}

TEST(Units, ListFilterByBatchNumbers) {
    auto uid_val = uid();
    auto pn = "PART-BN-" + uid_val;
    auto rn = "REV-BN-" + uid_val;
    auto batch = "BATCH-" + uid_val;
    auto ts = iso_now();
    client().parts().create().number(pn).name("Part " + uid_val).send();
    client().revisions().create().part_number(pn).number(rn).send();
    // Create a run with batch_number to auto-create the batch and link the unit
    client().runs().create().serial_number("SN-BN-" + uid_val).procedure_id(procedure_id()).part_number(pn).revision_number(rn).batch_number(batch).started_at(ts).ended_at(ts).outcome(Outcome::Pass).send();
    auto result = client().units().list().part_numbers({pn}).batch_numbers({batch}).send();
    ASSERT_FALSE(result.data.empty());
}

TEST(Units, ListFilterByCreatedAt) {
    auto before = iso_now(-2);
    auto [pn, _] = create_part_and_unit("CA");
    auto after = iso_now(2);
    auto result = client().units().list().part_numbers({pn}).created_after(before).created_before(after).send();
    ASSERT_FALSE(result.data.empty());
}
