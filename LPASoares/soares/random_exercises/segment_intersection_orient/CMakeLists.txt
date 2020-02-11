cmake_minimum_required(VERSION 3.13)
project(segment_intersection_orient C)

set(CMAKE_C_STANDARD 99)

SET (CMAKE_C_FLAGS  "-ansi -Wall -Wextra -Wpedantic")

add_executable(segment_intersection_orient main.c)