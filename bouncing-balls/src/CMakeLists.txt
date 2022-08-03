# CMake Version
cmake_minimum_required(VERSION 3.10)

# Specify C++ Standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STARNARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set the Project Name
project(boing VERSION 1.0)

# SFML Library Location
set(SFML_DEPENDENCIES ${CMAKE_CURRENT_SOURCE_DIR}/../../SFML)

# add the executable(s)
add_executable(boing Main.cpp Ball.cpp)

# External Header Files
target_include_directories(boing PUBLIC ${SFML_DEPENDENCIES}/include)

# Additional Compile Flags
option(RELEASE "Build release version" OFF)
if (RELEASE)
    set(GCC_ADDITIONAL_FLAGS "-Wall -O2")
else()
    set(GCC_ADDITIONAL_FLAGS "-Wall -g")
endif()
add_definitions(${GCC_ADDITIONAL_FLAGS})

# Link SFML Library
target_link_libraries(boing PRIVATE
        ${SFML_DEPENDENCIES}/bin/sfml-graphics-2.dll
        ${SFML_DEPENDENCIES}/bin/sfml-system-2.dll
        ${SFML_DEPENDENCIES}/bin/sfml-window-2.dll)