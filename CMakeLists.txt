cmake_minimum_required (VERSION 3.8)

project(Test)

add_compile_options(-Wall)
add_compile_options(-Wextra)
add_compile_options(-Werror)

add_compile_options(-g -pthread)

# add_compile_options(-fprofile-arcs -ftest-coverage)
# add_compile_options(--coverage)
# add_link_options(--coverage)

set(CMAKE_CXX_STANDARD 14)

include_directories("include")

file(GLOB SOURCES
  src/*.cpp
  src/*.c
)

add_executable(test ${SOURCES})

#Link with standard libraries
target_link_libraries(test pthread)

#Run test through valgrind to check for memory leak
add_custom_target(
   valgrind
   COMMAND valgrind --tool=memcheck --leak-check=full --track-origins=yes --suppressions=${CMAKE_CURRENT_SOURCE_DIR}/suppression_file ${CMAKE_CURRENT_SOURCE_DIR}/build/test --gtest_repeat=1 2>${CMAKE_CURRENT_SOURCE_DIR}/valgrind.txt
)

set(CMAKE_EXPORT_COMPILE_COMMANDS false)

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Now simply link against gtest or gtest_main as needed. Eg
# add_executable(example example.cpp)
target_link_libraries(test gtest)
# add_test(NAME TestPrintf.test1 COMMAND test)