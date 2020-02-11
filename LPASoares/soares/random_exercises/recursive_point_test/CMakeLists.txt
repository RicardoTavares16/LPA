cmake_minimum_required(VERSION 3.13)
project(recursive_point_test C)

set(CMAKE_C_STANDARD 99)

add_executable(recursive_point_test main.c)

SET ( CMAKE_C_FLAGS  "-ansi -Wall -Wextra -Wpedantic" )