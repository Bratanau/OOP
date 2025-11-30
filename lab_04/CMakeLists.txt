cmake_minimum_required(VERSION 3.12)
project(FiguresProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
endif()

find_package(GTest REQUIRED)

add_executable(figures_main src/main.cpp src/figures.cpp)
target_include_directories(figures_main PUBLIC ${CMAKE_SOURCE_DIR}/include)


