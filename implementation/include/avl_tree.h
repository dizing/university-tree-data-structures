#pragma once

#include "common.h"

namespace implementations {

template <typename T>
class AVLTree {
 public:
  struct AVLNode : public Node<T> {
    int height;
    AVLNode(typename Node<T>::ValueType value) : Node<T>(value), height(1) {}
    static int GetHeight(const AVLNode* node) {
      return (node) ? node->height : 0;
    }
    AVLNode* GetLeft() { return static_cast<AVLNode*>(this->left); }
    AVLNode* GetRight() { return static_cast<AVLNode*>(this->right); }
    const AVLNode* GetLeft() const volatile {
      return static_cast<const AVLNode*>(this->left);
    }
    const AVLNode* GetRight() const {
      return static_cast<const AVLNode*>(this->right);
    }
    void FixHeight() {
      height = std::max(GetHeight(GetLeft()), GetHeight(GetRight())) + 1;
    }
    int BalanceFactor() { return GetHeight(GetRight()) - GetHeight(GetLeft()); }
    ~AVLNode() override = default;
  };

  using NodeType = AVLNode;
  using ValueType = typename NodeType::ValueType;

  AVLTree() : root_(nullptr) {}
  ~AVLTree() { delete root_; }

  void Insert(ValueType& value) { root_ = InsertRecursive(root_, value); }

  void Insert(ValueType&& value) {
    root_ = InsertRecursive(root_, std::move(value));
  }

  const NodeType* GetRoot() const { return root_; }

 private:
  NodeType* root_;

  // Повороты
  static NodeType* RotateRight(NodeType* node) {
    NodeType* new_root = node->GetLeft();
    node->left = new_root->GetRight();
    new_root->right = node;
    node->FixHeight();
    new_root->FixHeight();
    return new_root;
  }
  static NodeType* RotateLeft(NodeType* node) {
    NodeType* new_root = node->GetRight();
    node->right = new_root->GetLeft();
    new_root->left = node;
    node->FixHeight();
    new_root->FixHeight();
    return new_root;
  }

  // Балансировка
  static NodeType* Balance(NodeType* node) {
    node->FixHeight();
    if (node->BalanceFactor() == 2) {
      if (node->GetRight()->BalanceFactor() == -1) {
        node->right = RotateRight(node->GetRight());
      }
      return RotateLeft(node);
    }
    if (node->BalanceFactor() == -2) {
      if (node->GetLeft()->BalanceFactor() == 1) {
        node->left = RotateLeft(node->GetLeft());
      }
      return RotateRight(node);
    }
    return node;
  }

  template <typename U>
  static NodeType* InsertRecursive(NodeType* root, U&& value) {
    if (!root) return new NodeType(std::forward<U>(value));
    if (value < root->data)
      root->left = InsertRecursive(root->GetLeft(), std::forward<U>(value));
    if (value > root->data)
      root->right = InsertRecursive(root->GetRight(), std::forward<U>(value));
    return Balance(root);
  }
};

}  // namespace implementations