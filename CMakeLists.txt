cmake_minimum_required(VERSION 3.21.0)
project(DSAProject3)

# These options will make our program run way faster
# Leaving these commented out for now because it makes debugging harder.
add_compile_options(-O3)
#add_compile_options(-march=native)

set(CMAKE_CXX_STANDARD 17)

add_executable(DSAProject3 main.cpp bplustree.h treeNode.h)
