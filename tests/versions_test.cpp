#include "common.hpp"
using namespace test;
using namespace tofupilot;

namespace {
std::string create_procedure(const std::string& uid_val) {
    return client().procedures().create().name("Proc Ver " + uid_val).send().id;
}
}

TEST(Versions, CreateReturnsId) {
    auto uid_val = uid();
    auto proc_id = create_procedure(uid_val);
    ASSERT_FALSE(client().versions().create().procedure_id(proc_id).tag("v" + uid_val).send().id.empty());
}

TEST(Versions, GetReturnsMatchingData) {
    auto uid_val = uid();
    auto proc_id = create_procedure(uid_val);
    auto tag = "v-g-" + uid_val;
    auto created = client().versions().create().procedure_id(proc_id).tag(tag).send();
    auto fetched = client().versions().get().procedure_id(proc_id).tag(tag).send();
    EXPECT_EQ(created.id, fetched.id);
    EXPECT_EQ(tag, fetched.tag);
}

TEST(Versions, GetNonexistentReturnsNotFound) {
    auto uid_val = uid();
    auto proc_id = create_procedure(uid_val);
    EXPECT_THROW(client().versions().get().procedure_id(proc_id).tag("v-none-" + uid()).send(), NotFoundError);
}

TEST(Versions, DeleteReturnsId) {
    auto uid_val = uid();
    auto proc_id = create_procedure(uid_val);
    auto tag = "v-d-" + uid_val;
    auto created = client().versions().create().procedure_id(proc_id).tag(tag).send();
    auto deleted = client().versions().delete_().procedure_id(proc_id).tag(tag).send();
    EXPECT_EQ(created.id, deleted.id);
}

TEST(Versions, DeleteNonexistentReturnsNotFound) {
    auto uid_val = uid();
    auto proc_id = create_procedure(uid_val);
    EXPECT_THROW(client().versions().delete_().procedure_id(proc_id).tag("v-none-" + uid()).send(), NotFoundError);
}
