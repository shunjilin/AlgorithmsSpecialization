#include <gmock/gmock.h>
#include "BitstringFunctions.hpp"
#include <algorithm>
#include <vector>

using namespace testing;
using namespace BitstringFunctions;

TEST(Bitstring, CorrectNumberOfOnes) {
    ASSERT_THAT(nOnes(0b10101), 3);
}

TEST(Bitstring, CorrectHammingDistance) {
    ASSERT_THAT(hammingDistance(0b1011, 0b1100), 3);
}

TEST(Bitstring, FlipBitCorrectly) {
    ASSERT_THAT(flipBit(0b1011, 1), 0b1001); 
}

TEST(Bitstring, GeneratesAllDistanceOneBitstrings) {
    auto generator = DistanceOneGenerator(0b101, 3);
    std::vector<int> bitstrings;
    while (!generator.done) {
        bitstrings.push_back(generator.generate());
    }
    std::sort(std::begin(bitstrings), std::end(bitstrings));
    ASSERT_THAT(bitstrings, ElementsAre(1, 4, 7));
}

TEST(Bitstring, GeneratesAllDistanceTwoBitstrings) {
    auto generator = DistanceTwoGenerator(0b1010, 4);
    std::vector<int> bitstrings;
    while (!generator.done) {
        bitstrings.push_back(generator.generate());
    }
    std::sort(std::begin(bitstrings), std::end(bitstrings));
    ASSERT_THAT(bitstrings, ElementsAre(0, 3, 6, 9, 12, 15));
}

int main(int argc, char *argv[])
{
    InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
