#pragma once

#include "Preprocessor.h"

#include <experimental/filesystem>
#include <vector>
#include <unordered_map>

namespace fs = std::experimental::filesystem;

namespace mbient {

/**
 * I cannot say what is better here.
 * For example, Russian Alice uses KNN.
 * But it really depends on data. KNN can be no the fastest way.
 * If groups in KNN is close to each other the result can be bad.
 * And so on and so on.
 *
 * This is implementation of a really simple classifier.
 * We even cannot ask in two different ways about weather.
 * Natural language is rich so simple string comparison does not enough.
 * Also, maybe it make sense use dictionary and convert words into ints.
 *
 * But anyway it works for three given sentences :)
 * Efficiency? The classifier is the first thing that I want to replace here.
 * Noone map cannot help here. The algorithm must be changed.
 */
class Classifier
{
public:
    /**
     * @return true if the classifier is trained, false otherwise.
     */
    bool is_trained() const { return m_trained; }

    /**
     * Trains the classifier.
     * @param preprocessor is preprocessor to prepare data.
     * @param data_file is file with data to the train.
     */
    void train(const Preprocessor & preprocessor, const fs::path & data_file);

    /**
     * Finds an intent for a sentence.
     *
     * @param tokens is tokenized sentence.
     * @return intent name or empty string if intent cannot be find.
     */
    std::string classify(const std::vector<std::string> & tokens);

private:
    // map[intent] = [[required, words, ...],[other, required, words, ...], ...]
    std::unordered_map<std::string, std::vector<std::vector<std::string>>> m_intents;
    // is it trained
    bool m_trained = false;
};

}
