cmake_minimum_required(VERSION 3.13)

project(c)

set(CMAKE_CXX_STANDARD 98)

set(CMAKE_CXX_FLAGS  "-ansi -Wall -Wextra -Wpedantic")

add_executable(c main.cpp)