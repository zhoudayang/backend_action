project(simple_pipe)
cmake_minimum_required(VERSION 3.5)

add_definitions(-std=c++11)
add_definitions(-o2)

add_executable(pipe pipe.cc)

add_executable(pipe_reader pipe_reader.cc)
add_executable(pipe_writer pipe_writer.cc)