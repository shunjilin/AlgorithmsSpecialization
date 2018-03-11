cmake_minimum_required(VERSION 3.5.1)
project(Karatsuba)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -g")

include_directories(include)

add_subdirectory(test)
add_subdirectory(01.Karatsuba)
add_subdirectory(02.Inversions)
add_subdirectory(03.QuickSort)
add_subdirectory(04.MinimumCut)
add_subdirectory(05.StronglyConnectedComponents)
