#ifndef KNAPSACK_BIG_HPP
#define KNAPSACK_BIG_HPP
#include <vector>
#include <unordered_map>
#include <iterator>
#include <utility>
#include <algorithm>

namespace Memoization {
    struct KnapsackObject {
        unsigned value;
        unsigned weight;
    };
    
    using n_items_weight_pair = std::pair<unsigned, unsigned>;
    
    struct Hasher { // hash for n_items_weight_pair
	// adapted from boost hash_combine
	std::size_t operator()(const n_items_weight_pair& key) const {
	    return key.first + 0x9e3779b9 + (key.second << 6) + (key.second >> 2);
	}
    };
    
    using value_cache = std::unordered_map<n_items_weight_pair, unsigned, Hasher>;

    // Recursive implementation
    template<typename Iterator>
    unsigned
    computeOptimalKnapsackValueAux(const Iterator begin, const Iterator end,
                                   unsigned max_weight,
                                   value_cache& cache) {
        if (end <= begin || max_weight == 0) return 0;
        auto n_items = std::distance(begin, end);
        auto cached =
            cache.find(std::make_pair(n_items, max_weight));
        if (cached != cache.end()) return cached->second;
        auto obj_weight = (end-1)->weight;
        auto obj_value = (end-1)->value;
        unsigned value_if_select = 0;
        if (obj_weight <= max_weight) {
            value_if_select =
                obj_value + computeOptimalKnapsackValueAux(begin, end - 1,
                                                           max_weight - obj_weight,
                                                           cache);   
        }
        unsigned value_if_not_select =
            computeOptimalKnapsackValueAux(begin, end - 1, max_weight, cache);

        auto optimal_value = std::max(value_if_select, value_if_not_select);
        cache[std::make_pair(n_items, max_weight)] = optimal_value;
        return optimal_value;
    }

    unsigned
    computeOptimalKnapsackValue(const std::vector<KnapsackObject>& objects,
                                         unsigned max_weight) {
        value_cache cache;
        return computeOptimalKnapsackValueAux(std::begin(objects),
                                              std::end(objects), max_weight,
                                              cache);
        return objects.size();
    }
}

#endif
