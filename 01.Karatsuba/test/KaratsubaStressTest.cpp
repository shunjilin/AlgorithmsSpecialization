#include <string>
#include <limits>
#include <iostream>
#include "Karatsuba.hpp"
#include "UniformRandom.hpp"

std::string Multiply(std::string number_one, std::string number_two) {
    auto x = std::stoull(number_one);
    auto y = std::stoull(number_two);
    auto result = x * y;
    return std::to_string(result);
}

int main(int argc, char *argv[])
{
    UniformRandom<unsigned> rng(0, std::numeric_limits<unsigned>::max());

    for (int i = 0; i < 10000; ++i) {
        auto x = rng.generate();
        auto y = rng.generate();
        auto x_string = std::to_string(x);
        auto y_string = std::to_string(y);

        auto karatsuba = Karatsuba::multiply(x_string, y_string);
        auto expected = Multiply(x_string, y_string);
        if (karatsuba == expected) {
            std::cout << "OK\n";
        } else {
            std::cout << "WRONG\n";
            break;
        }
        std::cout << x_string << " * " << y_string << "\n";
        std::cout << "Karatsuba: " << karatsuba
                  << " Expected: " << expected << "\n";
    } 
    return 0;
}
