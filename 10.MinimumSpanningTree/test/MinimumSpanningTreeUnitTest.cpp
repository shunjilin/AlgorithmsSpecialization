#include <gmock/gmock.h>
#include "MinimumSpanningTree.hpp"

using namespace testing;
using namespace PrimsAlgorithm;

class InitializeEdges : public Test {
public:
    std::vector<Edge> edges = {{0, 1, 1}, {1, 3, 2}, {2, 0, 4}, {3, 2, 5},
                               {3, 0, 3}};
    Graph graph = Graph(4);
    void SetUp() override {
        for (auto edge : edges) {
            graph.insertEdge(edge);
        }
    }
};

TEST(Graph, GraphUnDirected) {
    unsigned n_nodes = 2;
    Edge edge = {0, 1, 1};
    Graph graph(n_nodes);
    graph.insertEdge(edge);
    EXPECT_THAT(graph.getEdgesOfNode(0)[0].target, 1);
    ASSERT_THAT(graph.getEdgesOfNode(1)[0].target, 0);
}

TEST_F(InitializeEdges, ReturnsMinSpanningTreeCost) {
    ASSERT_THAT(computeMinimumSpanningTreeCost(graph), 7);
}

int main(int argc, char *argv[])
{
    InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
