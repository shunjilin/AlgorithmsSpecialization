#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "SCC.hpp"
#include "2SAT.hpp"
#include "SteadyClockTimer.hpp"


int main(int argc, char *argv[]) {
    std::vector<TWOSAT::Clause> clauses;
    int n_variables;

    if (argc > 1) {
        std::ifstream ifile(argv[1]);
        if (!ifile) {
            std::cerr << "Unable to open file: " << argv[1] << std::endl;
            return EXIT_FAILURE;
        }
        std::string line;
        std::getline(ifile, line);
        std::istringstream iss(line);
        iss >> n_variables;
        while (std::getline(ifile, line)) {
            std::istringstream iss(line);
            TWOSAT::Clause clause;
            iss >> clause.literal1 >> clause.literal2;
            clauses.emplace_back(clause);
        }
    } else {
        std::cerr << "No input file given!" << std::endl;
        return EXIT_FAILURE;
    }

    SteadyClockTimer timer;
    timer.start();
    auto is_satisfiable = TWOSAT::isSatisfiable(n_variables, clauses);
    auto time_taken = timer.getMs();
    std::cout << "The given 2 SAT instance ";
    if (is_satisfiable) {
        std::cout << "is satisfiable.\n";
    } else {
        std::cout << "is not satisfiable.\n";
    }
    std::cout << "Time taken is : " << time_taken << "ms\n";
}
