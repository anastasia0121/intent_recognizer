#pragma once

#include <experimental/filesystem>
#include <iostream>
#include <vector>
#include <unordered_map>

namespace fs = std::experimental::filesystem;

namespace mbient {

/**
 * Describes some parameter of user request.
 * It can be city or day.
 */
struct Entity
{
    // City
    std::string m_name;
    // Paris
    std::string m_value;
};

/**
 * Describes possible values of parameter possibly provided by user.
 * City can be Paris or Moscow.
 * Day can be today or monday.
 */
struct EntityTemplate
{
    // City
    std::string m_name;
    // [Paris, Moscow]
    std::vector<std::string> m_values;
};

/**
 * I believe that there are some libraries to do the task.
 * But it is easier to parse given example myself.
 *
 * When I use EntitiesFinder I have already known an intent so I should use it.
 */
class EntitiesFinder
{
public:
    /**
     * Trains the finder.
     * @param template_file is file with templates.
     */
    void init(const fs::path & template_file);

    /**
     * Finds entities value in a sentence.
     *
     * @param intent is intent name.
     * @param tokens is tokenized sentence.
     * @return list of entities found in the tokens
     */
    std::vector<Entity> find_entities(const std::string & intent, const std::vector<std::string> & tokens);

private:
    // map[GetWeather] = [{City: [paris, moscow]}, {Date: [today, monday], ...}]
    std::unordered_map<std::string, std::vector<EntityTemplate>> m_map;
};

}
