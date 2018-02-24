#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <tuple>
#include "include/Karatsuba.hpp"

int main(int argc, char *argv[])
{
    std::string number_one, number_two;
    if (argc > 1) {
        std::ifstream ifile(argv[1]);
        if (!ifile) {
            std::cerr << "Unable to open file: " << argv[1] << std::endl;
            exit(1);
        }
        ifile >> number_one >> number_two;
        if (number_one.size() == 0 || number_two.size() == 0) {
            std::cerr << "Invalid input!" << std::endl;
            exit(1);
        }
    } else {
        std::cerr << "No input given!" << std::endl;
        exit(1);
    }
    std::cout << number_one << " * " << number_two<< " =\n"
              << Karatsuba::multiply(number_one, number_two) << std::endl;
    
}
