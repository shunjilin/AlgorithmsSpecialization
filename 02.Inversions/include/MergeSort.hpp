#ifndef MERGE_SORT_HPP
#define MERGE_SORT_HPP

#include <utility>
#include <algorithm>
#include <memory>

// Trying out iterators, sorry if its too verbose
namespace MergeSort {
    
    template <typename I, typename Compare>
    void merge(const I first_begin, const I first_end,
               const I second_begin, const I second_end,
               I merge_space_begin,
               int* inversion_count, const Compare comp) {
        I lower = first_begin, upper = second_begin, merge = merge_space_begin;
        while (lower != first_end && upper != second_end) {
            if (comp(*lower, *upper)) {
                (*merge++) = (*lower++);
            } else {
                (*merge++) = (*upper++);
                if (inversion_count) *inversion_count += first_end - lower;
            }
        }
        std::move(lower, first_end, merge);
        std::move(upper, second_end, merge);
    }

    template<typename I, typename Compare>
    void sortHelper(const I begin, const I end,
                    const I merge_space_begin,
                    int *inversion_count,
                    const Compare comp) {
        auto n = end - begin;
        if (n <= 1) return;
        auto midpoint = n / 2;
        sortHelper(begin, begin + midpoint, merge_space_begin,
                   inversion_count, comp);
        sortHelper(begin + midpoint, end, merge_space_begin + midpoint,
                   inversion_count, comp);
        merge(begin, begin + midpoint, begin + midpoint, end,
              merge_space_begin, inversion_count, comp);
        std::move(merge_space_begin, merge_space_begin + n, begin);
    }

    template <typename I, typename Compare = std::less< typename I::value_type> >
    void sort(const I begin, const I end,
              int* inversion_count = nullptr,
              const Compare comp = Compare()) {
        std::vector<typename I::value_type> merge_space(end - begin); 
        sortHelper(begin, end, std::begin(merge_space), inversion_count, comp);
    }

    template<typename I, typename Compare = std::less< typename I::value_type> >
    int sortAndGetInversionCount(const I begin, const I end,
                                 const Compare comp = Compare()) {
        int inversion_count = 0;
        sort(begin, end, &inversion_count, comp);
        return inversion_count;
    }
};
#endif
