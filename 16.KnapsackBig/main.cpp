#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "SteadyClockTimer.hpp"
#include "KnapsackBig.hpp"

using namespace Memoization;

int main(int argc, char *argv[])
{
    std::vector<KnapsackObject> objects;
    unsigned max_weight, n_nodes;
    if (argc > 1) {
        std::ifstream ifile(argv[1]);
        if (!ifile) {
            std::cerr << "Unable to open file: " << argv[1] << std::endl;
            exit(1);
        }
        std::string line;
        std::getline(ifile, line);
        std::istringstream iss(line);
        iss >> max_weight >> n_nodes;
        while (std::getline(ifile, line)) {
            std::istringstream iss(line);
            unsigned value, weight;
            iss >> value >> weight;
            objects.push_back(KnapsackObject{value, weight});
        }
    } else {
        exit(1);
    }
    SteadyClockTimer timer;
    timer.start();
    auto optimal_value = computeOptimalKnapsackValue(objects, max_weight);
    auto time_taken = timer.getMs();
    std::cout << "Optimal knapsack value is : " << optimal_value
             << "\nTime taken is : " << time_taken << "ms\n";
    return 0;
}
