cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEB")
set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG -g")

set(VERSION 0.1)

project(mbient)

add_executable(${CMAKE_PROJECT_NAME} src/main.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_PROJECT_NAME}_lib)

set(RESOURCES etc/config.json etc/train.csv etc/templates.txt)
foreach(item IN LISTS RESOURCES)
  message(STATUS ${item})
  add_custom_command(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${item}"
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/${item}" "${CMAKE_CURRENT_BINARY_DIR}/${item}"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${item}"
    )
endforeach()

add_custom_target(resource-target ALL DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/${RESOURCES}")

add_subdirectory(src)
#add_subdirectory(test)
