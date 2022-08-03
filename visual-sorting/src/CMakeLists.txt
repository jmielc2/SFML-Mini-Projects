# List CMake Version
cmake_minimum_required(VERSION 3.0)

# Set CMake Macros
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STARDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# List Project Files
project(sort VERSION 1.0)

# SFML Library Location
set(SFML_DEPENDENCIES ${CMAKE_CURRENT_SOURCE_DIR}/../../SFML)

add_executable(sort Main.cpp stdafx.cpp Components/App.cpp Components/Bar.cpp Components/SortController.cpp)

# External Header Files
target_include_directories(sort PUBLIC ${SFML_DEPENDENCIES}/include)

# Additional Compile Flags
option(RELEASE "Build release version" OFF)
if (RELEASE)
    set(GCC_ADDITIONAL_FLAGS "-Wall -O2")
else()
    set(GCC_ADDITIONAL_FLAGS "-Wall -g")
endif()
add_definitions(${GCC_ADDITIONAL_FLAGS})

# Find and Link SFML Library
target_link_libraries(sort PRIVATE
        ${SFML_DEPENDENCIES}/bin/sfml-graphics-2.dll
        ${SFML_DEPENDENCIES}/bin/sfml-system-2.dll
        ${SFML_DEPENDENCIES}/bin/sfml-window-2.dll)