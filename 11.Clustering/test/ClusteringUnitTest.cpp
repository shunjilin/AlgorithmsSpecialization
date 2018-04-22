#include <gmock/gmock.h>
#include "UnionFind.hpp"
#include "Clustering.hpp"

using namespace testing;
using namespace DataStructures;
using namespace Clustering;

class InitializeEdges : public Test {
public:
    unsigned n_nodes = 5;
    std::vector<Edge> edges = {{0, 1, 1}, {0, 2, 100}, {0, 3, 100},
                               {0, 4, 100}, {1, 2, 100}, {1, 3, 100},
                               {1, 4, 100}, {2, 3, 10}, {2, 4, 10},
                               {3, 4, 10}};
};

TEST_F(InitializeEdges, ReturnsCorrectMaxSpacingOf2Clustering) {
    ASSERT_THAT(maxSpacingKClustering(n_nodes, edges, 2), 100);
}

int main(int argc, char *argv[])
{
    InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
