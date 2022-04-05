#include "IntentRecognizer.h"

namespace mbient {

void IntentRecognizer::init(const Config & config)
{
    m_preprocessor.init();
    m_classifier.train(m_preprocessor, config.get_train()); // or init from trained data
    m_entity_finder.init(config.get_templates());
}

std::string IntentRecognizer::recognize(const std::string & in)
{
    // 1. Check trained or not
    if (!m_classifier.is_trained()) {
        std::cerr << "Classifier is not trained" << std::endl;
        return "";
    }

    // 2. Preprocessing
    std::vector<std::string> tokens = m_preprocessor.prepocess(in);

    // 3. Recognize an intent
    std::string intent = m_classifier.classify(tokens);
    if (intent.empty()) {
        return "";
    }

    // 4. Fill entities connected to the intent
    std::vector<Entity> entities = m_entity_finder.find_entities(intent, tokens);

    // 5. Make output
    std::string out = intent;
    for (const auto & entity: entities) {
        out += " ";
        out += entity.m_name;
    }

    return out;
}

}
