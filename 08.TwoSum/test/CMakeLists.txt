add_executable(TwoSumUnitTest TwoSumUnitTest.cpp)
add_executable(TwoSumStressTest TwoSumStressTest.cpp)

target_link_libraries(TwoSumUnitTest gmock pthread)
