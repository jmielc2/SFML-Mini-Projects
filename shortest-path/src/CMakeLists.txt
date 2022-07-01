# establish cmake version
cmake_minimum_required(VERSION 3.0)

# establish version of c++ being used
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define Project
project(path VERSION 1.0)

add_executable(path Main.cpp stdafx.cpp 
                    Components/App.cpp Components/Block.cpp Components/BlockGrid.cpp Components/Node.cpp
                    Tools/SP_Algorithm.cpp)

# Additional Compile Flags
option(RELEASE "Build release version" OFF)
if (RELEASE)
    set(GCC_ADDITIONAL_FLAGS "-Wall -g -O2")
else()
    set(GCC_ADDITIONAL_FLAGS "-Wall -g")
endif()
add_definitions(${GCC_ADDITIONAL_FLAGS})

# Find the SFML Package (needs to be in the PATH)

# add_library(SFML SHARED IMPORTED)
# set_target_properties(SFML PROPERTIES IMPORTED_LOCATION "${CMAKE_SRC_DIR}/../../lib/" INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/../../include/")
# target_link_libraries(path SFML)

find_package(SFML 2.5 COMPONENTS graphics system window REQUIRED)
target_link_libraries(path sfml-graphics sfml-system sfml-window)



