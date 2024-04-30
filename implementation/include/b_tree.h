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
  T data;
  int BAL;
  Node* left;   // always points on childs
  Node* right;  // may points on child or on right neighbour

  Node(T data) : data(data), BAL(0), left(nullptr), right(nullptr) {}
};

}  // namespace binary_b_tree_support

template <typename T>
class BinaryBTree {
 public:
  using Node = binary_b_tree_support::Node<T>;

  void Insert(T value) { root_ = InsertRecursive(root_, value); }

  const Node* GetRoot() const { return root_; }

  int GetLevels() {
    auto ptr = root_;
    int count = 0;
    while (ptr) {
      ++count;
      ptr = ptr->left;
    }
    return count;
  }

    static void UniformTraversing(const Node* node,
                        std::function<void(T)> func) {
        if (!node) return;
        UniformTraversing(node->left, func);
        func(node->data);
        UniformTraversing(node->right, func);
    }

 private:
  Node* root_ = nullptr;
  bool VR = true;
  bool HR = true;

  template <typename U>
  Node* InsertRecursive(Node* node, U&& value) {
    if (!node) {
      VR = true;
      return new Node(std::forward<U>(value));
    }

    if (value < node->data) {
      node->left = InsertRecursive(node->left, std::forward<U>(value));
      if (VR) {
        if (node->BAL > 0) {
          //(3)
          auto q = node->left;
          node->left = q->right;
          q->right = node;
          node = q;
          q->BAL = 1;
          VR = false;
          HR = true;
        } else {
          //(4)
          node->BAL = 0;
          HR = true;
        }
      } else {
        HR = false;
      }

    } else if (value > node->data) {
      node->right = InsertRecursive(node->right, std::forward<U>(value));
      if (VR) {
        //(1)
        node->BAL = 1;
        VR = false;
        HR = true;
      } else if (HR) {
        if (node->BAL > 0) {
          //(2)
          auto q = node->right;
          node->right = q->left;
          node->BAL = 0;
          q->BAL = 0;
          q->left = node;
          node = q;
          VR = true;
          HR = false;
        } else {
          HR = false;
        }
      }
    }

    return node;
  }
};

}  // namespace implementations