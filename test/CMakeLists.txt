   add_executable(run_tests test_main.cpp)

   target_link_libraries(run_tests PRIVATE doctest::doctest) # link doctest to run_tests
