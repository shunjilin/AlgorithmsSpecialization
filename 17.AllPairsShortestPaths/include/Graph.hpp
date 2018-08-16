#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>

// common graph data structure to be used by graph algorithms
struct Edge {
    int source;
    int target;
    int length;
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

#endif
