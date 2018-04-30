#include <gmock/gmock.h>
#include <vector>
#include "MaxWeightIndependentSet.hpp"

using namespace testing;
using namespace DynamicProgramming;

TEST(PathGraph, CorrectMaxWeightIndependentSet) {
    auto path = std::vector<unsigned>{1, 4, 5, 4};
    ASSERT_THAT(totalWeightOfMWIS(path), 8);
}

TEST(PathGraph, CorrectNodesInMaxWeightIndependentSet) {
    auto path = std::vector<unsigned>{1, 4, 5, 4};
    ASSERT_THAT(getIndexOfMWISNodes(path), ElementsAre(1, 3));
}

int main(int argc, char *argv[])
{
    InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
