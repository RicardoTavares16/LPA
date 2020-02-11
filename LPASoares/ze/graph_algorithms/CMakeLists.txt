cmake_minimum_required(VERSION 3.13)

project(graph_algorithms)

set(CMAKE_CXX_STANDARD 98)

set(CMAKE_CXX_FLAGS "-Wall -std=c++98")

add_executable(graph_algorithms mooshak_solutions/m_dfs.cpp)