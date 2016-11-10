project(daemon)
cmake_minimum_required(VERSION 3.5)
add_definitions(-o2 -std=c++11)

add_executable(daemon daemon.cc)
