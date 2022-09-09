cmake_minimum_required(VERSION 3.14)

project(TheLogLogger VERSION 0.0.1
                     DESCRIPTION "Daily-journal program using C++ & SQLite")

add_subdirectory(sqlite)
add_executable(${PROJECT_NAME} src/main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE sqlite include)
target_link_libraries(${PROJECT_NAME} PRIVATE SQLite)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)