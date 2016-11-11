project(semaphore)
cmake_minimum_required(VERSION 3.5)
add_definitions(-std=c++11 -o2 -g -Wall -Werror)

add_executable(reader reader.cc)
add_executable(writer writer.cc)