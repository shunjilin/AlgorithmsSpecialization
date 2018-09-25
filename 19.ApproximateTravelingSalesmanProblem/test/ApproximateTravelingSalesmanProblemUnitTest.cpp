#include <gmock/gmock.h>
#include <vector>
#include "ApproximateTravelingSalesmanProblem.hpp"

using namespace testing;

class TSPInitialize : public Test {
public:
    std::vector<Vertex> vertices = {{1, 1}, {2, 1}, {3, 1}};
};

TEST_F(TSPInitialize, ReturnsCorrectApproximateTSPValue) {
    ASSERT_EQ(getApproximateTSPValue(vertices), 4);
}

int main(int argc, char *argv[])
{
    InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
