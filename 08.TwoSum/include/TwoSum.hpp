#ifndef TWO_SUM_HPP
#define TWO_SUM_HPP

#include <vector>
#include <set>
#include <unordered_set>


namespace TwoSum {
    int getNumOfTwoSumsInRange(const std::vector<long>& summands,
                               long min_sum, long max_sum) {
        std::set<long> summands_copy(std::begin(summands), std::end(summands));
        std::unordered_set<long> sums;
        for (auto first_summand : summands_copy) {
            auto second_summand_begin = summands_copy.lower_bound(min_sum-first_summand);
            auto second_summand_end = summands_copy.upper_bound(max_sum-first_summand);
            for (auto second_summand_it = second_summand_begin;
                 second_summand_it != second_summand_end; ++second_summand_it) {
                if (first_summand != *second_summand_it) {
                    sums.insert(first_summand + *second_summand_it);
                }
            }
        }
        return sums.size();
    };
}

#endif
