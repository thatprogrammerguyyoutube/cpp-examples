cmake_minimum_required(VERSION 3.25)
project(bst)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../doctest)

add_library(bst INTERFACE src/BinarySearchTree.h)

add_executable(bst_cli main.cpp)
target_link_libraries(bst_cli PUBLIC bst)
target_include_directories(bst_cli PUBLIC src)

add_executable(video_tests tests/tests.cpp tests/binary_search_tree.cpp)
target_link_libraries(video_tests PUBLIC bst)
target_include_directories(video_tests PUBLIC src)

enable_testing()

add_test(tests video_tests)
