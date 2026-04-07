#include "common.hpp"
using namespace test;
using namespace tofupilot;

TEST(Users, ListReturnsData) { ASSERT_FALSE(client().user().list().send().empty()); }

TEST(Users, ListCurrentUser) {
    auto result = client().user().list().current(true).send();
    EXPECT_EQ(1, result.size());
    ASSERT_FALSE(result[0].id.empty());
    ASSERT_FALSE(result[0].email.empty());
}
