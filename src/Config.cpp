#include "Config.h"

#include "nlohmann/json.hpp"

#include <fstream>
#include <iostream>

namespace mbient {

void Config::init()
{
    std::ifstream file(m_config_path);
    if (!file.is_open()) {
        std::cerr << "Cannot open the config file '" << m_config_path << "'" << std::endl;
        return;
    }

    nlohmann::json config;
    file >> config;

    for (auto & [key, value] : config.items()) {
        if (key == "train_file") {
            m_train_file = value.get<std::string>();
        }
        else if (key == "templates_file") {
            m_templates_file = value.get<std::string>();
        }
        else {
            std::cerr << "Unknown element in config file: " << key << std::endl;
        }
    }
}

}
