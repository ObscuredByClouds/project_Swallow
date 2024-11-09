cmake_minimum_required(VERSION 3.10)

   project(project_swallow)

   set(CMAKE_CXX_STANDARD 17)

   set(SFML_DIR "/usr/include/SFML") # path to SFML

   find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

   add_executable(project_swallow src/main.cpp)

   target_include_directories(project_swallow PRIVATE include)
   
   target_link_libraries(project_swallow sfml-graphics sfml-window sfml-system)