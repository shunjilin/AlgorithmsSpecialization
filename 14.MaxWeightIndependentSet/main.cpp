#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include "SteadyClockTimer.hpp"
#include "MaxWeightIndependentSet.hpp"

bool nodeIndexInSet(unsigned index, const std::set<unsigned>& nodes) {
    return nodes.find(index-1) != nodes.end();
}

using namespace DynamicProgramming;

int main(int argc, char *argv[])
{
    std::vector<unsigned> path;
    unsigned n_nodes;
    if (argc > 1) {
        std::ifstream ifile(argv[1]);
        if (!ifile) {
            std::cerr << "Unable to open file: " << argv[1] << std::endl;
            exit(1);
        }
        std::string line;
        std::getline(ifile, line);
        std::istringstream iss(line);
        iss >> n_nodes;
        while (std::getline(ifile, line)) {
            std::istringstream iss(line);
            int weight;
            iss >> weight;
            path.push_back(weight);
        }
    } else {
        exit(1);
    }
    SteadyClockTimer timer;
    timer.start();
    auto MWIS_nodes = getIndexOfMWISNodes(path);
    auto time_taken = timer.getMs();
    std::cout << nodeIndexInSet(1, MWIS_nodes)
              << nodeIndexInSet(2, MWIS_nodes)
              << nodeIndexInSet(3, MWIS_nodes)
              << nodeIndexInSet(4, MWIS_nodes)
              << nodeIndexInSet(17, MWIS_nodes)
              << nodeIndexInSet(117, MWIS_nodes)
              << nodeIndexInSet(517, MWIS_nodes)
              << nodeIndexInSet(997, MWIS_nodes)
              << "\nTime taken is : " << time_taken << "ms\n";
    return 0;
}
