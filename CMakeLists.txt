cmake_minimum_required(VERSION 3.23)
project(adventofcode_2022)

set(CMAKE_CXX_STANDARD 17)


#
# Include
#
include_directories(include)

include(FetchContent)
FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 9.1.0
)
FetchContent_MakeAvailable(fmt)


#
# Executable
#
set(COMMON_SRC)

function(add_day_executable day)
    add_executable(day${day}_1 src/day${day}/day${day}_1.cpp ${COMMON_SRC})
    add_executable(day${day}_2 src/day${day}/day${day}_2.cpp ${COMMON_SRC})
    target_link_libraries(day${day}_1 PRIVATE fmt::fmt)
    target_link_libraries(day${day}_2 PRIVATE fmt::fmt)
endfunction()

add_day_executable(2)
add_day_executable(3)
add_day_executable(7)
add_day_executable(8)
add_day_executable(9)
add_day_executable(10)

function(add_day_executable_v2 day)
    add_executable(day${day} src/day${day}/day${day}.cpp ${COMMON_SRC})
    target_link_libraries(day${day} PRIVATE fmt::fmt)
endfunction()

add_day_executable_v2(11)
add_day_executable_v2(12)
add_day_executable_v2(13)
add_day_executable_v2(14)
add_day_executable_v2(15)
add_day_executable_v2(16)
