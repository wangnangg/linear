cmake_minimum_required(VERSION 3.6)
project(cpp)

add_subdirectory(test)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES src/Matrix.cpp src/Matrix.h src/Algorithm.cpp src/Algorithm.h)
add_library(linear ${SOURCE_FILES})