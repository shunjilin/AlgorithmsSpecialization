#ifndef KARGERS_MIN_CUT_HPP
#define KARGERS_MIN_CUT_HPP

#include <vector>
#include <limits>
#include "UnionFind.hpp"

namespace Kargers {
    using namespace DataStructures;
    
    struct Edge {
        unsigned source;
        unsigned target;
        Edge(unsigned source, unsigned target) :
            source(source), target(target) {}
    };

    using Edgelist = std::vector<Edge>;
    
    bool isMerged(UnionFind& graph, unsigned x, unsigned y) {
        return (graph.find(x) == graph.find(y));
    }

    void contract(UnionFind& graph, unsigned x, unsigned y) {
        graph.doUnion(x, y);
    }

    template<class URBG>
    unsigned getEdgeCountFromRandomContract(unsigned n_nodes,
                                            Edgelist edge_list,
                                            URBG&& gen) {
        auto graph = UnionFind(n_nodes);
        std::shuffle(std::begin(edge_list), std::end(edge_list),
                     std::forward<URBG>(gen));
        
        while (!edge_list.empty() && n_nodes > 2) {
            auto edge = edge_list.back();
            edge_list.pop_back();
            if (!isMerged(graph, edge.source, edge.target)) {
                contract(graph, edge.source, edge.target);
                --n_nodes;
            }
        }
        unsigned edge_count = 0;
        for (auto edge : edge_list) {
            if (!isMerged(graph, edge.source, edge.target)) {
                ++edge_count;
            }
        }
        return edge_count;
    } 
}

#endif
