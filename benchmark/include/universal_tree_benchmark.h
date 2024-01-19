#pragma once
#include <concepts>
#include <iostream>
#include <type_traits>
namespace benchmark {

//Базовая специализация шаблонной функции получения корневой ноды в дереве.
//Пользователи класса обязаны сделать специализацию со своими типами.
template <typename Tree>
auto GetRootNodePtr(const Tree& tree);

// Единый концепт для различных типов представляющих узел в дереве
template <typename T>
concept NodeType = requires {
  T::left;
  T::right;
  T::data;
}
|| requires(T t) {  // TODO: сделать в бенчмарке поддержку этих функций
  t.GetLeft();
  t.GetRight();
  t.GetData();
};

// Универсальный класс, содержащий логику анализа и отображения дерева.
// Шаблонизируется типом узла и инициализируется корневым узлом.
template <NodeType Node>
class UniversalTreeBenchmark {
 public:
  using DataType = decltype(Node::data);
  template <typename Tree>
  UniversalTreeBenchmark(const Tree& tree) : root_(GetRootNodePtr(tree)) {}

  // Вывод дерева в консоль горизонтально.
  void PrintHorizontally() {
    PrintRecursive("", root_, false);
    std::cout << std::endl;
  }

  // Вычисление размера дерева
  std::size_t CalculateSize() {
    return CalculateSizeRecursive(root_);
  }

  // Вычисление высоты дерева
  // Cormen et al. Introduction to Algorithms (Appendix B.5.3): 
  // The height of a node Y is the number of edges on the longest downward simple path from Y to a leaf.
  // The height of a tree is defined as the height of its root node.
  std::size_t CalculateHeight() {
    return CalculateHeightRecursive(root_);
  }

  // Вычисление средней глубины(высоты) дерева:
  // Cумма длин путей от корня до каждой вершины / количество вершин
  double CalculateAverageDepth() {
    return CalculateSummaryDepth(root_, 0) / static_cast<double>(CalculateSize());
  }
  
  // Вычисление контрольной суммы
  DataType CheckSum() {
    DataType sum{};
    UniformTraversing(root_, [& sum] (const DataType& value) {sum += value;});
    return sum;
  }

  bool IsBinarySearchTree() {
    return IsBinarySearchTreeRecursive(root_);
  }


 private:
  const Node* root_;

  void PrintRecursive(const std::string& prefix, const Node* node,
                      bool isLeft) {
    if (node != nullptr) {
      std::cout << prefix;

      if (node != root_) {
        std::cout << (isLeft ? "├l─" : "└r─");
      } else {
        std::cout << "└──";
      }

      // Вывод значения
      std::cout << node->data << std::endl;

      // Вывод ветвей
      PrintRecursive(prefix + (isLeft ? "│   " : "    "), node->left, true);
      PrintRecursive(prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
  }

  std::size_t CalculateSizeRecursive(const Node* node) {
    return (node) ? 1 + CalculateSizeRecursive(node->left) + CalculateSizeRecursive(node->right)
                  : 0;
  }

  std::size_t CalculateHeightRecursive(const Node* node) {
    // null
    if (!node) return 0;
    // leaf
    if (!node->left && !node->right) return 0;

    return 1 + std::max(CalculateHeightRecursive(node->left), CalculateHeightRecursive(node->right));
  }

  std::size_t CalculateSummaryDepth(const Node* node, unsigned int level) {
     if (!node) return 0;
     return level + CalculateSummaryDepth(node->left, level + 1) + CalculateSummaryDepth(node->right, level + 1);
  }
  // Вызвать функтор, передав данные в каждой ноде 
  void UniformTraversing(Node* node, std::function<void(const DataType&)> func) {
    if (!node) return;
    UniformTraversing(node->left, func);
    func(node->data);
    UniformTraversing(node->right, func);
  }

  bool IsBinarySearchTreeRecursive(Node* node) {
    if (!node) return false;
    if (!node->left && !node->right) return true;
    if (node->left && !node->right) 
      return (node->left->data < node->data && IsBinarySearchTreeRecursive(node->left));
    if (!node->left && node->right) 
      return (node->right->data > node->data && IsBinarySearchTreeRecursive(node->right));
    
    return    node->right->data > node->data && IsBinarySearchTreeRecursive(node->right)
          &&  node->left->data  < node->data && IsBinarySearchTreeRecursive(node->left);
  }
};

//CTAD позволяющий определять тип ноды
template <typename Tree>
UniversalTreeBenchmark(const Tree& t) -> UniversalTreeBenchmark<
    std::remove_pointer_t<decltype(GetRootNodePtr(t))>>;

}  // namespace benchmark