#pragma once

/*
    Binary B search tree 
    Двоичное Б-дерево поиска (ДБД)

*/

namespace implementations {

namespace binary_b_tree_support {

template <typename T>
class Node {
    public:
    T value;
    bool have_right_neighbour; // in right pointer stored neighbour on same size
    Node* left; // always points on childs
    Node* right; // may points on child or on right neighbour
    
};

}  // namespace binary_b_tree_support

template <typename T>
class BinaryBTree {
 public:
  using Node = binary_b_tree_support::Node<T>;

    void Insert(T value) {
        root_ = InsertRecursive(root_, value);
    }

 private:
    Node* root_;

    template <typename U>
    Node* InsertRecursive(Node* node, U&& value) {
        if (!node) {
            return new Node(std::forward<U>(value));выds
        }

        if (value < node->value) {
            node->left = InsertRecursive(node->left, std::forward<U>(value));
            // третий случай 
        }



    }
};

}  // namespace implementations