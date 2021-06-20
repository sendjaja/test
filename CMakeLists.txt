cmake_minimum_required (VERSION 3.8)

project(Test CXX)

add_compile_options(-Wall)
add_compile_options(-Wextra)
add_compile_options(-Werror)

add_compile_options(-g -pthread)

add_compile_options(--coverage)

set(CMAKE_CXX_STANDARD 14)

include_directories("include")

file(GLOB SOURCES "src/*.cpp")

add_executable(test ${SOURCES})

target_link_libraries(test gcov)

#Link with standard libraries
target_link_libraries(test pthread)

#Run test through valgrind to check for memory leak
add_custom_target(
   valgrind
   COMMAND valgrind --tool=memcheck --leak-check=full --track-origins=yes --suppressions=${CMAKE_CURRENT_SOURCE_DIR}/suppression_file ${CMAKE_CURRENT_SOURCE_DIR}/build/test --gtest_repeat=1 2>${CMAKE_CURRENT_SOURCE_DIR}/valgrind.txt
)

set(CMAKE_EXPORT_COMPILE_COMMANDS)