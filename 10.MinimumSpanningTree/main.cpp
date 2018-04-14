#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "SteadyClockTimer.hpp"
#include "MinimumSpanningTree.hpp"

using namespace PrimsAlgorithm;

int main(int argc, char *argv[])
{
    Graph graph;
    if (argc > 1) {
        std::ifstream ifile(argv[1]);
        if (!ifile) {
            std::cerr << "Unable to open file: " << argv[1] << std::endl;
            exit(1);
        }
        std::string line;
        std::getline(ifile, line);
        std::istringstream iss(line);
        unsigned n_nodes, n_edges;
        iss >> n_nodes >> n_edges;
        graph = Graph(n_nodes);
        while (std::getline(ifile, line)) {
            std::istringstream iss(line);
            unsigned source_node, target_node;
            int edge_cost;
            iss >> source_node >> target_node >> edge_cost;
            graph.insertEdge(Edge{source_node-1, target_node-1, edge_cost});
        }
    } else {
        std::cerr << "No input given!" << std::endl;
        exit(1);
    }
    SteadyClockTimer timer;
    timer.start();
    auto minimum_spanning_tree_cost = computeMinimumSpanningTreeCost(graph);
    auto time_taken = timer.getMs();
    std::cout << "Minimum spanning tree cost is : "
              << minimum_spanning_tree_cost
              << "\nTime taken is : " << time_taken << "ms\n";
}
