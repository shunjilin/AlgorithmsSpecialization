include_directories("../include")

add_executable(QuickSortUnitTest QuickSortUnitTest.cpp)

target_link_libraries(QuickSortUnitTest gmock pthread)
