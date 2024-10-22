#include <gmock/gmock.h>
#include <vector>
#include "TravelingSalesmanProblem.hpp"

using namespace testing;

TEST(TSP, countSetBits) {
    ASSERT_EQ(countSetBits(0b101), 2);
}

TEST(TSP, isBitSetAtIndex) {
    ASSERT_TRUE(isBitSetAtIndex(0b101, 0));
}

TEST(TSP, getTSPSubsets) {
    ASSERT_THAT(getTSPSubsets(2), ElementsAre(Subset(0b01), Subset(0b11)));
}

class InitializeVertices : public Test {
public:
    std::vector<Vertex> vertices =
        std::vector<Vertex>{ Vertex{0, 0}, Vertex{0, 3}, Vertex{3, 3} };
};

TEST_F(InitializeVertices, CorrectTSPValue) {
    ASSERT_NEAR(getTSPvalue(vertices), 10.24, 0.01);
}

class InitializeVertices2 : public Test {
public:
    std::vector<Vertex> vertices =
        std::vector<Vertex>{ Vertex{0, 0}, Vertex{4, 3}, Vertex{4, 0}, Vertex{0, 3} };
};

TEST_F(InitializeVertices2, CorrectTSPValue) {
    ASSERT_NEAR(getTSPvalue(vertices), 14, 0.01);
}

int main(int argc, char *argv[])
{
    InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
