#include "common.hpp"
using namespace test;
using namespace tofupilot;

namespace {
std::string create_part(const std::string& uid_val) {
    auto part_number = "PART-RV-" + uid_val;
    client().parts().create().number(part_number).name("Rev Part " + uid_val).send();
    return part_number;
}
}

TEST(Revisions, CreateReturnsId) {
    auto uid_val = uid();
    auto part_number = create_part(uid_val);
    ASSERT_FALSE(client().revisions().create().part_number(part_number).number("REV-" + uid_val).send().id.empty());
}

TEST(Revisions, GetReturnsMatchingData) {
    auto uid_val = uid();
    auto part_number = create_part(uid_val);
    auto rev_number = "REV-G-" + uid_val;
    auto created = client().revisions().create().part_number(part_number).number(rev_number).send();
    auto fetched = client().revisions().get().part_number(part_number).revision_number(rev_number).send();
    EXPECT_EQ(created.id, fetched.id);
    EXPECT_EQ(rev_number, fetched.number);
}

TEST(Revisions, GetNonexistentReturnsNotFound) {
    auto uid_val = uid();
    auto part_number = create_part(uid_val);
    EXPECT_THROW(client().revisions().get().part_number(part_number).revision_number("REV-NONE-" + uid()).send(), NotFoundError);
}

TEST(Revisions, DeleteReturnsId) {
    auto uid_val = uid();
    auto part_number = create_part(uid_val);
    auto rev_number = "REV-D-" + uid_val;
    auto created = client().revisions().create().part_number(part_number).number(rev_number).send();
    auto deleted = client().revisions().delete_().part_number(part_number).revision_number(rev_number).send();
    EXPECT_EQ(created.id, deleted.id);
}

TEST(Revisions, DeleteNonexistentReturnsNotFound) {
    auto uid_val = uid();
    auto part_number = create_part(uid_val);
    EXPECT_THROW(client().revisions().delete_().part_number(part_number).revision_number("REV-NONE-" + uid()).send(), NotFoundError);
}

TEST(Revisions, CreateDuplicateOnSamePartReturnsConflict) {
    auto uid_val = uid();
    auto part_number = create_part(uid_val);
    auto rev_number = "REV-DUP-" + uid_val;
    client().revisions().create().part_number(part_number).number(rev_number).send();
    EXPECT_THROW(client().revisions().create().part_number(part_number).number(rev_number).send(), ConflictError);
}

TEST(Revisions, CreateSameNumberDifferentPartsSucceeds) {
    auto uid_val = uid();
    auto rev_number = "REV-SHARED-" + uid_val;
    auto part1 = create_part(uid_val + "a");
    auto part2 = create_part(uid_val + "b");
    auto rev1 = client().revisions().create().part_number(part1).number(rev_number).send();
    auto rev2 = client().revisions().create().part_number(part2).number(rev_number).send();
    ASSERT_FALSE(rev1.id.empty());
    ASSERT_FALSE(rev2.id.empty());
    EXPECT_NE(rev1.id, rev2.id);
}

TEST(Revisions, CreateInvalidPartNumberReturnsNotFound) {
    EXPECT_THROW(client().revisions().create().part_number("PART-INVALID-" + uid()).number("REV-" + uid()).send(), NotFoundError);
}
