#include "common.hpp"
using namespace test;
using namespace tofupilot;

TEST(RunsUpdate, ReturnsId) {
    auto created = create_test_run(uid());
    EXPECT_EQ(created.id, client().runs().update().id(created.id).send().id);
}

TEST(RunsUpdate, NonexistentReturnsNotFound) {
    EXPECT_THROW(client().runs().update().id("550e8400-e29b-41d4-a716-446655440000").send(), NotFoundError);
}
