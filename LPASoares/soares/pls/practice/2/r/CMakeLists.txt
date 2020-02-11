cmake_minimum_required(VERSION 3.13)
project(r C)

set(CMAKE_C_STANDARD 90)

add_executable(r main.c)

SET (CMAKE_C_FLAGS  "-ansi -Wall -Wextra -Wpedantic")