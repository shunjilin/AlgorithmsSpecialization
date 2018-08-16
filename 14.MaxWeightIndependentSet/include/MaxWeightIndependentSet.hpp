#ifndef MAX_WEIGHT_INDEPENDENT_SET_HPP
#define MAX_WEIGHT_INDEPENDENT_SET_HPP

#include <vector>
#include <algorithm>
#include <set>

namespace DynamicProgramming {

    std::vector<unsigned> computeMWIS(const std::vector<unsigned>& path) {
        auto MWIS_table = std::vector<unsigned>(path.size() + 1);
        MWIS_table[0] = 0;
        if (path.empty()) return MWIS_table;
        MWIS_table[1] = path[0];
        for (auto i = 2u; i <= path.size(); ++i) {
            auto include_node = MWIS_table[i-2] + path[i-1];
            auto exclude_node = MWIS_table[i-1];
            MWIS_table[i] = std::max(include_node, exclude_node);
        }
        return MWIS_table;
    }

    unsigned totalWeightOfMWIS(const std::vector<unsigned>& path) {
        return computeMWIS(path)[path.size()];
    }

    std::set<unsigned> getIndexOfMWISNodes(const std::vector<unsigned>& path) {
        auto MWIS_nodes = std::set<unsigned>();
        if (path.empty()) return MWIS_nodes;
        if (path.size() == 1) {
            MWIS_nodes.emplace(path[0]);
            return MWIS_nodes;
        }
        auto MWIS_table = computeMWIS(path);
        int i = path.size();
        while (i > 0) {
            if (MWIS_table[i-1] >= (MWIS_table[i-2] + path[i-1])) {
                --i;
            } else {
                MWIS_nodes.emplace(i-1);
                i -= 2;
            }
        }
        return MWIS_nodes;
    }
}

#endif
