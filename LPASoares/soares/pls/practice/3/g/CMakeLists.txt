cmake_minimum_required(VERSION 3.13)

project(g)

set(CMAKE_CXX_FLAGS  "-ansi -Wall -Wextra -Wpedantic")

set(CMAKE_CXX_STANDARD 98)

add_executable(g main.cpp)