#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <functional>
#include "SCC.hpp"
#include "SteadyClockTimer.hpp"

int main(int argc, char *argv[])
{
    std::vector<SCC::Edge> edges;
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
            unsigned source, target;
            iss >> source >> target;
            edges.emplace_back(SCC::Edge{source-1, target-1});
            if (source > n_nodes) n_nodes = source;
            if (target > n_nodes) n_nodes = target;
        }
    } else {
        std::cerr << "No input given!" << std::endl;
        exit(1);
    }
    SteadyClockTimer timer;
    timer.start();
    auto leader_to_scc_size = SCC::computeSCC(n_nodes, edges);
    std::priority_queue<unsigned, std::vector<unsigned>,
                        std::greater<unsigned> > largest_five_SCC_sizes;
    for (auto leader_size : leader_to_scc_size) {
        largest_five_SCC_sizes.push(leader_size.second);
        if (largest_five_SCC_sizes.size() > 5) {
            largest_five_SCC_sizes.pop();
        }
    }
    auto time_taken = timer.getMs();
    std::cout << "Largest 5 SCC sizes are:";
    while (!largest_five_SCC_sizes.empty()) {
        std::cout << " " << largest_five_SCC_sizes.top();
        largest_five_SCC_sizes.pop();
    }
    std::cout << "\n"
              << "Time taken is : " << time_taken << "ms\n";
}
