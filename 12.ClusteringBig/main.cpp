#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "SteadyClockTimer.hpp"
#include "ClusteringBig.hpp"

using namespace ClusteringBig;

int main(int argc, char *argv[])
{
    std::vector<int> nodes;
    unsigned n_nodes, n_bits;
    if (argc > 1) {
        std::ifstream ifile(argv[1]);
        if (!ifile) {
            std::cerr << "Unable to open file: " << argv[1] << std::endl;
            exit(1);
        }
        std::string line;
        std::getline(ifile, line);
        std::istringstream iss(line);
        iss >> n_nodes >> n_bits;
        while (std::getline(ifile, line)) {
            std::istringstream iss(line);
            int node = 0;
            for (unsigned i = 0; i < n_bits; ++i) {
                int bit;
                iss >> bit;
                node <<= 1;
                node += bit;
            }
            nodes.emplace_back(node);
        }
    } else {
        exit(1);
    }
    SteadyClockTimer timer;
    timer.start();
    auto k_clusters = kValueForSpacingOfAtLeast3(nodes, n_bits);
    auto time_taken = timer.getMs();
    std::cout << "Number of clusters for spacing of at least 3 is:  "
              << k_clusters
              << "\nTime taken is : " << time_taken << "ms\n";
    return 0;
}
