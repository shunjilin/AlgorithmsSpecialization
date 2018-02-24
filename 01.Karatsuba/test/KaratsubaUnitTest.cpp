//Copyright 2018 <Shunji Lin>

#include <gmock/gmock.h>
#include "Karatsuba.hpp"

using namespace testing;
using namespace Karatsuba;

class KaratsubaInitialize: public Test {
public:
    std::string even_one = "4321";
    std::string even_two = "9876";
    std::string odd_one = "321";
    std::string odd_two = "876";
    std::deque<char>untruncated = {0, 0, 1, 0, 0, 0};
};

TEST_F(KaratsubaInitialize, EncodeNumberCorrectly) {
    ASSERT_THAT(encode(even_one), ElementsAre(1, 2, 3, 4));
}

TEST_F(KaratsubaInitialize, DecodeNumberCorrectly) {
        ASSERT_THAT(decode(encode(even_one)), even_one);
}

TEST_F(KaratsubaInitialize, TruncateCorrectly) {
    truncate(untruncated);
    ASSERT_THAT(untruncated.size(), 3);
}

TEST_F(KaratsubaInitialize, AddNumbersCorrectly) {
    ASSERT_THAT(add(encode(even_one),
                    encode(even_two)),
                ElementsAre(7, 9, 1, 4, 1));
}

TEST_F(KaratsubaInitialize, SubtractNumbersCorrectly) {
    ASSERT_THAT(subtract(encode(even_two),
                         encode(even_one)), ElementsAre(5, 5, 5, 5));
}

TEST_F(KaratsubaInitialize, MultiplySingleDigitsCorrectly) {
    ASSERT_THAT(multiplySingleDigits(std::deque<char>{9},
                                     std::deque<char>{8}),
                ElementsAre(2, 7));
}

TEST_F(KaratsubaInitialize, MultiplyEvenNumbersCorrectly) {
    ASSERT_THAT(multiplyHelper(encode(even_one),
                               encode(even_two)), ElementsAre(6, 9, 1, 4, 7, 6, 2, 4));
}


TEST_F(KaratsubaInitialize, MultiplyOddNumbersCorrectly) {
    ASSERT_THAT(multiplyHelper(encode(odd_one),
                               encode(odd_two)), ElementsAre(6, 9, 1, 1, 8, 2));
}

int main(int argc, char *argv[]) {
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}

