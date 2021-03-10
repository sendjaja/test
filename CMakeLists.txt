cmake_minimum_required (VERSION 3.8)

project(Test CXX)

add_compile_options(-Wall)
add_compile_options(-Wextra)
add_compile_options(-Werror)

add_compile_options(-g -pthread)

set(CMAKE_CXX_STANDARD 14)

include_directories("include")

file(GLOB SOURCES "src/*.cpp")

add_executable(test ${SOURCES})

#Link with standard libraries
target_link_libraries(test pthread)
