#pragma once
#include <cassert>
#include <vector>

#include "common.h"

namespace implementations {

template <typename T>
class PerfectlyBalancedBinaryTree {
 public:
  using NodeType = Node<T>;
  using ValueType = typename NodeType::ValueType;

  PerfectlyBalancedBinaryTree() : root_(nullptr) {}
  PerfectlyBalancedBinaryTree(std::vector<ValueType> elements) {
    sort(elements.begin(), elements.end());
    elements.erase(unique(elements.begin(), elements.end()), elements.end());
    root_ = RecursiveTreeGenerate(0, elements.size() - 1, elements);
  }

  ~PerfectlyBalancedBinaryTree() { delete root_; }

  void Insert(ValueType value) {
    std::vector<ValueType> elements{value};
    UniformTraversing(root_,
                      [&elements](ValueType& val) { elements.push_back(val); });
    sort(elements.begin(), elements.end());
    elements.erase(unique(elements.begin(), elements.end()), elements.end());
    delete root_;
    root_ = RecursiveTreeGenerate(0, elements.size() - 1, elements);
  }

  const NodeType* GetRoot() const { return root_; }

 private:
  // left -- индекс первого элемента
  // left -- индекс последнего элемента
  NodeType* RecursiveTreeGenerate(std::size_t left, std::size_t right,
                                  std::vector<ValueType>& arr) {
    assert(left <= right);
    auto middle = left + (right - left) / 2;
    NodeType* node = new NodeType(arr[middle]);
    if (left != middle)
      node->left = RecursiveTreeGenerate(left, middle - 1, arr);
    if (right != middle)
      node->right = RecursiveTreeGenerate(middle + 1, right, arr);
    return node;
  }

 private:
  NodeType* root_;
};

}  // namespace implementations