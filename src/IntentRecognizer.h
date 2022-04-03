#pragma once

#include "Classifier.h"
#include "Config.h"
#include "EntitiesFinder.h"
#include "Preprocessor.h"

namespace mbient {

/**
 * Really simple imtent recognizer
 */
class IntentRecognizer
{
public:
    IntentRecognizer(const Config & config) :
        m_config(config)
    {}

    /**
     * Initializes internal structures from config
     */
    void init();

    /**
     * Recognizes an intent and its entities
     * @param in is user sentence
     * @return intent name or an empty string if it cannot classify the sentence
     */
    std::string recognize(const std::string & in);

private:
    Config m_config;
    Preprocessor m_preprocessor;
    Classifier m_classifier;
    EntitiesFinder m_entity_finder;
};

}
