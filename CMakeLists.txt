cmake_minimum_required(VERSION 3.5.1)
project(AlgorithmsSpecialization)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -g")

include_directories(include)

add_subdirectory(01.Karatsuba)
add_subdirectory(02.Inversions)
add_subdirectory(03.QuickSort)
add_subdirectory(04.MinimumCut)
add_subdirectory(05.StronglyConnectedComponents)
add_subdirectory(06.ShortestPath)
add_subdirectory(07.MedianMaintenance)
add_subdirectory(08.TwoSum)
