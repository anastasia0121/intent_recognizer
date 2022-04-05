#include "Config.h"
#include "IntentRecognizer.h"

#include <gtest/gtest.h>

using namespace mbient;

namespace {

struct IntentRecognizerTest : public ::testing::Test
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

TEST_F(IntentRecognizerTest, recognizer_test)
{
    // it is better to use csv file to test and train
    // train 70%
    // test 30%
    std::vector<std::pair<std::string, std::string>> data = 
        {{"What weather", "Get Weather"},
         {"How weather", "Get Weather"},
         {"What is the weather like today?", "Get Weather"},
         {"What is the weather like in Paris today?", "Get Weather City"},
         {"What weather in Moscow", "Get Weather City"},
         {"Tell me an interesting fact.", "Get Fact"},
         {"Tell fact", "Get Fact"},
         {"Something new and unusual", ""},
         {"What", ""},
         {"Paris", ""},
         {"fact", ""},
        };

    for (const auto & [in, out]: data) {
        EXPECT_EQ(m_intent_recognizer.recognize(in), out);
    }
}

}
