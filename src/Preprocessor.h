#pragma once

#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

namespace mbient {

/**
 * Text preprocessing.
 * It prepares text to Classifier.
 * Tokenizes and makes lower case.
 */
class Preprocessor
{
public:
    /**
     * Inits preprocessor.
     * Not in the case but we need stop words or convertion rules.
     */
    void init() {}

    /**
     * Tokenizes and converts into lower case.
     * @param in is given setnence.
     * @return tokenized sentence.
     */
    std::vector<std::string> prepocess(const std::string & in) const;

    /**
     * Divides a text into tokens.
     * @param in is given test.
     * @param delimeters is list of delimeters. For exmaple, ".,|".
     * @return tokenized sentence.
     */
    static std::vector<std::string> tokenize(const std::string & in, const std::string & delimeters);

private:
    // std::vector<std::sting> m_stop_words;
};

}
