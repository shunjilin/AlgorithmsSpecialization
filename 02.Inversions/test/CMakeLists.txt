add_executable(InversionsUnitTest InversionsUnitTest.cpp)
add_executable(InversionsStressTest InversionsStressTest.cpp)

target_link_libraries(InversionsUnitTest gmock pthread)

add_test(InversionsUnitTest InversionsUnitTest)
