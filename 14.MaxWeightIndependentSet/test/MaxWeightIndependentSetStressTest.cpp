#include <iostream>
#include <vector>
#include "UniformRandom.hpp"
#include "MaxWeightIndependentSet.hpp"

using namespace DynamicProgramming;

unsigned totalWeightOfMWISNaive(const std::vector<unsigned>& path) {
    if (path.empty()) return 0;
    if (path.size() == 1) return path[0];
    auto include_node = path[path.size()-1] +
        totalWeightOfMWISNaive(std::vector<unsigned>(std::begin(path),
                                                     std::end(path) - 2));
    auto exclude_node = totalWeightOfMWISNaive
        (std::vector<unsigned>(std::begin(path), std::end(path) - 1));
    return std::max(include_node, exclude_node);
}

int main()
{
    UniformRandom<unsigned> path_size_rng(0, 20);
    UniformRandom<unsigned> node_weight_rng(0, 100);

    for (int trials = 0; trials < 10000; ++trials) {
        std::vector<unsigned> path;
        auto n_nodes = path_size_rng.generate();
        for (auto i = 0u; i < n_nodes; ++i) {
            path.push_back(node_weight_rng.generate());
        }
        auto expected = totalWeightOfMWISNaive(path);
        auto actual = totalWeightOfMWIS(path);
        if (expected == actual) {
            std::cout << "OK\n";
        } else {
            std::cout << "WRONG\n";
            return 0;
        }
    }
    return 0;
}
