#ifndef UNION_FIND_HPP
#define UNION_FIND_HPP

#include <algorithm>
#include <vector>
#include <iostream>

namespace DataStructures {

    class UnionFind {
        std::vector<unsigned> parent;
        std::vector<unsigned> rank;
    public:
        std::size_t size() const { return parent.size(); }
        UnionFind(unsigned size) : parent(size) , rank(size, 0) {
            std::iota(std::begin(parent), std::end(parent), 0);
        }
        void doUnion(unsigned x, unsigned y) {
            x = find(x);
            y = find(y);
            if (rank[x] < rank[y]) {
                parent[x] = y;
            } else if (rank[y] < rank[x]) {
                parent[y] = x;
            } else {
                parent[x] = y;
                ++rank[y];
            }
        }
        unsigned find(unsigned x) {
            while (x != parent[x]) {
                parent[x] = parent[parent[x]];
                x = parent[x];
            }
            return x;
        }

        bool sameRoot(unsigned x, unsigned y) {
            return find(x) == find(y);
        }
    };

}

#endif
