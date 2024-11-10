cmake_minimum_required(VERSION 3.10)

   project(project_swallow VERSION 1.0 LANGUAGES CXX)

   set(CMAKE_CXX_STANDARD 23)

   get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)
   
   set(SFML_DIR "/usr/include/SFML") # path to SFML

   find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

   add_executable(project_swallow src/main.cpp)

   target_include_directories(project_swallow PRIVATE include)

   target_link_libraries(project_swallow sfml-graphics sfml-window sfml-system)