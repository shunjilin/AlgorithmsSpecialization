#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>
#include <cmath>
#include <limits>
#include "KargersMinCut.hpp"
#include "SteadyClockTimer.hpp"

int main(int argc, char *argv[])
{
    Kargers::Edgelist edge_list;
    unsigned n_nodes = 0;
    if (argc > 1) {
        std::ifstream ifile(argv[1]);
        if (!ifile) {
            std::cerr << "Unable to open file: " << argv[1] << std::endl;
            exit(1);
        }
        std::string line;
        while (std::getline(ifile, line)) {
            std::istringstream iss(line);
            int u, v;
            iss >> u;
            while (iss >> v) {
                if (u < v)
                    edge_list.emplace_back(u-1, v-1);
            }
            ++n_nodes;
        }
    } else {
        std::cerr << "No input given!" << std::endl;
        exit(1);
    }
    std::random_device rd;
    std::mt19937 gen = std::mt19937(rd());
    unsigned n_trials = pow(n_nodes, 2) * log(n_nodes);
    unsigned min_edges = std::numeric_limits<unsigned>::max();
    for (unsigned i = 0; i < n_trials; ++i) {
        auto edges = Kargers::
            getEdgeCountFromRandomContract(n_nodes, edge_list, gen);
        if (edges < min_edges) {
            min_edges = edges;
            std::cout << "Smallest # edges in cut so far: " << min_edges
                      << "\n";
        }
    }
}
