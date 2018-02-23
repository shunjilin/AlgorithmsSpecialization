//Copyright 2018 <Shunji Lin>

#include <gmock/gmock.h>
#include "Karatsuba.hpp"

using namespace testing;
using namespace Karatsuba;

class KaratsubaInitialize: public Test {
public:
    std::deque<char>even_one = {1, 2, 3, 4}; // 4321;
    std::deque<char>even_two = {6, 7, 8, 9}; // 9876;
    std::deque<char>odd_one = {1, 2, 3};
    std::deque<char>odd_two = {6, 7, 8};
    std::deque<char>untruncated = {0, 0, 1, 0, 0, 0};
};

TEST_F(KaratsubaInitialize, TruncateCorrectly) {
    truncate(untruncated);
    ASSERT_THAT(untruncated.size(), 3);
}

TEST_F(KaratsubaInitialize, AddNumbersCorrectly) {
    ASSERT_THAT(add(even_one, even_two), ElementsAre(7, 9, 1, 4, 1));
}

TEST_F(KaratsubaInitialize, SubtractNumbersCorrectly) {
    ASSERT_THAT(subtract(even_two, even_one), ElementsAre(5, 5, 5, 5));
}

TEST_F(KaratsubaInitialize, MultiplySingleDigitsCorrectly) {
    ASSERT_THAT(multiplySingleDigits(std::deque<char>{9},
                                     std::deque<char>{8}),
                ElementsAre(2, 7));
}

TEST_F(KaratsubaInitialize, MultiplyEvenNumbersCorrectly) {
    ASSERT_THAT(multiply(even_one, even_two), ElementsAre(6, 9, 1, 4, 7, 6, 2, 4));
}


TEST_F(KaratsubaInitialize, MultiplyOddNumbersCorrectly) {
    ASSERT_THAT(multiply(odd_one, odd_two), ElementsAre(6, 9, 1, 1, 8, 2));
}

int main(int argc, char *argv[]) {
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}

