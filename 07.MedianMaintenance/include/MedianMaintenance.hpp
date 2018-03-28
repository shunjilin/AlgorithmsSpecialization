#ifndef MEDIAN_MAINTENANCE_HPP
#define MEDIAN_MAINTENANCE_HPP

#include <queue>
#include <algorithm>

namespace DataStructures {
    template<typename T>
    class MedianMaintenance {
        std::priority_queue<T> lower_half;
        std::priority_queue<T, std::vector<T>, std::greater<T> > upper_half;

        void maintainInvariance() {
            if (lower_half.size() > upper_half.size() + 1) {
                upper_half.push(lower_half.top());
                lower_half.pop();
            }
            if (upper_half.size() > lower_half.size()) {
                lower_half.push(upper_half.top());
                upper_half.pop();
            }
        }
        
    public:        
        void push(T element) {
            if (lower_half.empty() || element <= lower_half.top()) {
                lower_half.push(element);
            } else {
                upper_half.push(element);
            }
            maintainInvariance();
        }

        T getMedian() const {
            return lower_half.top();
        }

    };
}

#endif
