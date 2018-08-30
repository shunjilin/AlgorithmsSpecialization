#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "TravelingSalesmanProblem.hpp"
#include "SteadyClockTimer.hpp"

int main(int argc, char *argv[]) {
    std::vector<Vertex> vertice;
    int n_vertice = 0;

    if (argc > 1) {
        std::ifstream ifile(argv[1]);
        if (!ifile) {
            std::cerr << "Unable to open file: " << argv[1] << std::endl;
            return EXIT_FAILURE;
        }
        std::string line;
        std::getline(ifile, line);
        std::istringstream iss(line);
        iss >> n_vertice;
        while (std::getline(ifile, line)) {
            std::istringstream iss(line);
            double x, y;
            iss >> x >> y;
            vertice.emplace_back(Vertex{x, y});
        }
    } else {
        std::cerr << "No input file given!" << std::endl;
        return EXIT_FAILURE;
    }
    
    SteadyClockTimer timer;
    timer.start();
    auto TSPvalue = getTSPvalue(vertice);
    auto time_taken = timer.getMs();
    std::cout << "TSP value is : " << TSPvalue << "\n";
    std::cout << "Time taken is : " << time_taken << "ms\n";
    return 0;
}
