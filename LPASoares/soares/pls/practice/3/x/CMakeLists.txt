cmake_minimum_required(VERSION 3.14)

project(x)

set(CMAKE_CXX_FLAGS  "-ansi -Wall -Wextra -Wpedantic")

set(CMAKE_CXX_STANDARD 98)

add_executable(x main.cpp)