#include <iostream>
#include <fstream>
#include <algorithm>
#include "QuickSort.hpp"
#include "SteadyClockTimer.hpp"

int main(int argc, char *argv[])
{
    std::vector<int> firstPivotCase;
    if (argc > 1) {
        std::ifstream ifile(argv[1]);
        if (!ifile) {
            std::cerr << "Unable to open file: " << argv[1] << std::endl;
            exit(1);
        }
        int number;
        while (ifile >> number) firstPivotCase.push_back(number);
    } else {
        std::cerr << "No input given!" << std::endl;
        exit(1);
    }

    std::vector<int> lastPivotCase(std::begin(firstPivotCase),
                                   std::end(firstPivotCase));
    std::vector<int> medianPivotCase(std::begin(firstPivotCase),
                                     std::end(firstPivotCase));
    
    unsigned long long comparisons_first = 0,  comparisons_last = 0,
        comparisons_median = 0;
        
    SteadyClockTimer timer;
    timer.start();
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
    auto time_taken = timer.getMs();

    std::cout << "Number of comparisons is [first pivot] : " << comparisons_first
              << "\nNumber of comparisons is [last pivot] : " << comparisons_last
              << "\nNumber of comparisons is [median of three pivot] : " << comparisons_median
              << "\nTime taken for 3 sorts is: " << timer.getMs() << " ms\n";
    
}
