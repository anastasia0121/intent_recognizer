#include "Preprocessor.h"

#include <algorithm>
#include <cctype>
#include <sstream> 
#include <string>
#include <vector>

namespace mbient {

std::vector<std::string> Preprocessor::tokenize(const std::string & in, const std::string & delimeters)
{
    std::vector<std::string> tokens;
    size_t start;
    size_t end = 0;
    
    while ((start = in.find_first_not_of(delimeters, end)) != std::string::npos)
    {
        end = in.find_first_of(delimeters, start);
        tokens.emplace_back(in.substr(start, end - start));
    }

    return tokens;
}

std::vector<std::string> Preprocessor::preprocess(const std::string & in) const
{
    // Use natural language processing tools
    // MITIE or text2vec or Moses or other

    // 1. Does it support multi languages? Translate.
    // 2. Does it converted (from audio, not typed) input?
    //    Should I convert everythig in lower case?
    // 3. Remove word endings. Not sure about weather example.
    //    playing -> play
    //    better -> good
    //    dog, dogs, dog’s, dogs’ -> dog
    //    grandmother's village -> grandmother village (maybe you want to know weather in some unusual place)
    // 4. Number replacing. Not in the case, but if we are talking about the future
    // 5. Remove stop words.
    // 6. Maybe it make sense to use white list?

    const std::string delimeters = ",. !?|";
    std::vector<std::string> tokens = tokenize(in, delimeters);

    for (auto & token: tokens) {
        std::transform(token.begin(), token.end(), token.begin(), [](char c){ return std::tolower(c); });
    }

    return tokens;
}

}
