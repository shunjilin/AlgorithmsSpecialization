#ifndef MINIMUM_SPANNING_TREE_HPP
#define MINIMUM_SPANNING_TREE_HPP

#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <limits>

namespace PrimsAlgorithm {

    struct Edge {
        unsigned source;
        unsigned target;
        int cost;
        bool operator>(const Edge& rhs) const {
            return cost > rhs.cost;
        }
    };
        
    struct Graph {
        std::vector<std::vector<Edge> > adjlist;
        Graph() {}
        Graph(unsigned n_nodes) : adjlist(n_nodes) {}
        void insertEdge(Edge edge) {
            adjlist[edge.source].push_back(edge);
            std::swap(edge.source, edge.target);
            adjlist[edge.source].push_back(edge);
        }
        const std::vector<Edge>& getEdgesOfNode(unsigned node) const {
            return adjlist[node];
        }
        unsigned getNumberOfNodes() const {
            return adjlist.size();
        }
    };

    struct FrontierNode {
        unsigned node;
        Edge edge;
    };
    
    std::priority_queue
    <Edge, std::vector<Edge>, std::greater<Edge> >
    initializeFrontier(const Graph& graph) {
        auto frontier = std::priority_queue<Edge, std::vector<Edge>,
                                            std::greater<Edge> >();
        for (auto edge : graph.getEdgesOfNode(0)) {
            frontier.push(edge);
        }
        return frontier;
    }

    void updateFrontier(unsigned node, const Graph& graph,
                        std::priority_queue<Edge, std::vector<Edge>,
                        std::greater<Edge> >& frontier) {
        for (auto edge : graph.getEdgesOfNode(node)) {
            frontier.push(edge);
        }
    }
    
    int computeMinimumSpanningTreeCost(const Graph& graph) {
        auto n_nodes = graph.getNumberOfNodes();
        if (n_nodes == 0) return 0;
        int min_spanning_tree_cost = 0;
        auto processed_nodes = std::set<unsigned>();
        processed_nodes.insert(0);
        auto frontier = initializeFrontier(graph);
        while(!frontier.empty()) {
            auto frontier_edge = frontier.top();
            frontier.pop();
            if (processed_nodes.find(frontier_edge.target) !=
                processed_nodes.end()) {
                continue;
            }
            processed_nodes.insert(frontier_edge.target);
            min_spanning_tree_cost += frontier_edge.cost;
            updateFrontier(frontier_edge.target, graph, frontier);
        }
        return min_spanning_tree_cost;
    }
}

#endif
