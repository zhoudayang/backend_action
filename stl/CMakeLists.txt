cmake_minimum_required(VERSION 3.5)
project(stl)
set(str_source str.cpp str_test.cpp)
add_executable(str_test ${str_source})
set(vector_source vector.h vector_test.cpp)
add_executable(vector_test ${vector_source})