#include "common.hpp"
using namespace test;
using namespace tofupilot;

TEST(Users, ListReturnsData) { ASSERT_FALSE(client().users().list().send().empty()); }

TEST(Users, GetCurrentUser) {
    auto me = client().users().get_current().send();
    ASSERT_FALSE(me.id.empty());
    ASSERT_FALSE(me.email.empty());
}
