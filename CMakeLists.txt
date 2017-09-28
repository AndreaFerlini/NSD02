cmake_minimum_required(VERSION 3.8)
project(Practical2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/loadgraph.cpp src/loadgraph.h src/bfs.cpp src/bfs.h)
add_executable(Practical2 ${SOURCE_FILES})