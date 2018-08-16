#ifndef SHORTEST_PATH
#define SHORTEST_PATH

#include <vector>
#include <limits>
#include <queue>

namespace ShortestPath {

    struct Edge {
        unsigned source;
        unsigned target;
        unsigned length;
    };

    struct Graph {
        std::vector< std::vector<Edge> > adjlist;

        Graph(std::size_t size) : adjlist(size) {}
        Graph(std::size_t size, std::vector<Edge> edges) : adjlist(size) {
            for (auto edge : edges) addEdge(edge);
        }
        void addEdge(Edge edge) {
            adjlist[edge.source].push_back(edge);
        }
        std::size_t size() const {
            return adjlist.size();
        }
    };

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

    // shortest path distance from source to all other vertice
    using ShortestPathDistances = std::vector<unsigned>;

    ShortestPathDistances dijkstra(const Graph& graph, unsigned source_node) {
        auto shortest_paths =
            ShortestPathDistances(graph.size(),
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

    ShortestPathDistances
    computeShortestPaths(std::size_t n_nodes, const std::vector<Edge>& edges,
                         unsigned source_node) {
        auto graph = Graph(n_nodes, edges);
        return dijkstra(graph, source_node);
    }
}

#endif
