project(struct_net)
cmake_minimum_required(VERSION 2.9)
add_definitions(-g -o2 -std=c++11)
add_executable(client client.cc util.cc)
add_executable(server server.cc util.cc)

