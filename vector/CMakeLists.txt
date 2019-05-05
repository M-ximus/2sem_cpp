cmake_minimum_required(VERSION 3.13)
project(vectorishka)

set(CMAKE_CXX_STANDARD 14)

add_executable(vectorishka main.cpp vectorishka.h myexcept.cpp myexcept.h Proxy_bool.cpp Proxy_bool.h)