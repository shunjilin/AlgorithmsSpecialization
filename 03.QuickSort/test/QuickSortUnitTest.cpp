#include <gmock/gmock.h>
#include "QuickSort.hpp"
#include <algorithm>

using namespace testing;

class QuickSortInitialize: public Test {
public:
    std::vector<int> numbers = {4, 7, 3, 1, 6, 2, 8, 5};
    std::vector<int> odd = {1, 2, 3};
    std::vector<int> even = {1, 2, 3, 4};
    std::vector<int> numbers_small = {2, 1};
    std::vector<int> already_sorted = {1, 2, 3, 4, 5, 6, 7, 8};
};

TEST_F(QuickSortInitialize, FirstPivotReturnsCorrectly) {
    ASSERT_THAT(*QuickSort::firstPivot<std::vector<int>::iterator>{}
                (std::begin(numbers), std::end(numbers)), 4);
}

TEST_F(QuickSortInitialize, LastPivotReturnsCorrectly) {
    ASSERT_THAT(*QuickSort::lastPivot<std::vector<int>::iterator>{}
                (std::begin(numbers), std::end(numbers)), 5);
}

TEST_F(QuickSortInitialize, GetMidReturnsCorrectOnOdd) {
    ASSERT_THAT(*QuickSort::getMid(std::begin(odd), std::end(odd)),
                2);
}

TEST_F(QuickSortInitialize, GetMidReturnsCorrectOnEven) {
    ASSERT_THAT(*QuickSort::getMid(std::begin(even), std::end(even)),
                2);
}

TEST_F(QuickSortInitialize, GetMedianOfThreeReturnsCorrect) {
    ASSERT_THAT(*QuickSort::getMedianOfThree(std::begin(odd) + 1,
                                             std::begin(odd),
                                             std::begin(odd) + 2,
                                             std::less<int>()),
                2);
}

TEST_F(QuickSortInitialize, PartitionCorrectly) {
    QuickSort::partition(std::begin(numbers), std::end(numbers),
                         std::begin(numbers) + 2, std::less<int>());
    ASSERT_THAT(std::vector<int>(std::begin(numbers),
                                 std::begin(numbers) + 3),
                UnorderedElementsAre(1,2,3));
}

TEST_F(QuickSortInitialize, PartitionSmallCorrectly) {
    QuickSort::partition(std::begin(numbers_small), std::end(numbers_small),
                         std::begin(numbers_small), std::less<int>());
    ASSERT_THAT(numbers_small, ElementsAre(1, 2));
}

TEST_F(QuickSortInitialize, QuickSorFirstPivotSortsCorrectly) {
    QuickSort::sort(std::begin(numbers), std::end(numbers),
                    QuickSort::firstPivot<std::vector<int>::iterator>(),
                    std::less<int>());
    ASSERT_THAT(numbers, ElementsAre(1, 2, 3, 4, 5, 6, 7, 8));
}

TEST_F(QuickSortInitialize, QuickSorLastPivotSortsCorrectly) {
    QuickSort::sort(std::begin(numbers), std::end(numbers),
                    QuickSort::lastPivot<std::vector<int>::iterator>(),
                    std::less<int>());
    ASSERT_THAT(numbers, ElementsAre(1, 2, 3, 4, 5, 6, 7, 8));
}

TEST_F(QuickSortInitialize, QuickSorMedianOfThreePivotSortsCorrectly) {
    QuickSort::sort(std::begin(numbers), std::end(numbers),
                    QuickSort::medianOfThreePivot<std::vector<int>::iterator,
                    std::less<int> >(),
                    std::less<int>());
    ASSERT_THAT(numbers, ElementsAre(1, 2, 3, 4, 5, 6, 7, 8));
}


TEST_F(QuickSortInitialize, ComparisonCountAccurate) {
    unsigned long long comparisons = 0;
    QuickSort::sort(std::begin(already_sorted), std::end(already_sorted),
                    QuickSort::firstPivot<std::vector<int>::iterator>(),
                    std::less<int>(), &comparisons);
    ASSERT_THAT(comparisons, 28);
}


int main(int argc, char *argv[]) {
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
