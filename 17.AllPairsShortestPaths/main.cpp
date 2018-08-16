#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Johnson.hpp"
#include "SteadyClockTimer.hpp"

int main(int argc, char *argv[]) {
    std::vector<Edge> edges;
    unsigned n_nodes = 0;

    if (argc > 1) {
        std::ifstream ifile(argv[1]);
        if (!ifile) {
            std::cerr << "Unable to open file: " << argv[1] << std::endl;
            return EXIT_FAILURE;
        }
        std::string line;
        std::getline(ifile, line);
        std::istringstream iss(line);
        iss >> n_nodes;
        while (std::getline(ifile, line)) {
            std::istringstream iss(line);
            int source, target, length;
            iss >> source >> target >> length;
            edges.emplace_back(Edge{source - 1, target - 1, length});
        }
    } else {
        std::cerr << "No input file given!" << std::endl;
        return EXIT_FAILURE;
    }

    auto graph = Graph(n_nodes, edges);
    
    SteadyClockTimer timer;
    timer.start();
    auto shortest_shortest_path = shortestShortestPath(graph);
    auto time_taken = timer.getMs();
    if (shortest_shortest_path.has_value()) {
        std::cout << "Shortest shortest path length is : "
                  << shortest_shortest_path.value() << "\n";
    } else {
        std::cout << "Graph has negative cycle!\n";
    }
    std::cout << "Time taken is : " << time_taken << "ms\n";
    return 0;
}
