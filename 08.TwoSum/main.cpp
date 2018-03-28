#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "SteadyClockTimer.hpp"
#include "TwoSum.hpp"

using namespace TwoSum;

constexpr long MIN_SUM = -10000;
constexpr long MAX_SUM = 10000;

int main(int argc, char *argv[])
{
    SteadyClockTimer timer;
    timer.start();
    std::vector<long> summands;
    if (argc > 1) {
        std::ifstream ifile(argv[1]);
        if (!ifile) {
            std::cerr << "Unable to open file: " << argv[1] << std::endl;
            exit(1);
        }
        std::string line;
        while (std::getline(ifile, line)) {
            std::istringstream iss(line);
            long summand;
            iss >> summand;
            summands.push_back(summand);
        }
    } else {
        std::cerr << "No input given!" << std::endl;
        exit(1);
    }
    std::cout << "here" << std::endl;
    auto time_taken = timer.getMs();
    std::cout << "Number of two sums is : "
              << getNumOfTwoSumsInRange(summands, MIN_SUM, MAX_SUM)
              << "\n";
    std::cout << "Time taken is : " << time_taken << "ms\n";
}
