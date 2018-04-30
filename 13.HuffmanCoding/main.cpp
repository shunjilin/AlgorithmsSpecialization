#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "SteadyClockTimer.hpp"
#include "HuffmanCoding.hpp"

using namespace HuffmanCoding;

int main(int argc, char *argv[])
{
    std::vector<Node> nodes;
    unsigned n_nodes;
    if (argc > 1) {
        std::ifstream ifile(argv[1]);
        if (!ifile) {
            std::cerr << "Unable to open file: " << argv[1] << std::endl;
            exit(1);
        }
        std::string line;
        std::getline(ifile, line);
        std::istringstream iss(line);
        iss >> n_nodes;
        while (std::getline(ifile, line)) {
            std::istringstream iss(line);
            int weight;
            iss >> weight;
            nodes.emplace_back(Node{weight});
        }
    } else {
        exit(1);
    }
    SteadyClockTimer timer;
    timer.start();
    auto huffman_tree = computeHuffmanTree(nodes);
    auto max_length = maxDepthOfBinaryTree(huffman_tree);
    auto min_length = minDepthOfBinaryTree(huffman_tree);
    auto time_taken = timer.getMs();
    std::cout << "Max length of codeword is :  "
              << max_length
              << "\nMin length of codeword is :  "
              << min_length
              << "\nTime taken is : " << time_taken << "ms\n";
    return 0;
}
