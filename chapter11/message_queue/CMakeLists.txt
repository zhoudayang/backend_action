project(message_queue)
cmake_minimum_required(VERSION 3.5)

add_definitions(-o2)
add_definitions(-std=c++11)
add_definitions(-Wall)
add_definitions(-g)

add_executable(receiver receiver.cc)
add_executable(sender sender.cc)