#include <gmock/gmock.h>
#include <memory>
#include "ShortestPath.hpp"

using namespace testing;
using namespace ShortestPath;

constexpr std::size_t N_NODES = 6;

class GraphInitialize : public Test {
public:
    std::vector<Edge> edges = {{0, 1, 4}, {0, 2, 2}, {1, 2, 5}, {1, 3, 10},
                               {2, 4, 3}, {4, 3, 4}, {3, 5, 11}};
    std::unique_ptr<Graph> graph;
    void SetUp() override {
        graph = std::make_unique<Graph>(N_NODES, edges);
    }
};

TEST_F(GraphInitialize, ShortestPathsCorrect) {
    auto shortest_paths = dijkstra(*graph, 0);
    ASSERT_THAT(shortest_paths, ElementsAre(0, 4, 2, 9, 5, 20));
}

TEST_F(GraphInitialize, ComputeShortestPathsCorrect) {
    auto shortest_paths = computeShortestPaths(N_NODES, edges, 0);
    ASSERT_THAT(shortest_paths, ElementsAre(0, 4, 2, 9, 5, 20));
}

int main(int argc, char *argv[])
{
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
