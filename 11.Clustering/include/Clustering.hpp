#ifndef CLUSTERING_HPP
#define CLUSTERING_HPP

#include <vector>
#include <algorithm>
#include "UnionFind.hpp"

namespace Clustering {
    struct Edge {
        unsigned node1;
        unsigned node2;
        unsigned cost;
        bool operator<(const Edge& other) const {
            return cost < other.cost;
        }
    };
    
    unsigned maxSpacingKClustering(unsigned n_nodes, std::vector<Edge>& edges,
                                   unsigned k) {
        auto clusters = DataStructures::UnionFind(n_nodes);
        unsigned n_clusters = n_nodes;
        std::sort(std::begin(edges), std::end(edges));
        for (auto & edge : edges) {
            if (!clusters.sameRoot(edge.node1, edge.node2)) {
                if (n_clusters == k) return edge.cost;
                clusters.doUnion(edge.node1, edge.node2);
                n_clusters--;
            }
        }
        return 0;
    }
}

#endif
