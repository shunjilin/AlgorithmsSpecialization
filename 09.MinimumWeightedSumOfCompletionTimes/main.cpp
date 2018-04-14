#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <limits>
#include "SteadyClockTimer.hpp"
#include "WeightedSumOfCompletionTimes.hpp"

using namespace WeightedSumOfCompletionTimes;

int main(int argc, char *argv[])
{
    std::vector<Job> jobs;
    if (argc > 1) {
        std::ifstream ifile(argv[1]);
        if (!ifile) {
            std::cerr << "Unable to open file: " << argv[1] << std::endl;
            exit(1);
        }
        std::string line;
        ifile.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore n_jobs
        while (std::getline(ifile, line)) {
            std::istringstream iss(line);
            unsigned weight, length;
            iss >> weight >> length;
            jobs.emplace_back(Job{weight, length});
        }
    } else {
        std::cerr << "No input given!" << std::endl;
        exit(1);
    }
    SteadyClockTimer timer;
    timer.start();
    auto weighted_sum_by_difference =  computeWeightedSumOfCompletionTimes
        (std::begin(jobs), std::end(jobs), DifferenceComparator());
    auto weighted_sum_by_ratio = computeWeightedSumOfCompletionTimes
        (std::begin(jobs), std::end(jobs), RatioComparator());
    auto time_taken = timer.getMs();
    std::cout << "Weighted sum of completion times by difference score is: "
              << weighted_sum_by_difference
              << "\nWeighted sum of completion times by ratio score (optimal) is: "
              << weighted_sum_by_ratio
              << "\nTime taken is : " << time_taken << "ms\n";
}
