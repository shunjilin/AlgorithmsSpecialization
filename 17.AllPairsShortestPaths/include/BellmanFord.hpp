#ifndef BELLMAN_FORD_HPP
#define BELLMAN_FORD_HPP

#include "Graph.hpp"
#include <vector>
#include <optional>
#include <iostream>

// Bellman-Ford algorithm

// build reversed adjlist, which holds incoming instead of outgoing edges
Graph reverseAdjlist(Graph const & graph) {
    Graph reversed = Graph(graph.size());
    for (auto const & edges : graph.adjlist) {
        for (auto const & edge : edges) {
            reversed.addEdge(Edge{edge.target, edge.source, edge.length});
        }
    }
    return reversed;
}

// dynamic programming: distance_table[i][vertex] is the minimum length of a source-vertex
// path with <= i edges

// shortest path distance from source to all other vertice
using ShortestPathDistances = std::vector<int>;


// return shortest path distances if exist, return empty optional if no shortest
// path, i.e. negative cost cycles exist
std::optional<ShortestPathDistances>
BellmanFord(const Graph& graph, unsigned source_node) {
    
    auto reversed = reverseAdjlist(graph);

    auto distance_table =
        std::vector< std::vector<int> >
        (graph.size() + 1, // additional iteration for cycle check
         std::vector<int>(graph.size(), std::numeric_limits<int>::max()));
    
    distance_table[0][source_node] = 0;

    for (size_t iteration = 1; iteration <= graph.size(); ++iteration) {
        for (size_t vertex = 0; vertex < graph.size(); ++vertex) {
            
            // find minimum of including additional edge
            auto min_of_including_edge = std::numeric_limits<int>::max();
            
            for (auto const & incoming_edge : reversed.adjlist[vertex]) {
                auto cost_without_last_hop =
                    distance_table[iteration-1][incoming_edge.target];
                if (cost_without_last_hop == std::numeric_limits<int>::max()) {
                    continue; // no such path
                }
                auto cost_with_last_hop = cost_without_last_hop + incoming_edge.length;
                if (cost_with_last_hop < min_of_including_edge) {
                    min_of_including_edge = cost_with_last_hop;
                }
            }
            
            distance_table[iteration][vertex] =
                std::min(distance_table[iteration-1][vertex], min_of_including_edge);
        }
    }

    // check for negative cycle
    for (size_t vertex = 0; vertex < graph.size(); ++vertex) {
        if (distance_table[graph.size()][vertex] !=
            distance_table[graph.size()-1][vertex]) {
            return {};
        }
    }
    
    return distance_table[graph.size()];
}
#endif
