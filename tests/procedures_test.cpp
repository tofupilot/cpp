#include "common.hpp"
using namespace test;
using namespace tofupilot;

TEST(Procedures, CreateReturnsId) { ASSERT_FALSE(client().procedures().create().name("Proc " + uid()).send().id.empty()); }

TEST(Procedures, GetReturnsMatchingData) {
    auto name = "Proc Get " + uid();
    auto created = client().procedures().create().name(name).send();
    auto fetched = client().procedures().get().id(created.id).send();
    EXPECT_EQ(name, fetched.name);
}

TEST(Procedures, GetNonexistentReturnsNotFound) {
    EXPECT_THROW(client().procedures().get().id("550e8400-e29b-41d4-a716-446655440000").send(), NotFoundError);
}

TEST(Procedures, ListReturnsList) { ASSERT_FALSE(client().procedures().list().send().data.empty()); }

TEST(Procedures, DeleteReturnsId) {
    auto created = client().procedures().create().name("Proc Del " + uid()).send();
    EXPECT_EQ(created.id, client().procedures().delete_().id(created.id).send().id);
}

TEST(Procedures, ListWithSearchQuery) {
    auto name = "Proc Srq " + uid();
    client().procedures().create().name(name).send();
    auto result = client().procedures().list().search_query(name).send();
    ASSERT_FALSE(result.data.empty());
}

TEST(Procedures, ListPagination) {
    for (int i = 0; i < 3; ++i) client().procedures().create().name("Proc Pg " + uid()).send();
    auto page1 = client().procedures().list().limit(1).send();
    EXPECT_EQ(1, page1.data.size());
    if (page1.meta.has_more) {
        auto page2 = client().procedures().list().limit(1).cursor(page1.meta.next_cursor.value()).send();
        EXPECT_EQ(1, page2.data.size());
        EXPECT_NE(page1.data[0].id, page2.data[0].id);
    }
}

TEST(Procedures, DeleteNonexistentReturnsNotFound) {
    EXPECT_THROW(client().procedures().delete_().id("550e8400-e29b-41d4-a716-446655440000").send(), NotFoundError);
}

TEST(Procedures, UpdateName) {
    auto uid_val = uid();
    auto created = client().procedures().create().name("Proc Old " + uid_val).send();
    auto new_name = "Proc New " + uid_val;
    client().procedures().update().id(created.id).name(new_name).send();
    EXPECT_EQ(new_name, client().procedures().get().id(created.id).send().name);
}

TEST(Procedures, GetIncludesRecentRuns) {
    auto uid_val = uid();
    auto proc = client().procedures().create().name("Proc RR " + uid_val).send();
    auto ts = iso_now();
    client().runs().create().serial_number("SN-RR-" + uid_val).procedure_id(proc.id).part_number("PART-RR-" + uid_val).started_at(ts).ended_at(ts).outcome(Outcome::Pass).send();
    auto fetched = client().procedures().get().id(proc.id).send();
    ASSERT_FALSE(fetched.recent_runs.empty());
}

TEST(Procedures, ListWithDateRange) {
    auto before = iso_now(-2);
    client().procedures().create().name("Proc DR " + uid()).send();
    auto after = iso_now(2);
    auto result = client().procedures().list().created_after(before).created_before(after).send();
    ASSERT_FALSE(result.data.empty());
}

TEST(Procedures, UpdateEmptyNameFails) {
    auto created = client().procedures().create().name("Proc EN " + uid()).send();
    EXPECT_ANY_THROW(client().procedures().update().id(created.id).name("").send());
}

TEST(Procedures, UpdateNonexistentReturnsNotFound) {
    EXPECT_THROW(client().procedures().update().id("550e8400-e29b-41d4-a716-446655440000").name("irrelevant").send(), NotFoundError);
}

TEST(Procedures, UpdateMultipleUpdates) {
    auto uid_val = uid();
    auto created = client().procedures().create().name("Proc MU " + uid_val).send();
    for (int i = 1; i <= 3; ++i)
        client().procedures().update().id(created.id).name("Proc MU " + uid_val + " v" + std::to_string(i)).send();
    auto fetched = client().procedures().get().id(created.id).send();
    EXPECT_TRUE(fetched.name.find("v3") != std::string::npos);
}
