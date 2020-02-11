cmake_minimum_required(VERSION 3.13)

project(e)

set(CMAKE_CXX_STANDARD 98)

set(CMAKE_CXX_FLAGS  "-ansi -Wall -Wextra -Wpedantic")

add_executable(e main.cpp)