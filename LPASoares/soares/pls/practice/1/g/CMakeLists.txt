cmake_minimum_required(VERSION 3.13)
project(g C)

set(CMAKE_C_STANDARD 90)

add_executable(g main.c)

SET (CMAKE_C_FLAGS  "-ansi -Wall -Wextra -Wpedantic")