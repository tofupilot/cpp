#include "common.hpp"
using namespace test;
using namespace tofupilot;

TEST(Parts, CreateReturnsId) {
    auto uid_val = uid();
    ASSERT_FALSE(client().parts().create().number("PART-" + uid_val).name("Part " + uid_val).send().id.empty());
}

TEST(Parts, GetReturnsMatchingData) {
    auto uid_val = uid();
    auto number = "PART-GET-" + uid_val;
    auto name = "Part Get " + uid_val;
    client().parts().create().number(number).name(name).send();
    auto fetched = client().parts().get().number(number).send();
    EXPECT_EQ(number, fetched.number);
    EXPECT_EQ(name, fetched.name);
}

TEST(Parts, GetNonexistentReturnsNotFound) {
    EXPECT_THROW(client().parts().get().number("NONEXISTENT-" + uid()).send(), NotFoundError);
}

TEST(Parts, ListReturnsList) {
    auto uid_val = uid();
    client().parts().create().number("PART-LST-" + uid_val).name("Part List " + uid_val).send();
    ASSERT_FALSE(client().parts().list().send().data.empty());
}

TEST(Parts, ListWithSearchQuery) {
    auto uid_val = uid();
    auto number = "PART-SRQ-" + uid_val;
    client().parts().create().number(number).name("Part Srq " + uid_val).send();
    auto result = client().parts().list().search_query(number).send();
    ASSERT_FALSE(result.data.empty());
}

TEST(Parts, ListPagination) {
    for (int i = 0; i < 3; ++i) {
        auto u = uid();
        client().parts().create().number("PART-PG-" + u).name("Part Pg " + u).send();
    }
    auto page1 = client().parts().list().limit(1).send();
    EXPECT_EQ(1, page1.data.size());
    if (page1.meta.has_more) {
        auto page2 = client().parts().list().limit(1).cursor(page1.meta.next_cursor.value()).send();
        EXPECT_EQ(1, page2.data.size());
        EXPECT_NE(page1.data[0].id, page2.data[0].id);
    }
}

TEST(Parts, DeleteReturnsId) {
    auto uid_val = uid();
    auto number = "PART-DEL-" + uid_val;
    auto created = client().parts().create().number(number).name("Part Del " + uid_val).send();
    auto deleted = client().parts().delete_().number(number).send();
    EXPECT_EQ(created.id, deleted.id);
}

TEST(Parts, DeleteNonexistentReturnsNotFound) {
    EXPECT_THROW(client().parts().delete_().number("NONEXISTENT-" + uid()).send(), NotFoundError);
}

TEST(Parts, UpdateName) {
    auto uid_val = uid();
    auto number = "PART-UPD-" + uid_val;
    client().parts().create().number(number).name("Part Old " + uid_val).send();
    auto new_name = "Part New " + uid_val;
    client().parts().update().number(number).name(new_name).send();
    auto fetched = client().parts().get().number(number).send();
    EXPECT_EQ(new_name, fetched.name);
}

TEST(Parts, UpdateNumber) {
    auto uid_val = uid();
    auto old_number = "PART-UPOLD-" + uid_val;
    auto new_number = "PART-UPNEW-" + uid_val;
    client().parts().create().number(old_number).name("Part Upd " + uid_val).send();
    client().parts().update().number(old_number).new_number(new_number).send();
    auto fetched = client().parts().get().number(new_number).send();
    EXPECT_EQ(new_number, fetched.number);
    EXPECT_THROW(client().parts().get().number(old_number).send(), NotFoundError);
}

TEST(Parts, UpdateDuplicateNumberReturnsConflict) {
    auto uid_val = uid();
    auto number1 = "PART-DUP1-" + uid_val;
    auto number2 = "PART-DUP2-" + uid_val;
    client().parts().create().number(number1).name("P1").send();
    client().parts().create().number(number2).name("P2").send();
    EXPECT_THROW(client().parts().update().number(number2).new_number(number1).send(), ConflictError);
}

TEST(Parts, CreateDuplicateNumberReturnsConflict) {
    auto uid_val = uid();
    auto number = "PART-CDUP-" + uid_val;
    client().parts().create().number(number).name("P1").send();
    EXPECT_THROW(client().parts().create().number(number).name("P2").send(), ConflictError);
}

TEST(Parts, CreateEmptyNumberFails) {
    EXPECT_ANY_THROW(client().parts().create().number("").name("Empty").send());
}
