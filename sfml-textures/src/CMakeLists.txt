# CMake Version
cmake_minimum_required(VERSION 3.0)

# C++ Standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Project
project(pics VERSION 1.0)

# SFML Library Location
set(SFML_DEPENDENCIES ${CMAKE_CURRENT_SOURCE_DIR}/../../SFML)

# Project Files
add_executable(pics Main.cpp)

# External Header Files
target_include_directories(pics PUBLIC ${SFML_DEPENDENCIES}/include)

# Additional Compile Flags
option(RELEASE "Build release version" OFF)
if (RELEASE)
    set(GCC_ADDITIONAL_FLAGS "-Wall -O2")
else()
    set(GCC_ADDITIONAL_FLAGS "-Wall -g")
endif()
add_definitions(${GCC_ADDITIONAL_FLAGS})

# Link SFML Library
target_link_libraries(pics PRIVATE
        ${SFML_DEPENDENCIES}/bin/sfml-graphics-2.dll
        ${SFML_DEPENDENCIES}/bin/sfml-system-2.dll
        ${SFML_DEPENDENCIES}/bin/sfml-window-2.dll)
