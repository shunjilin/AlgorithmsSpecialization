#ifndef CLUSTERING_BIG_HPP
#define CLUSTERING_BIG_HPP

#include <vector>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include "BitstringFunctions.hpp"
#include "UnionFind.hpp"

namespace ClusteringBig {
    unsigned kValueForSpacingOfAtLeast3(const std::vector<int>& nodes,
                                        unsigned n_bits) {
        auto _nodes = std::unordered_set<int>(std::begin(nodes),
                                              std::end(nodes));
        auto clusters = DataStructures::UnionFind(pow(2, n_bits));
        unsigned n_clusters = _nodes.size();
        for (auto node : nodes) {
            auto distance_one_generator =
                BitstringFunctions::DistanceOneGenerator(node, n_bits);
            while (!distance_one_generator.done) {
                auto generated = distance_one_generator.generate();
                if (_nodes.find(generated) != _nodes.end() &&
                    !clusters.sameRoot(node, generated)) {
                    clusters.doUnion(node, generated);
                    n_clusters--;
                }
            }
            auto distance_two_generator =
                BitstringFunctions::DistanceTwoGenerator(node, n_bits);
            while (!distance_two_generator.done) {
                auto generated = distance_two_generator.generate();
                if (_nodes.find(generated) != _nodes.end() &&
                    !clusters.sameRoot(node, generated)) {
                    clusters.doUnion(node, generated);
                    n_clusters--;
                }
            }
        }
        return n_clusters;
    }
}

#endif
