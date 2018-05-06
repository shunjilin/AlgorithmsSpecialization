#ifndef KNAPSACK_HPP
#define KNAPSACK_HPP
#include <vector>

namespace DynamicProgramming {
    struct KnapsackObject {
        unsigned value;
        unsigned weight;
    };

    unsigned
    computeOptimalKnapsackValue(const std::vector<KnapsackObject>& objects,
                                unsigned max_weight) {
        auto table = std::vector< std::vector<unsigned> >
            (objects.size() + 1, std::vector<unsigned>(max_weight + 1, 0));
        for (auto item = 1u; item <= objects.size(); ++item) {
            auto obj_value = objects[item - 1].value;
            auto obj_weight = objects[item - 1].weight;
            for (auto total_weight = 1u; total_weight <= max_weight; ++total_weight) {
                // don't choose item
                table[item][total_weight] = table[item-1][total_weight];
                // choose item
                if (obj_weight <= total_weight) {
                    auto total_value =
                        obj_value + table[item-1][total_weight - obj_weight];
                    if (total_value > table[item][total_weight]) {
                        table[item][total_weight] = total_value;
                    }
                }
            }
        }
        return table[objects.size()][max_weight];
    }
}

#endif
