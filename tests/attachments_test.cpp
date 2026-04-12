#include "common.hpp"
#include <fstream>
using namespace test;
using namespace tofupilot;

TEST(Attachments, RunAttachmentsCreate) {
    auto run = create_test_run(uid());
    auto path = "/tmp/tofupilot-test-" + uid() + ".txt";
    { std::ofstream f(path); f << "attach to run test"; }
    auto id = client().runs().attachments().upload(run.id, path);
    ASSERT_FALSE(id.empty());
    ASSERT_EQ(36u, id.size());
    std::remove(path.c_str());
}

TEST(Attachments, RunAttachmentsCreateAndVerify) {
    auto run = create_test_run(uid());
    auto path = "/tmp/tofupilot-test-" + uid() + ".txt";
    { std::ofstream f(path); f << "verify test"; }
    auto id = client().runs().attachments().upload(run.id, path);
    auto fetched = client().runs().get().id(run.id).send();
    bool found = false;
    if (fetched.attachments) {
        for (const auto& a : *fetched.attachments) {
            if (a.id == id) { found = true; break; }
        }
    }
    EXPECT_TRUE(found);
    std::remove(path.c_str());
}

TEST(Attachments, RunAttachmentsFileNotFound) {
    EXPECT_THROW(client().runs().attachments().upload("fake-id", "/nonexistent/file.txt"), HttpError);
}

TEST(Attachments, RunAttachmentsDownloadEmptyUrl) {
    EXPECT_THROW(client().runs().attachments().download("", "/tmp/out.txt"), ValidationError);
}

TEST(Attachments, UnitAttachmentsCreateAndDelete) {
    auto u = uid();
    auto part = "PART-DAT-" + u;
    auto serial = "SN-DAT-" + u;
    auto rev = "REV-DAT-" + u;
    client().parts().create().number(part).name("Part " + u).send();
    client().revisions().create().part_number(part).number(rev).send();
    client().units().create().serial_number(serial).part_number(part).revision_number(rev).send();

    auto path = "/tmp/tofupilot-del-" + u + ".txt";
    { std::ofstream f(path); f << "to be deleted"; }
    auto id = client().units().attachments().upload(serial, path);
    ASSERT_FALSE(id.empty());

    auto result = client().units().attachments().delete_(serial, {id});
    EXPECT_FALSE(result.ids.empty());

    auto fetched = client().units().get().serial_number(serial).send();
    bool found = false;
    if (fetched.attachments) {
        for (const auto& a : *fetched.attachments) {
            if (a.id == id) { found = true; break; }
        }
    }
    EXPECT_FALSE(found);
    std::remove(path.c_str());
}
