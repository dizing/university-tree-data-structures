#include <array>
#include <map>
#include <random>

#include "avl_tree.h"
#include "naive_bst.h"
#include "perfectly_balanced_bst.h"
#include "universal_tree_benchmark.h"

template <>
auto benchmark::GetRootNodePtr<
    implementations::PerfectlyBalancedBinaryTree<int>>(
    const implementations::PerfectlyBalancedBinaryTree<int>& tree) {
  return tree.GetRoot();
}

template <>
auto benchmark::GetRootNodePtr<implementations::AVLTree<int>>(
    const implementations::AVLTree<int>& tree) {
  return static_cast<const implementations::Node<int>*>(tree.GetRoot());
}

std::vector<int> GenerateRandomData(std::size_t size) {
  std::random_device rd;  // Only used once to initialise (seed) engine
  std::mt19937 rng(
      rd());  // Random-number engine used (Mersenne-Twister in this case)
  std::uniform_int_distribution<int> uni{-10000, 10000};  // Guaranteed unbiased

  std::vector<int> data;
  while (data.size() < size) {
    if (int new_value = uni(rng);
        std::find(data.begin(), data.end(), new_value) == data.end()) {
      data.emplace_back(new_value);
    }
  }
  return data;
}

int main() {
  // Подготовка данных
  std::array<std::vector<int>, 5> data_set_list;
  for (std::size_t i = 0; i < 5; ++i) {
    data_set_list[i] = GenerateRandomData((1 + i) * 100);
  }

  // Заполнение авл деревьев наборами данных
  std::array<implementations::AVLTree<int>, 5> avl_trees;
  for (std::size_t i = 0; i < 5; ++i) {
    for (auto& value : data_set_list[i]) {
      avl_trees[i].Insert(value);
    }
  }
  std::cout << "Распечатать авл деревья слева направо разных размеров"
            << std::endl;
  for (std::size_t i = 0; i < 5; ++i) {
    std::cout << "Размер: " << (i + 1) * 100 << std::endl;
    UniformTraversing(avl_trees[i].GetRoot(),
                      [](auto& value) { std::cout << value << " "; });
    std::cout << std::endl;
  }

  std::cout << "Вывод анализа АВЛ дерева" << std::endl;
  for (auto& tree : avl_trees) {
    benchmark::UniversalTreeBenchmark bench(tree);
    std::cout << bench.CalculateSize() << ", " << bench.CheckSum() << ", "
              << bench.CalculateHeight() << ", "
              << bench.CalculateAverageDepth() << std::endl;
  }

  std::cout << "Вывод анализа идеально сбалансированного дерева поиска"
            << std::endl;
  for (auto& data_set : data_set_list) {
    implementations::PerfectlyBalancedBinaryTree<int> tree{data_set};
    benchmark::UniversalTreeBenchmark bench(tree);
    std::cout << bench.CalculateSize() << ", " << bench.CheckSum() << ", "
              << bench.CalculateHeight() << ", "
              << bench.CalculateAverageDepth() << std::endl;
  }
}