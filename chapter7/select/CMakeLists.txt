project(select)
cmake_minimum_required(VERSION 3.5)
add_definitions(-o2)
add_definitions(-std=c++11)

add_executable(server server.cc)
add_executable(client client.cc)
