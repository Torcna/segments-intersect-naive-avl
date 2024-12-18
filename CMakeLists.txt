cmake_minimum_required(VERSION 3.5)


project(AIAS)

include_directories (include)
add_executable(AIAS_s 
src/source.cpp 
include/source_func_for_main.hpp
include/header.hpp 
include/tree.hpp
include/tests_header.hpp
)