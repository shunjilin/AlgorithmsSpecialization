#include <gmock/gmock.h>
#include "ClusteringBig.hpp"
#include <vector>

using namespace testing;
using namespace ClusteringBig;

class InitializeEdges : public Test {
public:
    unsigned n_bits = 5;
    std::vector<int> nodes = {0b00000, 0b11111, 0b00001, 0b11100, 0b00010,
                              0b00010};
};


TEST_F(InitializeEdges, CorrectNumberOfClusteringForSpacingOfAtLeast3) {
    ASSERT_THAT(kValueForSpacingOfAtLeast3(nodes, n_bits), 2);
}

int main(int argc, char *argv[])
{
    InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}

