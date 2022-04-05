#include "Preprocessor.h"

#include <gtest/gtest.h>

using namespace mbient;

namespace {

struct PreprocessorTest : public ::testing::Test
{
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }

    Preprocessor m_preprocessor;
};

struct InOut
{
    std::string in;
    std::vector<std::string> out;
    std::string delimeters;
};

TEST_F(PreprocessorTest, tokenize)
{
    std::vector<InOut> in_out = {{"aaa bbb",   {"aaa", "bbb"}, " "},
                                 {"..aaa  ,,", {"aaa"},        ". ,"},
                                 {"aa",        {"aa"},         ".,|"},
                                 {".....",     {},             "."},
                                 {"a,... b",   {"a", "b"},     ",. "}};


    for (const auto & [in, out, delimeters]: in_out) {
        std::vector<std::string> vout = Preprocessor::tokenize(in, delimeters);
        EXPECT_EQ(out.size(), vout.size());
        EXPECT_TRUE(std::equal(out.begin(), out.end(), vout.begin()));
    }
}

TEST_F(PreprocessorTest, preprocess)
{
    std::vector<InOut> in_out = {{"Aaa bbb",   {"aaa", "bbb"}, {}},
                                 {"..Aaa  ,,", {"aaa"},        {}},
                                 {"AA",        {"aa"},         {}},
                                 {".....",     {},             {}},
                                 {"a,... B",   {"a", "b"},     {}}};


    for (const auto & [in, out, delimeters]: in_out) {
        std::vector<std::string> vout = m_preprocessor.preprocess(in);
        EXPECT_EQ(out.size(), vout.size()) << in;
        EXPECT_TRUE(std::equal(out.begin(), out.end(), vout.begin()));
    }
}

}
