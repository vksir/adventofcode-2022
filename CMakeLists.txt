cmake_minimum_required(VERSION 3.23)
project(adventofcode_2022)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/day2)

add_executable(day2_1 src/day2/day2_1.cpp src/util.cpp src/util.h)
add_executable(day2_2 src/day2/day2_2.cpp src/util.cpp src/util.h)
add_executable(day3_1 src/day3/day3_1.cpp src/util.cpp src/util.h)
add_executable(day3_2 src/day3/day3_2.cpp src/util.cpp src/util.h)
