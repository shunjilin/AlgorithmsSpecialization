#include <iostream>
#include <fstream>
#include <vector>
#include "MergeSort.hpp"
#include "SteadyClockTimer.hpp"

int main(int argc, char *argv[])
{
    std::vector<int> numbers;
    if (argc > 1) {
        std::ifstream ifile(argv[1]);
        if (!ifile) {
            std::cerr << "Unable to open file: " << argv[1] << std::endl;
            exit(1);
        }
        int number;
        while (ifile >> number) numbers.push_back(number);
    } else {
        std::cerr << "No input given!" << std::endl;
        exit(1);
    }
    SteadyClockTimer timer;
    timer.start();
    auto inversion_count
        = MergeSort::sortAndGetInversionCount(std::begin(numbers),
                                              std::end(numbers));
    auto time_taken = timer.getMs();
    std::cout << "Number of inversions: " << inversion_count << "\n"
              << "Time taken: " << time_taken << "ms\n";
}
