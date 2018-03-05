#include <gmock/gmock.h>
#include <random>
#include "UnionFind.hpp"
#include "KargersMinCut.hpp"

using namespace testing;
using namespace Kargers;
using namespace DataStructures;

constexpr unsigned N_NODES = 4;

class KargersMinCutInitialize : public Test {
public:
    Edgelist edge_list;
    UnionFind graph = UnionFind(N_NODES);
    std::random_device rd;
    std::mt19937 gen = std::mt19937(rd());
    void SetUp() override {
        edge_list.emplace_back(0, 1);
        edge_list.emplace_back(0, 2);
        edge_list.emplace_back(1, 3);
        edge_list.emplace_back(2, 3);
    }
};
TEST_F(KargersMinCutInitialize, IdentifySeparateNodes) {
    EXPECT_FALSE(isMerged(graph, 0, 1));
    EXPECT_FALSE(isMerged(graph, 1, 2));
    EXPECT_FALSE(isMerged(graph, 2, 3));
}


TEST_F(KargersMinCutInitialize, ContractEdgeCorrectly) {
    contract(graph, 0, 3);
    ASSERT_TRUE(isMerged(graph, 0, 3));
}

TEST_F(KargersMinCutInitialize, RandomContractCorrectly) {
    ASSERT_THAT(getEdgeCountFromRandomContract(N_NODES, edge_list, gen), 2);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}

