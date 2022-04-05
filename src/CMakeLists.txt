set(BINARY ${CMAKE_PROJECT_NAME}_lib)

file(GLOB SOURCES *.cpp)
list(FILTER SOURCES EXCLUDE REGEX main.cpp)

add_library(${BINARY} STATIC ${SOURCES})

target_include_directories(${BINARY} PUBLIC .)

target_link_libraries(${BINARY} PUBLIC stdc++fs nlohmann_json::nlohmann_json)
