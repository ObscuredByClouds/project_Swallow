cmake_minimum_required(VERSION 3.13) # declare the minimum required CMake version

project(project_swallow VERSION 1.0 LANGUAGES CXX) # project name, version and language
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON) # C++ standart
get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY) # Check if the directory is subproject

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -Wextra")

# SFML
set(SFML_VERSION 2.5.1)
set(SFML_DIR "/usr/include/SFML") # path to SFML (dpkg -L libsfml-dev)
find_package(SFML ${SFML_VERSION} REQUIRED COMPONENTS graphics window system REQUIRED) # <optional> - let CMake automatically find the SFML

# doctest
find_package(doctest REQUIRED)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.hpp")

add_library(swallow_lib ${SOURCES} ${HEADERS})

add_executable(${PROJECT_NAME} main.cpp)

option(SWALLOW_TESTING "Enable module testing" ON)
option(SWALLOW_COVERAGE "Enable code coverage" OFF)

if(NOT SWALLOW_TESTING)
    message(STATUS "Testing Project Swallow is disabled")
elseif(IS_SUBPROJECT)
    message(STATUS "Project Swallow will not test in submodule mode")
else()
    add_subdirectory(test)
endif()

if(NOT IS_SUBPROJECT)
    add_subdirectory(doc)
endif()


target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system swallow_lib)