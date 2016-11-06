project(gdb)
cmake_minimum_required(VERSION 3.5)
add_definitions(-g)
add_executable(test_ test.cc)

add_executable(down core.cc)
