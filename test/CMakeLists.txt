cmake_minimum_required(VERSION 3.6)

add_subdirectory(googletest/googletest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

include_directories(../src
        googletest/googletest/include
        googletest/googletest)

set(SOURCE_FILES BasicOperation.cpp)
add_executable(BasicOperation ${SOURCE_FILES})
target_link_libraries(BasicOperation linear gtest gtest_main)
