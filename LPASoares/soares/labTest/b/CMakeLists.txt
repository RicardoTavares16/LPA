cmake_minimum_required(VERSION 3.14)

project(b)

set(CMAKE_CXX_STANDARD 98)

set(CMAKE_CXX_FLAGS "-Wall -Wpedantic")

add_executable(b main.cpp)