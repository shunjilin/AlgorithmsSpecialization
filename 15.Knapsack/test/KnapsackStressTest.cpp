#include <iostream>
#include <vector>
#include "UniformRandom.hpp"
#include "Knapsack.hpp"

// recursive
unsigned
computeOptimalKnapsackValue(std::vector<DynamicProgramming::KnapsackObject> objects,
                            unsigned max_weight) {
    if (max_weight == 0 || objects.size() == 0) return 0;
    auto obj_weight = objects.back().weight;
    auto obj_value = objects.back().value;
    objects.pop_back();
    unsigned choose = (obj_weight <= max_weight) ?
        obj_value + ::computeOptimalKnapsackValue(objects,
                                                max_weight - obj_weight) : 0;
    unsigned dont_choose = ::computeOptimalKnapsackValue(objects, max_weight);
    return std::max(choose, dont_choose);
}

int main()
{
    UniformRandom<unsigned> value_rng(0, 100);
    UniformRandom<unsigned> weight_rng(0, 100);
    UniformRandom<unsigned> n_weights_rng(0, 2);

    for (int trials = 0; trials < 1000; ++trials) {
        std::vector<DynamicProgramming::KnapsackObject> objects(n_weights_rng.generate());
        for (std::size_t i = 0; i < objects.size(); ++i) {
            objects[i].value = value_rng.generate();
            objects[i].weight = weight_rng.generate();
        }
        unsigned max_weight = weight_rng.generate();
        auto expected_optimal_value = ::computeOptimalKnapsackValue(objects, max_weight);
        auto actual_optimal_value = DynamicProgramming::computeOptimalKnapsackValue(objects, max_weight);
        if (expected_optimal_value == actual_optimal_value) {
            std::cout << "OK\n";
        } else {
            std::cout << "WRONG\n"
                      << "Max weight: " << max_weight
                      << "\nWeights: ";
            for (auto object : objects) {
                std::cout << "weight : " << object.weight
                          << " value : " << object.weight;
            }
            std::cout << "\nExpected optimal value : " << expected_optimal_value
                      << "\nActual optimal value : " << actual_optimal_value
                      << "\n";
            return 0;
        }
    }
}
