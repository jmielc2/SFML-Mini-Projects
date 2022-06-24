# CMake Version
cmake_minimum_required(VERSION 3.0)

# C++ Standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Project
project(grid VERSION 1.0)

# Add The Executables
add_executable(grid Main.cpp Core.cpp Components/Grid.cpp Components/Block.cpp)

# Find SFML Library
find_package(SFML 2.5 COMPONENTS graphics system REQUIRED)
target_link_libraries(grid sfml-graphics sfml-system)