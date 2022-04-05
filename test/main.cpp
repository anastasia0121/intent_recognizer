#include "Config.h"
#include "IntentRecognizer.h"

#include <gtest/gtest.h>

#include <iostream>

using namespace mbient;

namespace {

struct MbientTest : public ::testing::Test
{
    void SetUp() override
    {
        Config config("etc/config.json");
        m_intent_recognizer.init(config);
    }

    void TearDown() override
    {
    }

    IntentRecognizer m_intent_recognizer;
};

}

TEST_F(MbientTest, first_test)
{
    std::string in = "What weather";
    std::string out = m_intent_recognizer.recognize(in);

    EXPECT_EQ(out, "Get Weather");
}

int main(int argc, char ** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
