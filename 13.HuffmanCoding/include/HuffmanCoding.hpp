#ifndef HUFFMAN_CODING_HPP
#define HUFFMAN_CODING_HPP

#include <memory>
#include <vector>
#include <queue>
#include <algorithm>
#include <queue>

namespace HuffmanCoding {

    struct Node {
        int weight;
        std::shared_ptr<Node> left_child = nullptr;
        std::shared_ptr<Node> right_child = nullptr;
        Node() = default;
            
        Node(int weight) :  weight(weight) {}
        bool operator>(const Node& other) const {
            return weight > other.weight;
        }
    };
    
    unsigned maxDepthOfBinaryTree(const Node& root) {
        if (!root.left_child && !root.right_child) return 0;
        auto left_subtree_depth =
            root.left_child ? maxDepthOfBinaryTree(*(root.left_child)) : 0;
        auto right_subtree_depth =
            root.right_child ? maxDepthOfBinaryTree(*(root.right_child)) : 0;
        return 1 + std::max(left_subtree_depth, right_subtree_depth);
    }

    unsigned minDepthOfBinaryTree(const Node& root) {
        if (!root.left_child && !root.right_child) return 0;
        auto left_subtree_depth =
            root.left_child ? minDepthOfBinaryTree(*(root.left_child)) : 0;
        auto right_subtree_depth =
            root.right_child ? minDepthOfBinaryTree(*(root.right_child)) : 0;
        return 1 + std::min(left_subtree_depth, right_subtree_depth);
    }
    
    Node mergeNodes(const Node& node_1, const Node& node_2) {
        Node root;
        root.left_child = std::make_shared<Node >(node_1);
        root.right_child = std::make_shared<Node >(node_2);
        root.weight = node_1.weight + node_2.weight;
        return root;
    }

    Node computeHuffmanTree(const std::vector<Node>& nodes) {
         auto merge_queue = std::priority_queue<Node, std::vector<Node >,
                                               std::greater<Node >  >
            (std::begin(nodes), std::end(nodes));
        while (!merge_queue.empty()) {
            auto min_node_1 = merge_queue.top();
            merge_queue.pop();
            auto min_node_2 = merge_queue.top();
            merge_queue.pop();
            auto merge_node = mergeNodes(min_node_1, min_node_2);
            if (merge_queue.empty()) {
                return merge_node;
            }
            merge_queue.push(merge_node);
        }
        return Node();
    }
}

#endif
