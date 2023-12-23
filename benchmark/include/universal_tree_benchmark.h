#pragma once
#include <concepts>
#include <iostream>
#include <type_traits>
namespace benchmark {

//Базовая специализация шаблонной функции получения корневой ноды в дереве.
//Пользователи класса обязаны сделать специализацию со своими типами.
template <typename Tree>
const auto GetRootNodePtr(const Tree& tree);

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

// Универсальный класс, содержащий логику анализа дерева.
// Шаблонизируется типом узла и инициализируется корневым узлом.
template <NodeType Node>
class UniversalTreeBenchmark {
 public:
  template <typename Tree>
  UniversalTreeBenchmark(const Tree& tree) : root_(GetRootNodePtr(tree)) {}

  void PrintHorizontally() {
    PrintRecursive("", root_, false);
    std::cout << std::endl;
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

      // print the value of the node
      std::cout << node->data << std::endl;

      // enter the next tree level - left and right branch
      PrintRecursive(prefix + (isLeft ? "│   " : "    "), node->left, true);
      PrintRecursive(prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
  }
};

//CTAD позволяющий определять тип ноды
template <typename Tree>
UniversalTreeBenchmark(const Tree& t) -> UniversalTreeBenchmark<
    std::remove_pointer_t<decltype(GetRootNodePtr(t))>>;

}  // namespace benchmark