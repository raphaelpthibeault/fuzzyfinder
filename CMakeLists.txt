cmake_minimum_required(VERSION 3.27)
project(fuzzyfinder)

set(CMAKE_C_STANDARD 11)

find_package(OpenMP REQUIRED)

include_directories(
        fuzzyfinder
        fuzzysearch
        util
)

add_executable(fuzzyfinder
        util/util.h
        util/error_handling.c
        util/error_handling.h
        util/wrapper.c
        util/wrapper.h
        test.c
        fuzzysearch/damarau_levenshtein.c
        fuzzysearch/damarau_levenshtein.h
        fuzzysearch/fuzzy.c
        fuzzysearch/fuzzy.h
        fuzzysearch/bitonic_sort.c
        fuzzysearch/bitonic_sort.h
)

target_include_directories(fuzzyfinder PUBLIC ${OpenMP_CXX_INCLUDE_DIRS})
target_link_libraries(fuzzyfinder PUBLIC OpenMP::OpenMP_CXX)
