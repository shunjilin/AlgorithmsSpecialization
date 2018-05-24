#ifndef WEIGHTED_SUM_OF_COMPLETION_TIMES_HPP
#define WEIGHTED_SUM_OF_COMPLETION_TIMES_HPP

#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>

namespace WeightedSumOfCompletionTimes {
    struct Job {
        unsigned weight;
        unsigned length;
    };

    long differenceScore(const Job& job) {
        return static_cast<long>(job.weight) - job.length;
    }

    struct DifferenceComparator {
        bool operator()(const Job& lhs, const Job& rhs) const {
            auto difference_score_lhs = differenceScore(lhs);
            auto difference_score_rhs = differenceScore(rhs);
            if (difference_score_lhs == difference_score_rhs) {
                return lhs.weight > rhs.weight;
            }
            return differenceScore(lhs) > differenceScore(rhs);
        }
    };

    double ratioScore(const Job& job) {
        return static_cast<double>(job.weight) / job.length;
    }

    struct RatioComparator {
        bool operator()(const Job& lhs, const Job& rhs) const {
            return ratioScore(lhs) > ratioScore(rhs);
        }
    };

    template<class RandomIt, class Compare>
    long unsigned computeWeightedSumOfCompletionTimes(RandomIt first,
                                                 RandomIt last,
                                                 Compare comp) {
        auto jobs =
            std::vector<typename std::iterator_traits<RandomIt>::value_type>
            (first, last);
        std::sort(std::begin(jobs), std::end(jobs), comp);
        long unsigned cumulated_length = 0;
        
        return std::accumulate(std::begin(jobs), std::end(jobs),
                               static_cast<long unsigned>(0),
                               [&](long unsigned weighted_sum, const Job& job) {
                                   cumulated_length += job.length;
                                   return weighted_sum +
                                       job.weight * cumulated_length;
                        });
    }

}

#endif
