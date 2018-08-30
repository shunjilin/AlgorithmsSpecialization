#include <gmock/gmock.h>
#include <vector>
#include "Graph.hpp"
#include "BellmanFord.hpp"

using namespace testing;

class InitializeGraph : public Test {
public:
    std::vector<Edge> edges = { {0, 1, 2}, {0, 4, 3}, {1, 3, -2}, {3, 2, 1},
                                {3, 4, 2}, {4, 2, -1}, {2, 0, 1}, {3, 0, 4}};
    Graph graph = Graph(5, edges);

};

TEST_F(InitializeGraph, CorrectShortestPathDistances) {
    ASSERT_THAT(*BellmanFord(graph, 1), ElementsAre(0, 0, -1, -2, 0));
}

class InitializeGraphWithNegativeCycle : public Test {
public:
    std::vector<Edge> edges = { {0, 1, 2}, {0, 4, 3}, {1, 3, -2}, {3, 0, 4},
                                {4, 2, -1}, {3, 2, 1}, {2, 0, 1}, {3, 4, -1}};
    Graph graph = Graph(5, edges);
};

TEST_F(InitializeGraphWithNegativeCycle, NoShortestPathDistances) {
    ASSERT_FALSE(BellmanFord(graph, 1).has_value());
}
int main(int argc, char *argv[])
{
    InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
