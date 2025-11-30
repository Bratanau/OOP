project(lab_05 LANGUAGES CXX)

add_executable(lab_05_run main.cpp include/queue_with_pmr.hpp)

add_executable(lab_05_tests tests/queue_tests.cpp include/queue_with_pmr.hpp)

target_link_libraries(lab_05_tests PRIVATE gtest gtest_main)