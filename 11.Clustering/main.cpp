#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "SteadyClockTimer.hpp"
#include "Clustering.hpp"

using namespace Clustering;
constexpr unsigned k_clusters = 4;

int main(int argc, char *argv[])
{
    std::vector<Edge> edges;
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
            unsigned node1, node2, cost;
            iss >> node1 >> node2 >> cost;
            edges.emplace_back(Edge{node1-1, node2-1, cost});
        }
    } else {
        std::cerr << "No input given!" << std::endl;
        exit(1);
    }
    SteadyClockTimer timer;
    timer.start();
    auto max_spacing_k_clusterings =
        maxSpacingKClustering(n_nodes, edges, k_clusters);
    auto time_taken = timer.getMs();
    std::cout << "Max spacing for " << k_clusters << " clusterings is : "
              << max_spacing_k_clusterings
              << "\nTime taken is : " << time_taken << "ms\n";
    return 0;
}
