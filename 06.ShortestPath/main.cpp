#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "ShortestPath.hpp"
#include "SteadyClockTimer.hpp"

using namespace ShortestPath;

int main(int argc, char *argv[])
{
    
    std::vector<Edge> edges;
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
            unsigned source, target, length;
            iss >> source;
            while (iss >> target) {
                iss.ignore(1, ',');
                iss >> length;
                edges.emplace_back(Edge{source - 1, target - 1, length});
                if (source > n_nodes) n_nodes = source;
                if (target > n_nodes) n_nodes = target;
            }
        }
    } else {
        std::cerr << "No input given!" << std::endl;
        exit(1);
    }
    SteadyClockTimer timer;
    timer.start();
    auto shortest_paths = computeShortestPaths(n_nodes, edges, 0);
    auto time_taken = timer.getMs();
    std::cout << "Shortest path distances are: "
              << shortest_paths[7-1] << ","
              << shortest_paths[37-1] << ","
              << shortest_paths[59-1] << ","
              << shortest_paths[82-1] << ","
              << shortest_paths[99-1] << ","
              << shortest_paths[115-1] << ","
              << shortest_paths[133-1] << ","
              << shortest_paths[165-1] << ","
              << shortest_paths[188-1] << ","
              << shortest_paths[197-1]
              << "\n";
    std::cout << "Time taken is : " << time_taken << "ms\n";
}
