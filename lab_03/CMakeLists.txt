project(lab_03 LANGUAGES CXX)

add_executable(lab_03_run main.cpp include/figure.hpp include/pentagon.h include/rhombus.h include/trapezoid.h)

add_executable(lab_03_tests tests/main_tests.cpp include/figure.h include/pentagon.h include/rhombus.h include/trapezoid.h)

target_link_libraries(lab_03_tests PRIVATE gtest gtest_main)