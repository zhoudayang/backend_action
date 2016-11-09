project(epoll)
add_definitions(-std=c++11)
add_definitions(-o2)
add_definitions(-Wall)

add_executable(server server.cc)
add_executable(client client.cc)
