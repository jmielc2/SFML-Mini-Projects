# CMake Version
cmake_minimum_required(VERSION 3.10)

# Specify C++ Standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STARNARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set the Project Name
project(boing VERSION 1.0)

# add the executable(s)
add_executable(boing main.cpp Ball.cpp)

# Find the SFML Library
find_package(SFML 2.5 COMPONENTS graphics audio network system audio REQUIRED)
target_link_libraries(boing sfml-graphics sfml-audio sfml-network sfml-system sfml-audio)