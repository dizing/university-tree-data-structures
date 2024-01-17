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
    return (node) ? CalculateSizeRecursive(node->left) + CalculateSizeRecursive(node->right)
                  : 1;
  }

  std::size_t CalculateHeightRecursive(const Node* node) {
    // null
    if (!node) return 0;
    // leaf
    if (!node->left && !node->right) return 0;

    return 1 + std::max(CalculateHeightRecursive(node->left), CalculateHeightRecursive(node->right));
  }
};

//CTAD позволяющий определять тип ноды
template <typename Tree>
UniversalTreeBenchmark(const Tree& t) -> UniversalTreeBenchmark<
    std::remove_pointer_t<decltype(GetRootNodePtr(t))>>;

}  // namespace benchmark