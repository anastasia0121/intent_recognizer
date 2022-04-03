#include "Config.h"

#include <fstream>
#include <iostream>

// using json = nlohmann::json;

namespace mbient {

void Config::init()
{
    std::ifstream file(m_config_path);
    if (!file.is_open()) {
        std::cerr << "Cannot open the config file '" << m_config_path << "'\n";
        return;
    }

    //json config;
    //file >> config;

    // auto train = config.at("train_file");
    // auto template = config.at("templates_file");

    m_train_file = "etc/train.csv";
    m_templates_file = "etc/templates.txt";
}

}
