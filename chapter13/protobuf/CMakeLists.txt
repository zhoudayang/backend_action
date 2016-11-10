project(protobuf)
cmake_minimum_required(VERSION 3.5)
find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIR})
link_libraries(${Protobuf_LIBRARY_DIR})

add_executable(reader reader.cc message.pb.cc)
add_executable(writer writer.cc message.pb.cc)

target_link_libraries(reader protobuf)
target_link_libraries(writer protobuf)