cmake_minimum_required(VERSION 3.5.1)
project(karatsuba)

set(CMAKE_CXX_STANDARD 14)

include_directories(../include)
include_directories(include)
add_subdirectory(test)

add_executable(karatsuba main.cpp)


