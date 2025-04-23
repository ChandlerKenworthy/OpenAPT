cmake_minimum_required(VERSION 3.10)

# Project name
project(OpenAPT VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include include/GeometryObjects)

# Source files
file(GLOB_RECURSE SOURCES main.cpp "src/*.cpp" "src/GeometryObjects/*.cpp")

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories for the target
target_include_directories(${PROJECT_NAME} PRIVATE include)