#ifndef MINIMUM_SPANNING_TREE_HPP
#define MINIMUM_SPANNING_TREE_HPP

#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_set>
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


    bool nodeInClosed(unsigned node,
                      const std::unordered_set<unsigned>& closed) {
        return closed.find(node) == closed.end();
    }
    
    void updateFrontier(unsigned node, const Graph& graph,
                        std::priority_queue<Edge, std::vector<Edge>,
                        std::greater<Edge> >& frontier,
                        const std::unordered_set<unsigned>& closed =
                        std::unordered_set<unsigned>()) {
        for (auto edge : graph.getEdgesOfNode(node)) {
            if (nodeInClosed(edge.target, closed)) {
                frontier.push(edge);
            }
        }
    }
    
    int computeMinimumSpanningTreeCost(const Graph& graph) {
        auto n_nodes = graph.getNumberOfNodes();
        if (n_nodes == 0) return 0;
        int min_spanning_tree_cost = 0;

        // initialize closed (stores processed nodes) and
        // frontier (stores potential edges to add to spanning tree)
        auto closed = std::unordered_set<unsigned>();
        closed.insert(0);
        auto frontier = std::priority_queue<Edge, std::vector<Edge>,
                                            std::greater<Edge> >();
        updateFrontier(0, graph, frontier, closed);
        
        while(!frontier.empty()) {
            auto frontier_edge = frontier.top();
            frontier.pop();
            if (nodeInClosed(frontier_edge.target, closed)) {
                closed.insert(frontier_edge.target);
                min_spanning_tree_cost += frontier_edge.cost;
                updateFrontier(frontier_edge.target, graph, frontier, closed);
            }
        }
        return min_spanning_tree_cost;
    }
}

#endif
