project(process_status)
cmake_minimum_required(VERSION 3.5)
add_definitions(-std=c++11 -o2 -g -Wall)

add_executable(exit_status status.cc)
add_executable(status_waitpid status_waitpid.cc)