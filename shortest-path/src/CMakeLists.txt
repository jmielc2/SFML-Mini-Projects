# establish cmake version
cmake_minimum_required(VERSION 3.0)

# establish version of c++ being used
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define Project
project(path VERSION 1.0)

# SFML Library Location
set(SFML_DEPENDENCIES ${CMAKE_CURRENT_SOURCE_DIR}/../../SFML)

# Project Files
add_executable(path Main.cpp stdafx.cpp
                    Controllers/App.cpp Controllers/GridController.cpp
                    Components/Block.cpp Components/Grid.cpp Components/Node.cpp
                    Tools/SP_Algorithm.cpp Tools/MG_Algorithm.cpp)

# External Header Files
target_include_directories(path PUBLIC ${SFML_DEPENDENCIES}/include)

# Additional Compile Flags
option(RELEASE "Build release version" OFF)
if (RELEASE)
    set(GCC_ADDITIONAL_FLAGS "-Wall -O3 -DDEBUG=0")
else()
    set(GCC_ADDITIONAL_FLAGS "-Wall -g -DDEBUG=1")
endif()
add_definitions(${GCC_ADDITIONAL_FLAGS})

# Link SFML Library
target_link_libraries(path PRIVATE
        ${SFML_DEPENDENCIES}/bin/sfml-graphics-2.dll
        ${SFML_DEPENDENCIES}/bin/sfml-system-2.dll
        ${SFML_DEPENDENCIES}/bin/sfml-window-2.dll)




