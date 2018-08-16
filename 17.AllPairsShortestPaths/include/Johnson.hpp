#ifndef JOHNSON_HPP
#define JOHNSON_HPP

#include "Graph.hpp"
#include "BellmanFord.hpp"
#include "Dijkstra.hpp"

// preprocessing step of Johnson's algorithm,
// new source vertex s is added with edges to every vertex in graph
Graph JohnsonPreProcess(Graph graph) {
    auto new_source_vertex = (int)graph.size();
    graph.adjlist.emplace_back(); // entry for new source vertex
    for (auto vertex = 0; vertex < new_source_vertex; ++ vertex) {
        graph.addEdge(Edge{new_source_vertex, vertex, 0}); // add edge of cost 0
    }
    return graph;
}

// Johnson's algorithm, return 2d array of all pairs shortest paths
std::optional< std::vector< std::vector<int> > >
Johnson(Graph const & graph) {
    auto preprocessed_graph = JohnsonPreProcess(graph);
    auto preprocessed_distances = BellmanFord(preprocessed_graph, graph.size());
    if (!preprocessed_distances.has_value()) return {};
    for (auto & edges : preprocessed_graph.adjlist) {
        for (auto & edge : edges) {
            // adjust lengths to non negative while preserving shortest path lengths
            // (plus addition of constant) to allow for dijkstra's algorithm
            edge.length +=
                (preprocessed_distances.value()[edge.source] -
                 preprocessed_distances.value()[edge.target]);
        }
    }
    
    preprocessed_graph.adjlist.pop_back(); // remove preprocessing node
    
    auto adjusted_shortest_paths =
        std::vector< std::vector<int> >(graph.size(),
                                        std::vector<int>(graph.size()));
    // perform Dijkstra from every vertex
    for (size_t vertex = 0; vertex < graph.size(); ++vertex) {
        adjusted_shortest_paths[vertex] =
            Dijkstra(preprocessed_graph, vertex);
    }

    // reweight for actual shortest paths
    for (size_t u = 0; u < graph.size(); ++u) {
        for (size_t v = 0; v < graph.size(); ++v) {
            adjusted_shortest_paths[u][v] -= (preprocessed_distances.value()[u] -
                                              preprocessed_distances.value()[v]);
        }
    }
    return adjusted_shortest_paths;
}

std::optional<int> shortestShortestPath(Graph const & graph) {
    auto all_pairs_shortest_paths = Johnson(graph);
    if (!all_pairs_shortest_paths.has_value()) return {};
    int shortest_shortest_path = std::numeric_limits<int>::max();
    for (auto const & distances : all_pairs_shortest_paths.value()) {
        for (auto distance : distances) {
            if (distance < shortest_shortest_path) {
                shortest_shortest_path = distance;
            }
        }
    }
    return shortest_shortest_path;
}

#endif
