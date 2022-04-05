set(TEST_NAME ${CMAKE_PROJECT_NAME}_test)

set(TEST_SOURCES main.cpp IntentRecognizerTest.cpp PreprocessorTest.cpp)

add_executable(${TEST_NAME} ${TEST_SOURCES})

target_link_libraries(${TEST_NAME} PRIVATE ${CMAKE_PROJECT_NAME}_lib gtest)

set(RESOURCES etc/config.json etc/train.csv etc/templates.txt)
foreach(item IN LISTS RESOURCES)
  message(STATUS ${item})
  add_custom_command(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${item}"
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/${item}" "${CMAKE_CURRENT_BINARY_DIR}/${item}"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${item}"
    )
endforeach()

add_custom_target(test-resource-target ALL DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/${RESOURCES}")

add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})

