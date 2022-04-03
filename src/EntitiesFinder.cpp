#include "EntitiesFinder.h"
#include "Preprocessor.h"

#include <algorithm>
#include <fstream>
#include <iostream>

namespace mbient {

void EntitiesFinder::init(const fs::path & template_file)
{
    std::ifstream file(template_file);
    if (!file.is_open()) {
        std::cerr << "Cannot open the template file '" << template_file << "'" << std::endl;
        return;
    }

    // [Get Weather]
    // City = (Paris | Moscow)

    auto trim = +[](std::string to_trim){
        const std::string delimeters = "[] ";
        to_trim.erase(to_trim.find_last_not_of(delimeters) + 1);
        to_trim.erase(0, to_trim.find_first_not_of(delimeters));
        return to_trim;
    };

    std::string intent;
    while (std::getline(file, intent)) {
        intent = trim(std::move(intent));

        std::vector<std::string> entities;
        std::string line;
        while (std::getline(file, line) && !line.empty()) {
            auto it = line.find('=');
            if (it != std::string::npos) {
                std::string name = trim(line.substr(0, it));
                line.erase(0, it + 1);
                std::transform(line.begin(), line.end(), line.begin(), [](char c){ return std::tolower(c); });

                const std::string delimeters = "( |)=";
                std::vector<std::string> tokens = Preprocessor::tokenize(line, delimeters);
                m_map[intent].push_back({std::move(name), std::move(tokens)});
            }
        }
    }
}

std::vector<Entity> EntitiesFinder::find_entities(const std::string & intent, const std::vector<std::string> & tokens)
{
    auto it = m_map.find(intent);
    if (it == m_map.end()) {
        return {};
    }

    // In the example with the weather, it makes sense to find a city name only.
    // Why else would we use the name of the city in the weather request?

    // In the improvement version, we can create a graph to describe our grammar.
    // With grammar we can find some patterns.

    std::vector<Entity> ret;
    for (const auto & entity: it->second) {
        for (const auto & value: entity.m_values) {
            auto it = std::find(tokens.begin(), tokens.end(), value);
            if (it != tokens.end()) {
                ret.push_back({entity.m_name, value});
            }
        }
    }
    return ret;
}

}
