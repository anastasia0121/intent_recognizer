# intent_recognizer
This is a simple intent recognizer.

# build
mkdir build

cd build

cmake ../

make

# out
What is the weather like today? => Prints (Intent: Get Weather)

What is the weather like in Paris today? => Prints (Intent: Get Weather City)

Tell me an interesting fact. => Prints (Intent: Get Fact)

What weather => Prints (Intent: Get Weather)

How weather => Prints (Intent: Get Weather)

What weather in Paris => Prints (Intent: Get Weather City)

Tell fact => Prints (Intent: Get Fact)

Something new and unusual => Prints (Intent: Not found)
