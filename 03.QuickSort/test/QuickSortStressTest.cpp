#include <iostream>
#include <vector>
#include "UniformRandom.hpp"
#include "QuickSort.hpp"

int main()
{
    UniformRandom<unsigned> vector_size_rng(0, 10000);
    UniformRandom<int> number_rng(-1000, 1000);

    for (int i = 0; i < 10000; ++i) {
        std::vector<int>firstPivotCase(vector_size_rng.generate());
        std::generate(std::begin(firstPivotCase), std::end(firstPivotCase),
                      std::bind(&UniformRandom<int>::generate, number_rng));
        std::vector<int>lastPivotCase(std::begin(firstPivotCase),
                                      std::end(firstPivotCase));
        std::vector<int>medianPivotCase(std::begin(firstPivotCase),
                                        std::end(firstPivotCase));
        unsigned long long comparisons_first = 0, comparisons_last = 0,
            comparisons_median = 0;
        
        QuickSort::sort(std::begin(firstPivotCase), std::end(firstPivotCase),
                        QuickSort::firstPivot<typename std::vector<int>::iterator>(),
                        &comparisons_first);
    
        QuickSort::sort(std::begin(lastPivotCase), std::end(lastPivotCase),
                        QuickSort::lastPivot<typename std::vector<int>::iterator>(),
                        &comparisons_last);
    
        QuickSort::sort(std::begin(medianPivotCase), std::end(medianPivotCase),
                        QuickSort::medianOfThreePivot<std::vector<int>::iterator,
                        std::less<int> >(),
                        &comparisons_median);
        
        if (comparisons_median > comparisons_first ||
            comparisons_median > comparisons_last) {
            std::cout << "WRONG: number of comparisons\n";
            break;
        }
        else if (!std::is_sorted(std::begin(firstPivotCase),
                                 std::end(firstPivotCase))) {
            std::cout << "WRONG: first pivot case not sorted\n";
            break;
        }
        else if (!std::is_sorted(std::begin(lastPivotCase),
                                 std::end(lastPivotCase))) {
            std::cout << "WRONG: last pivot case not sorted\n";
            break;
        }
        else if (!std::is_sorted(std::begin(medianPivotCase),
                                 std::end(medianPivotCase))) {
            std::cout << "WRONG: median pivot case not sorted\n";
            break;
        } else {
            std::cout << "OK\n";
        }
    }
}
