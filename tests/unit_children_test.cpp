#include "common.hpp"
using namespace test;
using namespace tofupilot;

namespace {
std::string create_unit(const std::string& prefix) {
    auto uid_val = uid();
    auto pn = "PART-" + prefix + "-" + uid_val;
    auto sn = "SN-" + prefix + "-" + uid_val;
    auto rn = "REV-" + prefix + "-" + uid_val;
    client().parts().create().number(pn).name("Part " + uid_val).send();
    client().revisions().create().part_number(pn).number(rn).send();
    client().units().create().serial_number(sn).part_number(pn).revision_number(rn).send();
    return sn;
}
}

TEST(UnitChildren, AddChildSuccess) {
    auto parent = create_unit("ACHP");
    auto child = create_unit("ACHC");
    client().units().add_child().serial_number(parent).child_serial_number(child).send();

    auto parent_unit = client().units().get().serial_number(parent).send();
    ASSERT_TRUE(parent_unit.children.has_value());
    bool found = false;
    for (const auto& c : parent_unit.children.value()) if (c.serial_number == child) found = true;
    EXPECT_TRUE(found);

    auto child_unit = client().units().get().serial_number(child).send();
    ASSERT_TRUE(child_unit.parent.has_value());
    EXPECT_EQ(parent, child_unit.parent.value().serial_number);
}

TEST(UnitChildren, AddMultipleChildren) {
    auto parent = create_unit("AMCP");
    std::vector<std::string> children;
    for (int i = 0; i < 3; ++i) children.push_back(create_unit("AMC" + std::to_string(i)));
    for (const auto& child : children) client().units().add_child().serial_number(parent).child_serial_number(child).send();

    auto parent_unit = client().units().get().serial_number(parent).send();
    ASSERT_TRUE(parent_unit.children.has_value());
    EXPECT_EQ(3, parent_unit.children.value().size());
}

TEST(UnitChildren, RemoveChildSuccess) {
    auto parent = create_unit("RMCP");
    auto child = create_unit("RMCC");
    client().units().add_child().serial_number(parent).child_serial_number(child).send();
    client().units().remove_child().serial_number(parent).child_serial_number(child).send();

    auto parent_unit = client().units().get().serial_number(parent).send();
    bool has_child = false;
    if (parent_unit.children.has_value()) {
        for (const auto& c : parent_unit.children.value()) if (c.serial_number == child) has_child = true;
    }
    EXPECT_FALSE(has_child);
}

TEST(UnitChildren, RemoveChildFromMultiple) {
    auto parent = create_unit("RFMP");
    std::vector<std::string> children;
    for (int i = 0; i < 3; ++i) {
        auto child = create_unit("RFM" + std::to_string(i));
        client().units().add_child().serial_number(parent).child_serial_number(child).send();
        children.push_back(child);
    }
    client().units().remove_child().serial_number(parent).child_serial_number(children[1]).send();

    auto parent_unit = client().units().get().serial_number(parent).send();
    ASSERT_TRUE(parent_unit.children.has_value());
    EXPECT_EQ(2, parent_unit.children.value().size());
    bool found_removed = false;
    for (const auto& c : parent_unit.children.value()) if (c.serial_number == children[1]) found_removed = true;
    EXPECT_FALSE(found_removed);
}

TEST(UnitChildren, AddChildSelfReferenceFails) {
    auto unit = create_unit("SELF");
    EXPECT_ANY_THROW(client().units().add_child().serial_number(unit).child_serial_number(unit).send());
}

TEST(UnitChildren, AddChildCycleDetection) {
    auto a = create_unit("CYCA");
    auto b = create_unit("CYCB");
    client().units().add_child().serial_number(a).child_serial_number(b).send();
    EXPECT_ANY_THROW(client().units().add_child().serial_number(b).child_serial_number(a).send());
}

TEST(UnitChildren, AddChildParentNotFound) {
    auto child = create_unit("ACPNF");
    EXPECT_THROW(client().units().add_child().serial_number("NONEXISTENT-" + uid()).child_serial_number(child).send(), NotFoundError);
}

TEST(UnitChildren, AddChildChildNotFound) {
    auto parent = create_unit("ACCNF");
    EXPECT_THROW(client().units().add_child().serial_number(parent).child_serial_number("NONEXISTENT-" + uid()).send(), NotFoundError);
}

TEST(UnitChildren, ExcludeUnitsWithParent) {
    auto parent = create_unit("EXWP");
    auto child = create_unit("EXWC");
    client().units().add_child().serial_number(parent).child_serial_number(child).send();

    auto result = client().units().list().serial_numbers({parent, child}).exclude_units_with_parent(true).send();
    bool found_child = false, found_parent = false;
    for (const auto& u : result.data) {
        if (u.serial_number == child) found_child = true;
        if (u.serial_number == parent) found_parent = true;
    }
    EXPECT_FALSE(found_child);
    EXPECT_TRUE(found_parent);
}

TEST(UnitChildren, RemoveChildNotActuallyChildFails) {
    auto parent = create_unit("RNAC_P");
    auto other = create_unit("RNAC_O");
    EXPECT_ANY_THROW(client().units().remove_child().serial_number(parent).child_serial_number(other).send());
}

TEST(UnitChildren, RemoveChildParentNotFound) {
    auto child = create_unit("RCPNF");
    EXPECT_THROW(client().units().remove_child().serial_number("NONEXISTENT-" + uid()).child_serial_number(child).send(), NotFoundError);
}
