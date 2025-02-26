cmake_minimum_required(VERSION 3.0)

project(first-http-server)

add_executable(first-http-server main.cpp)

install(TARGETS first-http-server RUNTIME DESTINATION bin)
