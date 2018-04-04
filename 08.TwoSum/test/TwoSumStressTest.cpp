#include <iostream>
#include <vector>
#include <unordered_set>
#include "UniformRandom.hpp"
#include "TwoSum.hpp"

long getNumOfTwoSumsInRangeNaive(const std::vector<long>& summands,
                                long min_sum, long max_sum) {
    std::unordered_set<long> sums;
    for (std::size_t i = 0; i < summands.size(); ++i) {
        for (std::size_t j = i + 1; j < summands.size(); ++j) {
            auto sum = summands[i] + summands[j];
            if (summands[i] != summands[j] && sum >= min_sum && sum <= max_sum) {
                sums.insert(sum);
            }
        }
    }
    return sums.size();
}

int main()
{
    UniformRandom<long> min_sum_rng(-1000, 0);
    UniformRandom<long> max_sum_rng(0, 1000);
    UniformRandom<long> summands_rng(-1000, 1000);

    for (int trials = 0; trials < 10000; ++trials) {
        std::vector<long> summands;
        auto min_sum = min_sum_rng.generate();
        auto max_sum = max_sum_rng.generate();
        for (int n_summands = 0; n_summands < 100; ++n_summands) {
            summands.push_back(summands_rng.generate());
        }
        auto expected = getNumOfTwoSumsInRangeNaive(summands, min_sum, max_sum);
        auto actual = TwoSum::getNumOfTwoSumsInRange(summands, min_sum, max_sum);

        if (expected == actual) {
            std::cout << "OK\n";
        } else {
            std::cout << "WRONG\n";
            return 0;
        }
    }
}
