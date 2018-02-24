include_directories("../include")

add_executable(KaratsubaUnitTest KaratsubaUnitTest.cpp)
add_executable(KaratsubaStressTest KaratsubaStressTest.cpp)

target_link_libraries(KaratsubaUnitTest gmock pthread)
