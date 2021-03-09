cmake_minimum_required(VERSION 3.8.10)
project(nexustec)

set(CMAKE_CXX_STANDARD_REQUIRED 14)

include_directories(include)

add_executable(tsp src/tsp_main.cpp src/graph.cpp)