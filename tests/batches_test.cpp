#include "common.hpp"
using namespace test;
using namespace tofupilot;

namespace {
std::string create_batch_via_run(const std::string& uid_val) {
    auto batch_number = "BATCH-" + uid_val;
    auto ts = iso_now();
    client().runs().create()
        .serial_number("SN-B-" + uid_val)
        .procedure_id(procedure_id())
        .part_number("PART-B-" + uid_val)
        .batch_number(batch_number)
        .started_at(ts)
        .ended_at(ts)
        .outcome(Outcome::Pass)
        .send();
    return batch_number;
}
}

TEST(Batches, CreateReturnsId) {
    ASSERT_FALSE(client().batches().create().number("BATCH-CRE-" + uid()).send().id.empty());
}

TEST(Batches, GetReturnsMatchingData) {
    auto uid_val = uid();
    auto batch_number = create_batch_via_run(uid_val);
    auto fetched = client().batches().get().number(batch_number).send();
    EXPECT_EQ(batch_number, fetched.number);
}

TEST(Batches, GetNonexistentReturnsNotFound) {
    EXPECT_THROW(client().batches().get().number("NONEXISTENT-" + uid()).send(), NotFoundError);
}

TEST(Batches, ListReturnsList) {
    create_batch_via_run(uid());
    ASSERT_FALSE(client().batches().list().send().data.empty());
}

TEST(Batches, ListWithSearchQuery) {
    auto uid_val = uid();
    auto batch_number = create_batch_via_run(uid_val);
    auto result = client().batches().list().search_query(batch_number).send();
    ASSERT_FALSE(result.data.empty());
}

TEST(Batches, ListWithNumberFilter) {
    auto uid_val = uid();
    auto batch_number = create_batch_via_run(uid_val);
    auto result = client().batches().list().numbers({batch_number}).send();
    ASSERT_FALSE(result.data.empty());
    EXPECT_EQ(batch_number, result.data[0].number);
}

TEST(Batches, ListPagination) {
    for (int i = 0; i < 3; ++i) create_batch_via_run(uid());
    auto page1 = client().batches().list().limit(1).send();
    EXPECT_EQ(1, page1.data.size());
    ASSERT_TRUE(page1.meta.has_more);
    auto page2 = client().batches().list().limit(1).cursor(page1.meta.next_cursor.value()).send();
    EXPECT_EQ(1, page2.data.size());
    EXPECT_NE(page1.data[0].id, page2.data[0].id);
}

TEST(Batches, ListSortOrder) {
    for (int i = 0; i < 2; ++i) create_batch_via_run(uid());
    auto desc = client().batches().list().sort_order(ListSortOrder::Desc).limit(2).send();
    auto asc = client().batches().list().sort_order(ListSortOrder::Asc).limit(2).send();
    if (desc.data.size() >= 2 && asc.data.size() >= 2) {
        EXPECT_GE(desc.data[0].created_at, desc.data[1].created_at);
        EXPECT_LE(asc.data[0].created_at, asc.data[1].created_at);
    }
}

TEST(Batches, DeleteReturnsId) {
    auto uid_val = uid();
    auto number = "BATCH-DEL-" + uid_val;
    auto created = client().batches().create().number(number).send();
    auto deleted = client().batches().delete_().number(number).send();
    EXPECT_FALSE(deleted.id.empty());
}

TEST(Batches, DeleteNonexistentReturnsNotFound) {
    EXPECT_THROW(client().batches().delete_().number("NONEXISTENT-" + uid()).send(), NotFoundError);
}

TEST(Batches, UpdateNumber) {
    auto uid_val = uid();
    auto old_number = "BATCH-UPOLD-" + uid_val;
    auto new_number = "BATCH-UPNEW-" + uid_val;
    client().batches().create().number(old_number).send();
    client().batches().update().number(old_number).new_number(new_number).send();
    auto fetched = client().batches().get().number(new_number).send();
    EXPECT_EQ(new_number, fetched.number);
    EXPECT_THROW(client().batches().get().number(old_number).send(), NotFoundError);
}

TEST(Batches, UpdateDuplicateNumberReturnsConflict) {
    auto uid_val = uid();
    auto number1 = "BATCH-DUP1-" + uid_val;
    auto number2 = "BATCH-DUP2-" + uid_val;
    client().batches().create().number(number1).send();
    client().batches().create().number(number2).send();
    EXPECT_THROW(client().batches().update().number(number2).new_number(number1).send(), ConflictError);
}

TEST(Batches, CreateEmptyNumberFails) {
    EXPECT_ANY_THROW(client().batches().create().number("").send());
}
