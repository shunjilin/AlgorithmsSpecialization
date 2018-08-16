#ifndef ALL_PAIRS_SHORTEST_PATH_HPP
#define ALL_PAIRS_SHORTEST_PATH_HPP

#include <vector>
#include <queue>
#include <limits>

struct Edge {
    unsigned source;
    unsigned target;
    unsigned length;
};

struct Graph {
    std::vector< std::vector<Edge> > adjlist;

    Graph(size_t size) : adjlist(size) {}
    Graph(size_t size, std::vector<Edge> edges) : adjlist(size) {
        for (auto edge : edges) addEdge(edge);
    }
    void addEdge(Edge edge) {
        adjlist[edge.source].push_back(edge);
    }
    size_t size() const {
        return adjlist.size();
    }  
};

// Dijkstra's Algorithm
struct FrontierNode {
    unsigned target;
    unsigned length;
        
    bool operator >(const FrontierNode& other) const {
        return length > other.length;
    }
};
using Frontier = std::priority_queue<FrontierNode,
                                     std::vector<FrontierNode>,
                                     std::greater<FrontierNode> >;

using NodeToShortestPathDistance = std::vector<unsigned>;
NodeToShortestPathDistance dijkstra(const Graph& graph, unsigned source_node) {
    auto shortest_paths =
        NodeToShortestPathDistance(graph.size(),
                                   std::numeric_limits<unsigned>::max());
    auto frontier = Frontier();
    shortest_paths[source_node] = 0;
    for (auto& edge : graph.adjlist[source_node]) {
        frontier.push({edge.target, edge.length});
    }
    while (!frontier.empty()) {
        auto node = frontier.top();
        frontier.pop();
        if (shortest_paths[node.target] ==
            std::numeric_limits<unsigned>::max()) { // if unvisited
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
