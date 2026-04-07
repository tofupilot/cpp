#include "common.hpp"
using namespace test;
using namespace tofupilot;

namespace {
std::pair<std::string, std::string> create_station(const std::string& uid_val) {
    auto name = "Station-" + uid_val;
    auto created = client().stations().create().name(name).procedure_id(procedure_id()).send();
    return {created.id, name};
}
}

TEST(Stations, CreateReturnsId) {
    auto [id, _] = create_station(uid());
    ASSERT_FALSE(id.empty());
}

TEST(Stations, GetReturnsMatchingData) {
    auto uid_val = uid();
    auto [id, name] = create_station(uid_val);
    auto fetched = client().stations().get().id(id).send();
    EXPECT_EQ(id, fetched.id);
    EXPECT_EQ(name, fetched.name);
}

TEST(Stations, GetNonexistentReturnsNotFound) {
    EXPECT_THROW(client().stations().get().id("550e8400-e29b-41d4-a716-446655440000").send(), NotFoundError);
}

TEST(Stations, ListReturnsList) {
    create_station(uid());
    ASSERT_FALSE(client().stations().list().send().data.empty());
}

TEST(Stations, ListWithSearchQuery) {
    auto uid_val = uid();
    auto [_, name] = create_station(uid_val);
    auto result = client().stations().list().search_query(name).send();
    ASSERT_FALSE(result.data.empty());
    bool found = false;
    for (const auto& s : result.data) if (s.name == name) found = true;
    EXPECT_TRUE(found);
}

TEST(Stations, ListPagination) {
    for (int i = 0; i < 3; ++i) create_station(uid());
    auto page1 = client().stations().list().limit(1).send();
    EXPECT_EQ(1, page1.data.size());
    ASSERT_TRUE(page1.meta.has_more);
    auto page2 = client().stations().list().limit(1).cursor(page1.meta.next_cursor.value()).send();
    EXPECT_EQ(1, page2.data.size());
    EXPECT_NE(page1.data[0].id, page2.data[0].id);
}

TEST(Stations, RemoveReturnsId) {
    auto [id, _] = create_station(uid());
    auto removed = client().stations().remove().id(id).send();
    EXPECT_EQ(id, removed.id);
}

TEST(Stations, RemoveNonexistentReturnsNotFound) {
    EXPECT_THROW(client().stations().remove().id("550e8400-e29b-41d4-a716-446655440000").send(), NotFoundError);
}

TEST(Stations, RemoveTwiceFails) {
    auto [id, _] = create_station(uid());
    client().stations().remove().id(id).send();
    EXPECT_THROW(client().stations().remove().id(id).send(), NotFoundError);
}

TEST(Stations, UpdateName) {
    auto uid_val = uid();
    auto [id, _] = create_station(uid_val);
    auto new_name = "Station-Updated-" + uid_val;
    client().stations().update().id(id).name(new_name).send();
    auto fetched = client().stations().get().id(id).send();
    EXPECT_EQ(new_name, fetched.name);
}

TEST(Stations, UpdateNonexistentReturnsNotFound) {
    EXPECT_THROW(client().stations().update().id("550e8400-e29b-41d4-a716-446655440000").name("irrelevant").send(), NotFoundError);
}

TEST(Stations, CreateDuplicateNameReturnsConflict) {
    auto uid_val = uid();
    auto [_, name] = create_station(uid_val);
    EXPECT_THROW(client().stations().create().name(name).procedure_id(procedure_id()).send(), ConflictError);
}

TEST(Stations, GetCurrentWithUserKeyReturnsForbidden) {
    EXPECT_THROW(client().stations().get_current().send(), ForbiddenError);
}
