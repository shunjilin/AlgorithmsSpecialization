add_executable(BitstringFunctionsUnitTest BitstringFunctionsUnitTest.cpp)
add_executable(ClusteringBigUnitTest ClusteringBigUnitTest.cpp)

target_link_libraries(BitstringFunctionsUnitTest gmock pthread)
target_link_libraries(ClusteringBigUnitTest gmock pthread)

add_test(BitstringFunctionsUnitTest BitstringFunctionsUnitTest)
add_test(ClusteringBigUnitTest ClusteringBigUnitTest)
