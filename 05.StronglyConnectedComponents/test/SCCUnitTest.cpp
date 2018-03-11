#include <gmock/gmock.h>
#include <memory>
#include "SCC.hpp"

using namespace testing;
using namespace SCC;

constexpr std::size_t N_NODES = 9;

class GraphInitialize : public Test {
public:
    std::vector<Edge> edges = {{6, 0}, {3, 6}, {0, 3}, {8, 6}, {5, 8}, {2, 5},
                               {8, 2}, {7, 5}, {7, 4}, {4, 1}, {1, 7}};
    std::unique_ptr<Graph> graph;
    std::unique_ptr<Graph> reversed_graph;
    void SetUp() override {
        graph = std::make_unique<Graph>(N_NODES, edges);
        auto reversed_edges = edges;
        for (auto& edge : reversed_edges) {
            reverseEdge(edge);
        }
        reversed_graph = std::make_unique<Graph>(N_NODES, reversed_edges);
    }
    
};

TEST_F(GraphInitialize, FinishingTimesCorrect) {
    auto finishing_times = kosarajuFirstPass(*reversed_graph);
    auto max_scc_1 = std::max(std::max(finishing_times[0], finishing_times[6]),
                              finishing_times[3]);
    auto max_scc_2 = std::max(std::max(finishing_times[8], finishing_times[5]),
                              finishing_times[2]);
    auto max_scc_3 = std::max(std::max(finishing_times[7], finishing_times[4]),
                              finishing_times[1]);
    EXPECT_GT(max_scc_1, max_scc_2);
    EXPECT_GT(max_scc_2, max_scc_3);
}

TEST_F(GraphInitialize, LeadersCorrect) {
    auto finishing_times = kosarajuFirstPass(*reversed_graph);
    auto node_to_leader = kosarajuSecondPass(*graph, finishing_times);
    ASSERT_THAT(node_to_leader, ElementsAre(0, 7, 8, 0, 7, 8, 0, 7, 8));
}

TEST_F(GraphInitialize, SCCSizesCorrect) {
    auto finishing_times = kosarajuFirstPass(*reversed_graph);
    auto node_to_leader = kosarajuSecondPass(*graph, finishing_times);
    auto leader_to_scc_size = getSCCSizes(node_to_leader);
    std::vector<unsigned>  scc_sizes;
    for (auto k_v : leader_to_scc_size) {
        scc_sizes.push_back(k_v.second);
    }
    ASSERT_THAT(scc_sizes, ElementsAre(3, 3, 3));
}

TEST_F(GraphInitialize, ComputeSCCCorrect) {
    auto leader_to_scc_size = computeSCC(N_NODES, edges);
    std::vector<unsigned>  scc_sizes;
    for (auto k_v : leader_to_scc_size) {
        scc_sizes.push_back(k_v.second);
    }
    ASSERT_THAT(scc_sizes, ElementsAre(3, 3, 3));
}


int main(int argc, char *argv[])
{
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
