#include "Classifier.h"

#include <fstream>
#include <iostream>

namespace mbient {

void Classifier::train(const Preprocessor & preprocessor, const fs::path & data_file)
{
    if (m_trained) {
        return;
    }

    std::ifstream file(data_file);
    if (!file.is_open()) {
        std::cerr << "Cannot open the train file '" << data_file << "'" << std::endl;
        return;
    }

    const std::string csv_delimeter = ";";

    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> csv_values = Preprocessor::tokenize(line, csv_delimeter);
        if (!csv_values.empty() && (csv_values.size() != 2)) {
            std::cerr << "Skip line: " << line << std::endl;
            continue;
        }
        std::string & intent = csv_values[0];
        std::string & sentence = csv_values[1];

        std::vector<std::string> tokens = preprocessor.prepocess(sentence);
        if (!intent.empty() && !tokens.empty()) {
            m_intents[intent].emplace_back(std::move(tokens));
        }
    }

    m_trained = true;
}

std::string Classifier::classify(const std::vector<std::string> & tokens)
{
    for (const auto & [intent, sentences]: m_intents) {
        for (const auto & sentence: sentences) {
            auto word_it = sentence.begin();
            auto token_it = tokens.begin();
            for (;;) {
                if (word_it == sentence.end()) {
                    return intent;                    
                }
                if (token_it == tokens.end()) {
                    break;
                }
                if (*word_it == *token_it) {
                    word_it++;
                }
                token_it++;
            }
        }
    }
    
    // We are here because we cannot classify the input.
    // Is it noise?
    // Should we google it?
    // Or our user is lonely person and they want to talk with us...
    // This is a really simple classifier!
    // It does not have extra intense as GoogleIt or TalkWithMe.
    // So I return empty string
    return "";
}

}
