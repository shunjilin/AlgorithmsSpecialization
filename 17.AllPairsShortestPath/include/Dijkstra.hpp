#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include <vector>
#include <limits>
#include <queue>
#include "Graph.hpp"
// Dijkstra's Algorithm

struct FrontierNode {
    int target;
    int length;
        
    bool operator >(const FrontierNode& other) const {
        return length > other.length;
    }
};
using Frontier = std::priority_queue<FrontierNode,
                                     std::vector<FrontierNode>,
                                     std::greater<FrontierNode> >;

using NodeToShortestPathDistance = std::vector<int>;
NodeToShortestPathDistance Dijkstra(const Graph& graph, int source_node) {
    auto shortest_paths =
        NodeToShortestPathDistance(graph.size(),
                                   std::numeric_limits<int>::max());
    auto frontier = Frontier();
    shortest_paths[source_node] = 0;
    for (auto& edge : graph.adjlist[source_node]) {
        frontier.push({edge.target, edge.length});
    }
    while (!frontier.empty()) {
        auto node = frontier.top();
        frontier.pop();
        if (shortest_paths[node.target] ==
            std::numeric_limits<int>::max()) { // if unvisited
            shortest_paths[node.target] = node.length;
            for (auto edge : graph.adjlist[node.target]) {
                frontier.push({edge.target,
                            edge.length + shortest_paths[node.target]});
            }
        }
    }
    return shortest_paths;
}

#endif
