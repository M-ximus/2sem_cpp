cmake_minimum_required(VERSION 3.13)
project(Game)

set(CMAKE_CXX_STANDARD 14)

add_executable(Game main.cpp Engine.cpp Engine.h Matter.cpp Matter.h Eat.cpp Eat.h)