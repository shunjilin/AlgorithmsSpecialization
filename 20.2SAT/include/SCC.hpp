#ifndef SCC_HPP
#define SCC_HPP

#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_map>

namespace SCC {

    struct Edge {
        unsigned source;
        unsigned target;
    };

    struct Graph {
        std::vector< std::vector<unsigned> > adjlist;

        Graph(std::size_t size) : adjlist(size) {}
        Graph(std::size_t size, std::vector<Edge> edges) : adjlist(size) {
            for (auto edge : edges) addEdge(edge);
        }
        void addEdge(Edge edge) {
            adjlist[edge.source].push_back(edge.target);
        }
        std::size_t size() const {
            return adjlist.size();
        }
    };

    void reverseEdge(Edge& edge) {
        std::swap(edge.source, edge.target);
    }

    template<typename F>
    void DFS(const Graph& graph, std::vector<bool>& visited,
             unsigned node, F postDFSWork) {
        if (visited[node]) return;
        visited[node] = true;
        for (auto target : graph.adjlist[node]) {
            if (!visited[target]) {
                DFS(graph, visited, target, postDFSWork);
            }
        }
        postDFSWork(node);
    }

    using FinishingTimes = std::vector<unsigned>;    
    FinishingTimes kosarajuFirstPass(const Graph& reversed_graph) {
        unsigned finishing_time = 0;
        FinishingTimes finishing_times(reversed_graph.size());
        std::vector<bool> visited(reversed_graph.size(), false);
        for (unsigned node = 0; node < reversed_graph.size(); ++node) {
            if (!visited[node]) {
                DFS(reversed_graph, visited, node,
                    [&](unsigned node) {
                        finishing_times[node] = finishing_time++;
                    });
            }
        }
        return finishing_times;
    }

    using NodeToLeader = std::vector<unsigned>;
    NodeToLeader kosarajuSecondPass(const Graph& graph,
                                    const FinishingTimes& finishing_times) {
        std::vector<unsigned> time_to_node(graph.size());
        for (std::size_t node = 0; node < graph.size(); ++node) {
            time_to_node[finishing_times[node]] = node;
        }
        std::vector<bool> visited(graph.size(), false);
        NodeToLeader node_to_leader(graph.size());
        for (auto node_it = time_to_node.rbegin();
             node_it != time_to_node.rend(); ++node_it) {
            if (!visited[*node_it]) {
                unsigned leader = *node_it;
                DFS(graph, visited, *node_it,
                    [&](unsigned node) {
                        node_to_leader[node] = leader;
                    });
            }
        }
        return node_to_leader;
    }

    NodeToLeader computeSCC(std::size_t n_nodes,
                                            std::vector<Edge> edges) {
        Graph graph = Graph(n_nodes, edges);
        for (auto& edge : edges) {
            reverseEdge(edge);
        }
        Graph reversed_graph = Graph(n_nodes, edges);
        auto finishing_times = kosarajuFirstPass(reversed_graph);
        auto node_to_leader = kosarajuSecondPass(graph, finishing_times);
        return node_to_leader;
    }
    
}

#endif
