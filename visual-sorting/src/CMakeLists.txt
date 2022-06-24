# List CMake Version
cmake_minimum_required(VERSION 3.0)

# Set CMake Macros
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STARDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# List Project Files
project(sort VERSION 1.0)

add_executable(sort Main.cpp stdafx.cpp Components/App.cpp Components/Bar.cpp Components/SortController.cpp)

set(GCC_ADDITIONAL_FLAGS "-Wall -g -O2")
add_definitions(${GCC_ADDITIONAL_FLAGS})

# Find and Link SFML Library
find_package(SFML 2.5 COMPONENTS graphics system window REQUIRED)
target_link_libraries(sort sfml-graphics sfml-system sfml-window)