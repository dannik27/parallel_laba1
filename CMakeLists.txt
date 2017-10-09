cmake_minimum_required(VERSION 3.8)
project(parallel_laba1)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")

set(SOURCE_FILES main.cpp Matrix.cpp Matrix.h)
add_executable(parallel_laba1 ${SOURCE_FILES})