cmake_minimum_required(VERSION 3.13)
project(1 C)

set(CMAKE_C_STANDARD 99)

add_executable(1 main.c)

SET (CMAKE_C_FLAGS  "-ansi -Wall -Wextra -Wpedantic")