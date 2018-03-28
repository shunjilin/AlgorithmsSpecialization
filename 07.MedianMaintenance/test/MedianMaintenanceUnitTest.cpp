#include <gmock/gmock.h>
#include <memory>
#include "MedianMaintenance.hpp"

#include <vector>

using namespace testing;
using namespace DataStructures;

class IntegerStreamInitialize : public Test {
public:
    std::vector<int> numbers = {2, 5, 1, 4, 3};
    MedianMaintenance<int>MM = MedianMaintenance<int>();
};

TEST_F(IntegerStreamInitialize, firstMedianCorrect) {
    MM.push(numbers.back());
    ASSERT_THAT(MM.getMedian(), 3);
}

TEST_F(IntegerStreamInitialize, EvenMedianCorrect) {
    for (int i = 0; i < 2; ++i) {
        MM.push(numbers.back());
        numbers.pop_back();
    }
    ASSERT_THAT(MM.getMedian(), 3);
}

TEST_F(IntegerStreamInitialize, OddMedianCorrect) {
    for (int i = 0; i < 3; ++i) {
        MM.push(numbers.back());
        numbers.pop_back();
    }
    ASSERT_THAT(MM.getMedian(), 3);
}

TEST_F(IntegerStreamInitialize, MedianStreamCorrect) {
    std::vector<int> median_stream;
    for (auto number : numbers) {
        MM.push(number);
        median_stream.push_back(MM.getMedian());
    }
    ASSERT_THAT(median_stream, ElementsAre(2, 2, 2, 2, 3));    
}

int main(int argc, char *argv[])
{
    InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
