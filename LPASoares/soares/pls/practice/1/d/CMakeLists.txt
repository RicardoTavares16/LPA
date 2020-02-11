cmake_minimum_required(VERSION 3.13)
project(d)

set(CMAKE_CXX_STANDARD 98)

add_executable(d main.cpp)

SET (CMAKE_CXX_FLAGS  "-ansi -Wall -Wextra -Wpedantic")