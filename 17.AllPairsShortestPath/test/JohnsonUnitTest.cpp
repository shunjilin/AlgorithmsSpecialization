#include <gmock/gmock.h>
#include <vector>
#include "Graph.hpp"
#include "BellmanFord.hpp"
#include "Johnson.hpp"

using namespace testing;

class InitializeGraph : public Test {
public:
    std::vector<Edge> edges = { {0, 1, 2}, {0, 4, 3}, {1, 3, -2}, {3, 2, 1},
                                {3, 4, 2}, {4, 2, -1}, {2, 0, 1}, {3, 0, 4}};
    Graph graph = Graph(5, edges);

};

TEST_F(InitializeGraph, CorrectShortestPathDistances) {
    auto all_pairs_shortest_paths = Johnson(graph).value();
    EXPECT_THAT(all_pairs_shortest_paths[0], ElementsAre(0, 2, 1, 0, 2));
    EXPECT_THAT(all_pairs_shortest_paths[1], ElementsAre(0, 0, -1, -2, 0));
    EXPECT_THAT(all_pairs_shortest_paths[2], ElementsAre(1, 3, 0, 1, 3));
    EXPECT_THAT(all_pairs_shortest_paths[3], ElementsAre(2, 4, 1, 0, 2));
    EXPECT_THAT(all_pairs_shortest_paths[4], ElementsAre(0, 2, -1, 0, 0));
}

TEST_F(InitializeGraph, CorrectShortestShortestPathDistances) {
    ASSERT_EQ(shortestShortestPath(graph).value(), -2);
}

class InitializeGraphWithNegativeCycle : public Test {
public:
    std::vector<Edge> edges = { {0, 1, 2}, {0, 4, 3}, {1, 3, -2}, {3, 0, 4},
                                {4, 2, -1}, {3, 2, 1}, {2, 0, 1}, {3, 4, -1}};
    Graph graph = Graph(5, edges);
};

TEST_F(InitializeGraphWithNegativeCycle, NoShortestPathDistances) {
    ASSERT_FALSE(Johnson(graph).has_value());
}
int main(int argc, char *argv[])
{
    InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
