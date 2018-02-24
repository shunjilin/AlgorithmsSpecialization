include_directories("../include")

add_executable(KaratsubaTest KaratsubaTest.cpp)
add_executable(StressTest StressTest.cpp)

target_link_libraries(KaratsubaTest gmock pthread)
