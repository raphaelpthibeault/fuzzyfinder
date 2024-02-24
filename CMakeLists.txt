cmake_minimum_required(VERSION 3.27)
project(fuzzyfinder)

set(CMAKE_C_STANDARD 11)

enable_testing()
find_package(GTest REQUIRED)

# add executables for tests 
# add_executable ...
# target_include_directories
# target_link_directories

include_directories(
        fuzzyfinder
        fuzzysearch
        util
)

# add_executable main project
add_executable(fuzzyfinder
        util/util.h
        util/error_handling.c
        util/error_handling.h
        util/wrapper.c
        util/wrapper.h
        test.c
)

# I think fuzzy search should be a lib

