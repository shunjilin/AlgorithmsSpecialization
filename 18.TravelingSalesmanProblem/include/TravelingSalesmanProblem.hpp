#ifndef TRAVELING_SALESMAN_PROBLEM_HPP
#define TRAVELING_SALESMAN_PROBLEM_HPP

#include <cmath>
#include <limits>
#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>

struct Vertex {
    double x;
    double y;
    Vertex(double x, double y) : x(x), y(y) {}
};

double euclideanDistance(Vertex const & v1, Vertex const & v2) {
    return sqrt(pow((v1.x - v2.x), 2) + pow((v1.y - v2.y), 2));
}

int countSetBits(int bitstring) {
    int count = 0;
    while (bitstring != 0) {
        bitstring &= (bitstring - 1);
        ++count;
    }
    return count;
}

// check if bit is set for element at index (index from right)
bool isBitSetAtIndex(int bitstring, int index) {
    return (bitstring & (1 << index)) != 0;
}

// append first element which is always set for TSP
int offsetByOneAndSetOne(int bitstring) {
    bitstring <<= 1;
    bitstring += 1;
    return bitstring;
}

// set or unset bit at index
int setBitAtIndex(int bitstring, int index) {
    int mask = 1 << index;
    return bitstring ^ mask;
}

// get 2d array of euclidean distances between any two vertices
std::vector< std::vector<double> >
getEuclideanDistanceTable(std::vector<Vertex> const & vertices) {
    auto distances = std::vector< std::vector<double> >
        (vertices.size(), std::vector<double>(vertices.size()));
    for (size_t i = 0; i < vertices.size(); ++i) {
        for (size_t j = 0; j < vertices.size(); ++j) {
            distances[i][j] = euclideanDistance(vertices[i], vertices[j]);
        }
    }
    return distances;
}

// associates bistring subset to subset size
struct Subset {
    int subset;
    size_t size;
    Subset(int subset) : subset(subset) {
        size = countSetBits(subset);
    }
    // order by increasing subset size
    bool operator<(const Subset& rhs) const {
        return size < rhs.size;
    }
    bool operator==(const Subset& rhs) const {
        return subset == rhs.subset;
    }
};

std::vector<Subset> getTSPSubsets(int n_vertices) {
    std::vector<Subset> subsets;
    for (int subset = 0, max = pow(2, n_vertices-1); subset < max; ++subset) {
        subsets.emplace_back(Subset(offsetByOneAndSetOne(subset)));
    }
    std::sort(subsets.begin(), subsets.end());
    return subsets;
}

double getTSPvalue(std::vector<Vertex> const & vertices) {
    auto n_vertices = vertices.size();
    
    if (n_vertices < 2) return 0;

    auto distances = getEuclideanDistanceTable(vertices);
    
    auto subsets = getTSPSubsets(n_vertices);

    // shortest path from i to j that visits ever vertex of subset size k once
    auto table = std::vector< std::vector<double> >
        (pow(2, n_vertices), std::vector<double>
         (n_vertices, std::numeric_limits<double>::max()));

// base case: shortest path from vertex 0 to 0
    auto base_case_subset = offsetByOneAndSetOne(0);
    table[base_case_subset][0] = 0;

    int subset_index = 1;
    for (size_t subset_size = 2; subset_size <= n_vertices; ++subset_size) {
        while (subsets[subset_index].size == subset_size) {
            auto subset = subsets[subset_index].subset;
            for (size_t j = 1; j < n_vertices; ++j) { // j is last hop vertex
                auto subset_less_j = setBitAtIndex(subset, j);
                // shortest path from 1 to k
                for (size_t k = 0; k < n_vertices; ++k) {
                    if (k != j) {
                        auto candidate_value = table[subset_less_j][k] +
                            distances[k][j];
                        if (candidate_value < table[subset][j])
                            table[subset][j] = candidate_value;
                    }
                }
            }
            ++subset_index;
        }
    }
    
    auto min_value = std::numeric_limits<double>::max();
    auto & all_vertices_visited = table[pow(2, n_vertices) - 1];
    for (size_t j = 1; j < n_vertices; ++j) {
        auto candidate_value =
            all_vertices_visited[j] + distances[j][0];
        if (candidate_value < min_value) min_value = candidate_value;
    }
    return min_value;
}


#endif
