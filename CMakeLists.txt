cmake_minimum_required(VERSION 3.13) # declare the minimum required CMake version

   project(project_swallow VERSION 1.0 LANGUAGES CXX) # project name, version and language
   set(CMAKE_CXX_STANDARD 23) # C++ standart

   get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY) # Check if the directory is subproject

   # SFML
   set(SFML_DIR "/usr/include/SFML") # path to SFML (dpkg -L libsfml-dev)
   find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED) # <optional> - let CMake automatically find the SFML

   # doctest
   find_package(doctest REQUIRED)
   
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

   add_executable(project_swallow src/main.cpp)

   target_include_directories(project_swallow PRIVATE include)

   target_link_libraries(project_swallow sfml-graphics sfml-window sfml-system)