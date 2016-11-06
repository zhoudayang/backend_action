project(valgrind)
cmake_minimum_required(VERSION 3.5)
add_definitions(-g -o2)
add_executable(illegal_mem illegal_memory.cc)

add_executable(uninitialized uninitialized.cc)

add_executable(out_of_bound out_of_bound.cc)

add_executable(cover cover.cc)

add_executable(free_twice free_twice.cc)

add_executable(mem_leaks mem_leaks.cc)
