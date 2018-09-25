#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "ApproximateTravelingSalesmanProblem.hpp"
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
            size_t index;
            double x, y;
            iss >> index >> x >> y;
            vertice.emplace_back(Vertex{x, y});
        }
    } else {
        std::cerr << "No input file given!" << std::endl;
        return EXIT_FAILURE;
    }
    
    SteadyClockTimer timer;
    timer.start();
    auto ApproximateTSPvalue = getApproximateTSPValue(vertice);
    auto time_taken = timer.getMs();
    std::cout << "Approximate TSP value is : "
        << static_cast<long>(ApproximateTSPvalue) << "\n";
    std::cout << "Time taken is : " << time_taken << "ms\n";
    return 0;
}
