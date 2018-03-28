#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "MedianMaintenance.hpp"
#include "SteadyClockTimer.hpp"

using namespace DataStructures;

int main(int argc, char *argv[])
{
    SteadyClockTimer timer;
    timer.start();
    MedianMaintenance<unsigned> median_maintenance;
    unsigned median_sum = 0;
    if (argc > 1) {
        std::ifstream ifile(argv[1]);
        if (!ifile) {
            std::cerr << "Unable to open file: " << argv[1] << std::endl;
            exit(1);
        }
        std::string line;
        while (std::getline(ifile, line)) {
            std::istringstream iss(line);
            unsigned number;
            iss >> number;
            median_maintenance.push(number);
            median_sum += median_maintenance.getMedian();
            median_sum %= 10000;
        }
    } else {
        std::cerr << "No input given!" << std::endl;
        exit(1);
    }
    auto time_taken = timer.getMs();
    std::cout << "Sum of medians is : " << median_sum << "\n";
    std::cout << "Time taken is : " << time_taken << "ms\n";
}
