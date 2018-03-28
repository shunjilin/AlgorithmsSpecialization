#include <iostream>
#include <vector>
#include "UniformRandom.hpp"
#include "MedianMaintenance.hpp"

template<typename T>
struct NaiveMedianMaintenance {
    std::vector<T> elements;
    void push(T element) {
        elements.push_back(element);
        std::sort(std::begin(elements), std::end(elements));
    }
    T getMedian() const {
        auto n_elements = elements.size();
        if (n_elements % 2 == 0) {
            return elements[n_elements / 2 - 1];
        } else {
            return elements[n_elements / 2];
        }
    }
};


int main(int argc, char *argv[])
{
    UniformRandom<unsigned> sequence_size_rng(0, 10000);
    UniformRandom<unsigned> number_rng(0, 10000);
    DataStructures::MedianMaintenance<unsigned> MM;
    NaiveMedianMaintenance<unsigned> NMM;

    auto sequence_size = sequence_size_rng.generate();
    for (unsigned i = 0; i < sequence_size; ++i) {
        auto number = number_rng.generate();
        MM.push(number);
        NMM.push(number);
        auto expected_median = NMM.getMedian();
        auto actual_median = MM.getMedian();
        if (expected_median == actual_median) {
            std::cout << "OK\n";
        } else {
            std::cout << "WRONG\n";
            return 0;
        }
    }
}
