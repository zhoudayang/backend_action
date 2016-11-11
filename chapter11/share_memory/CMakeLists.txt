project(shared_memory)
cmake_minimum_required(VERSION 3.5)

# Werror : treat warning as error!
add_definitions(-std=c++11 -o2 -g -Wall -Werror)


add_executable(consumer consumer.cc)
add_executable(producer producer.cc)
