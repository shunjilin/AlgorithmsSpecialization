add_executable(BellmanFordUnitTest BellmanFordUnitTest.cpp)

target_link_libraries(BellmanFordUnitTest gmock pthread)

add_test(BellmanFordUnitTest BellmanFordUnitTest)

add_executable(JohnsonUnitTest JohnsonUnitTest.cpp)

target_link_libraries(JohnsonUnitTest gmock pthread)

add_test(JohnsonUnitTest JohnsonUnitTest)
