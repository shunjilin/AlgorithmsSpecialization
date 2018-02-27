cmake_minimum_required(VERSION 3.5.1)
project(Inversions)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall")

include_directories(../include)
include_directories(include)
add_subdirectory(test)

add_executable(Inversions main.cpp)


