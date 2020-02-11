cmake_minimum_required(VERSION 3.13)
project(b)

set(CMAKE_CXX_STANDARD 98)

add_executable(b main.cpp)

SET (CMAKE_CXX_FLAGS  "-ansi -Wall -Wextra -Wpedantic")