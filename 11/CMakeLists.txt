cmake_minimum_required(VERSION 3.0.0)                          # CMake version check

get_filename_component(PROJECT_NAME ${CMAKE_SOURCE_DIR} NAME)  # Get the main directory name and set the project name to it
project(${PROJECT_NAME})                                       # Create a project with its name

set(CMAKE_CXX_STANDARD 20)                                     # Enable c++14 standard

file(GLOB SOURCES src/*.cpp)                                   # Add all cpp files from src as a var named SOURCES

add_executable(${PROJECT_NAME} ${SOURCES})                     # Add executable target with source files listed in the SOURCES variable

