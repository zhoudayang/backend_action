project(sema)
cmake_minimum_required(VERSION 3.5)
add_definitions(-std=c++11)
add_definitions(-o2)
add_definitions(-g)

add_executable(sema sema.cc)
target_link_libraries(sema pthread)
