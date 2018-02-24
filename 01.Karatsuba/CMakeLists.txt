cmake_minimum_required(VERSION 3.5.1)
project(karatsuba)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES main.cpp)

include_directories(../include)
include_directories(include)
add_subdirectory(test)

add_executable(karatsuba ${SOURCE_FILES})


