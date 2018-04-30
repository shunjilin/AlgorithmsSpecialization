#include <gmock/gmock.h>
#include "HuffmanCoding.hpp"
#include <vector>

using namespace HuffmanCoding;
using namespace testing;

class InitializeSymbols : public Test {
public:
    std::vector<Node> codes = { {3}, {2}, {6}, {8}, {2}, {6} };
    
};

TEST_F(InitializeSymbols, CorrectMaximumLengthOfCodeword) {
    ASSERT_THAT(maxDepthOfBinaryTree(computeHuffmanTree(codes)), 4);
}

TEST_F(InitializeSymbols, CorrectMinimumLengthOfCodeword) {
    ASSERT_THAT(minDepthOfBinaryTree(computeHuffmanTree(codes)), 2);
}

int main(int argc, char *argv[])
{
    InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
