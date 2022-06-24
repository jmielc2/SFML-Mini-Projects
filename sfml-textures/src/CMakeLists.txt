# CMake Version
cmake_minimum_required(VERSION 3.0)

# C++ Standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Project
project(pics VERSION 1.0)

# Add The Executables
add_executable(pics Main.cpp)

# Find SFML Library
find_package(SFML 2.5 COMPONENTS graphics audio network system REQUIRED)
target_link_libraries(pics sfml-graphics sfml-audio sfml-network sfml-window sfml-system)
