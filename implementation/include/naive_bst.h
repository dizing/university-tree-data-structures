#pragma once

#include "common.h"

namespace implementations {

template <typename T>
class NaiveBinarySearchTree {
 public:
  using NodeType = Node<T>;
  using ValueType = typename NodeType::ValueType;

  NaiveBinarySearchTree() : root_(nullptr) {}
  ~NaiveBinarySearchTree() { delete root_; }

  void Insert(ValueType value) {
    if (!root_) {
      root_ = new NodeType(value);
      return;
    }
    NodeType* find_ptr = root_;
    while (true) {
      if (value > find_ptr->data) {
        if (find_ptr->right) {
          find_ptr = find_ptr->right;
        } else {
          find_ptr->right = new NodeType(value);
          return;
        }
      }
      if (value < find_ptr->data) {
        if (find_ptr->left) {
          find_ptr = find_ptr->left;
        } else {
          find_ptr->left = new NodeType(value);
          return;
        }
      }
      // Если одинаковы ничего не делать -- логика сета
      if (value == find_ptr->data) {
        return;
      }
    }
  }

  const NodeType* GetRoot() const { return root_; }

 private:
  NodeType* root_;
};

}  // namespace implementations