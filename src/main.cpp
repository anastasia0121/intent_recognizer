#include "Config.h"
#include "IntentRecognizer.h"

#include <iostream>

using namespace mbient;

/**
 * Task:
 *
 * What is the weather like today? => Prints (Intent: Get Weather)
 * What is the weather like in Paris today? => Prints (Intent: Get Weather City)
 * Tell me an interesting fact. => Prints (Intent: Get Fact)
 *
 * Description:
 *
 * In the task sentences have grammar,
 * but as a user, I am sure I will ask anyway but not use the grammar.
 * I can ask about the weather in different ways.
 * I want to believe that the intent recognizer understands me.
 *
 * What's it like outside?
 * It's really cold now.
 * How's the weather?
 * Do you have rain?
 * What's the temperature in Manchester?
 * It's snowing here in Manchester, what's it doing there?
 * What's the weather forecast for the rest of the week?
 *
 * I think it is possible to make enough big dataset and train something.
 * But to parse some extra information we need some patterns.
 * And the patterns ask for some grammar.
 * I did not realize grammar handling in the task but it can be one of the improvements.
 *
 * For exmaple:
 *
 * [Get Fact]
 * what = (nature | IT)
 * about <what>
 *
 * It is not the best example but the idea to find some constructions in a text.
 * "nature" does not have a lot of sense without context.
 * 
 * My templates:
 *
 * 1. Here's a really pure grammar.
 *    If your intention is GetWeather and you mention some city.
 *    I think you ask about the weather in the city.
 *    Also I do not see the "when" entity in the output, so I skip it.
 *    But it makes sense to find smth like today, Monday, week, 3 April, ...
 *
 * [Get Weather]
 * City = (Paris | Moscow)
 *
 * 2. It is more pure grammar.
 *    But maybe it makes sense to find something after "about" word.
 *
 * [Get Fact]
 */
int main(int argc, char ** argv)
{
    (void)argv;
    (void)argc;

    // It does not have a lot of sense to use intent recognition alone.
    // I believe that it should be used as a part of a voice assistent.
    // If translation + recognition + execution parts takes a lot of time
    // user may get bored and ask "Cancel" operation.
    // So It makes sense to use one thread for listening and one to execution.
    // But during the execution handle only the "Cancel" operation to prevent a mess.

    Config config("etc/config.json");
    IntentRecognizer intent_recognizer(config);
    intent_recognizer.init();

    for (std::string in; std::getline(std::cin, in);) {
        if (!in.empty()) {
            std::string out = intent_recognizer.recognize(in);
            if (out.empty()) {
                std::cout << in << " => Prints(Intent: Not found)\n";
            }
            else {
                std::cout << in << " => Prints (Intent: " << out << ")\n";
            }
        }
    }

    return 0;
}
