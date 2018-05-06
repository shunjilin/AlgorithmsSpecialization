#include <gmock/gmock.h>
#include <vector>
#include "Knapsack.hpp"

using namespace testing;
using namespace DynamicProgramming;

class InitializeKnapsackObjects : public Test {
public:
    std::vector<KnapsackObject> objects = { {92, 23}, {57, 31}, {49, 29},
                                            {68, 44}, {60, 53}, {43, 38},
                                            {67, 63}, {84, 85}, {87, 89},
                                            {72, 82} };
    unsigned max_weight = 165;
};

TEST_F(InitializeKnapsackObjects, ReturnOptimalSolution) {
    ASSERT_THAT(computeOptimalKnapsackValue(objects, 165),
                objects[0].value + objects[1].value + objects[2].value +
                objects[3].value + objects[5].value);
}

int main(int argc, char *argv[])
{
    InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
