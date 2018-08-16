add_executable(SCCUnitTest SCCUnitTest.cpp)

target_link_libraries(SCCUnitTest gmock pthread)

add_test(SCCUnitTest SCCUnitTest)
