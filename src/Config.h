#pragma once

#include <iostream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

namespace mbient {

/**
 * Intent recognizer configuration
 */
class Config
{
public:
    /**
     * Makes and inits config.
     * @param config_path path to configuration file
     */
    Config(const fs::path & config_path) :
        m_config_path(config_path)
    {
        init();
    }

    /**
     * Parses config file
     */
    void init();

    /**
     * @return file to train intent classifier
     */
    fs::path get_train() const { return m_train_file; }

    /**
     * @return file with templates
     */
    fs::path get_templates() const { return m_templates_file; }

private:
    fs::path m_config_path;
    fs::path m_train_file;
    fs::path m_templates_file;
};

}
