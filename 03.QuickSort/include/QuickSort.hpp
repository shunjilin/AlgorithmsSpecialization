#ifndef QUICKSORT_HPP
#define QUICKSORT_HPP
#include <algorithm>

namespace QuickSort {

    template <typename I>
    I getMid(const I begin, const I end) {
        auto size = end - begin;
        auto mid_offset = size % 2 == 0 ? size / 2 - 1 : size / 2;
        return begin + mid_offset;
    }

    template <typename I, typename Compare>
    I getMedianOfThree(const I one, const I two, const I three,
                       Compare comp) {
        auto median = std::max(std::min(*one, *two, comp),
                            std::min(std::max(*one, *two, comp),
                                     *three, comp), comp);
        if (*one == median) return one;
        if (*two == median) return two;
        return three; // *three == median
    }
    
    template <typename I, typename Compare = std::less<typename I::value_type> >
    struct firstPivot {
        I operator()(const I begin, const I end,
                     const Compare comp = Compare()) const {
            return (begin == end) ? end : begin;
        }
    };

    template <typename I, typename Compare = std::less<typename I::value_type> >
    struct lastPivot {
        I operator()(const I begin, const I end,
                     const Compare comp = Compare()) const {
            return (begin == end) ? end : end-1;
        }
    };

    template <typename I, typename Comp>
    struct medianOfThreePivot {
        I operator()(const I begin, const I end, const Comp comp) const {
            if (begin == end) {
                return end;
            } else {
                return getMedianOfThree(begin, getMid(begin, end), end-1, comp);
            }
        }
    };

    template<typename I, typename Compare>
    I partition(const I begin, const I end, const I pivot,
                   const Compare comp) {
        if (end - begin <= 1) return begin;
        using std::swap;
        swap(*begin, *pivot);
        I greater_begin = begin + 1, unpartitioned_begin = begin + 1;
        while (unpartitioned_begin != end) {
            if (comp(*unpartitioned_begin, *begin)) {
                swap(*unpartitioned_begin, *greater_begin);
                ++greater_begin;
            }
            ++unpartitioned_begin;
        }
        swap(*begin, *(greater_begin - 1));
        return greater_begin - 1;
    }

    template <typename I, typename ChoosePivot,
              typename Compare = std::less<typename I::value_type> >
    void sort(const I begin, const I end,
              const ChoosePivot choosePivot,
              unsigned long long *comparisons = nullptr,
              const Compare comp = Compare()) {
        if (end - begin <= 1) return;
        if (comparisons) *comparisons += end - begin - 1;
        auto pivot = choosePivot(begin, end, comp);
        pivot = partition(begin, end, pivot, comp); 
        sort(begin, pivot, choosePivot, comparisons, comp);
        sort(pivot + 1, end, choosePivot, comparisons, comp);
    }
};

#endif
