#include "common.hpp"
using namespace test;
using namespace tofupilot;

TEST(RunsDelete, ReturnsIds) {
    auto created = create_test_run(uid());
    auto deleted = client().runs().delete_().ids({created.id}).send();
    ASSERT_FALSE(deleted.id.empty());
}

TEST(RunsDelete, DeleteMultipleReturnsIds) {
    auto run1 = create_test_run(uid());
    auto run2 = create_test_run(uid());
    auto deleted = client().runs().delete_().ids({run1.id, run2.id}).send();
    EXPECT_EQ(2, deleted.id.size());
}

TEST(RunsDelete, NonexistentReturnsNotFound) {
    EXPECT_THROW(client().runs().delete_().ids({"550e8400-e29b-41d4-a716-446655440000"}).send(), NotFoundError);
}
