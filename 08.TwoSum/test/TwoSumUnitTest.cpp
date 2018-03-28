#include <gmock/gmock.h>
#include <memory>
#include "TwoSum.hpp"

#include <vector>

using namespace testing;
using namespace TwoSum;

class NumbersInitialize : public Test {
public:
    std::vector<long> summands = {5, -1, 3, 0, -1, 5};
    long max_sum = 4;
    long min_sum = -4;
};

TEST_F(NumbersInitialize, ReturnCorrectNumberOfUniqueSums) {
    ASSERT_THAT(getNumOfTwoSumsInRange(summands, min_sum, max_sum), 4);
}

int main(int argc, char *argv[]) {
    InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
