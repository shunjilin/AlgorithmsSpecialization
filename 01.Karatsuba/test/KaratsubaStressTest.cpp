#include <string>
#include "Karatsuba.hpp"
#include <random>
#include <array>
#include <limits>
#include <functional>
#include <iostream>

std::string Multiply(std::string number_one, std::string number_two) {
    auto x = std::stoull(number_one);
    auto y = std::stoull(number_two);
    auto result = x * y;
    return std::to_string(result);
}

int main(int argc, char *argv[])
{
    std::random_device rd;
    std::array<int, std::mt19937::state_size> seed_data {};
    std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
    std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
    auto eng = std::mt19937{seq};
    auto dist = std::uniform_int_distribution<unsigned>
        {0, std::numeric_limits<unsigned>::max()};

    for (int i = 0; i < 10000; ++i) {
        auto x = dist(eng);
        auto y = dist(eng);
        auto x_string = std::to_string(x);
        auto y_string = std::to_string(y);

        auto karatsuba = Karatsuba::multiply(x_string, y_string);
        auto actual = Multiply(x_string, y_string);
        if (karatsuba == actual) {
            std::cout << "OK\n";
        } else {
            std::cout << "WRONG\n";
            break;
        }
        std::cout << x_string << " * " << y_string << "\n";
        std::cout << "Karatsuba: " << karatsuba
                  << " Actual: " << actual << "\n";
    } 
    return 0;
}
