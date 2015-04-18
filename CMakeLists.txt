cmake_minimum_required(VERSION 2.6)
project(bdsm)

#
# Testing
#

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/gtest/include)
add_subdirectory(3rdparty/gtest)
enable_testing()

#
# Sources
#

set(CMAKE_C_FLAGS "-std=c99 -Werror -Wall -Wextra")

add_library(${CMAKE_PROJECT_NAME} STATIC src/alloc.c
  src/slist.c
  src/dlist.c
  src/array.c
  src/vector.c
  src/heap.c
)

#
# Tests
#

set(CMAKE_CXX_FLAGS "-std=c++0x -Werror -Wall -Wextra -Wno-sign-compare")

add_executable(${CMAKE_PROJECT_NAME}_test 
  3rdparty/gtest/src/gtest_main.cc
  test/alloc_test.cpp
  test/single_linked_list_test.cpp
  test/double_linked_list_test.cpp
  test/array_test.cpp
  test/vector_test.cpp
  test/heap_test.cpp
)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/)
target_link_libraries(${CMAKE_PROJECT_NAME}_test gtest bdsm)

add_test(${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_NAME}_test)

add_custom_target(run_tests ALL DEPENDS
  ${CMAKE_PROJECT_NAME}_test)

add_custom_command(TARGET run_tests
                   POST_BUILD
                   COMMAND ctest --output-on-failure)
