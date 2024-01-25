#pragma once

#include "common.h"

namespace implementations {

template <typename T>
class AVLTree {
 public:
  struct AVLNode : Node<T> {
    int height;
    using Node<T>::left;
    using Node<T>::right;
    using Node<T>::data;
    AVLNode(Node<T>::ValueType value) : Node<T>(value), height(1) {}
    void FixHeight() {
        height = std::max(GetHeight(static_cast<AVLNode*>(left)), GetHeight(static_cast<AVLNode*>(right))) + 1;
    }
    static int GetHeight(AVLNode* node) {
        return (node) ? node->height : 0;
    }
  };
  using NodeType = AVLNode;
  using ValueType = typename NodeType::ValueType;

  AVLTree() : root_(nullptr) {}
  ~AVLTree() { delete root_; }

  void Insert(ValueType value) {
    
  }

  const NodeType* GetRoot() const { return root_; }

 private:

  static int BalanceFactor(NodeType* node) {

  }
  
  // Повороты
  static NodeType* RotateRight(NodeType* node){

  }
  static NodeType* RotateLeft(NodeType* node){

  }
  static NodeType* Balance(NodeType* node) {

  }

 private:
  NodeType* root_;
};

}  // namespace implementations