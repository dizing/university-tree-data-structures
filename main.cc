#include <array>
#include <map>
#include <random>

#include "avl_tree.h"
#include "b_tree.h"
#include "universal_tree_benchmark.h"

template <>
auto benchmark::GetRootNodePtr<implementations::AVLTree<int>>(
    const implementations::AVLTree<int>& tree) {
  return static_cast<const implementations::Node<int>*>(tree.GetRoot());
}

template <>
auto benchmark::GetRootNodePtr<implementations::BinaryBTree<int>>(
    const implementations::BinaryBTree<int>& tree) {
  return tree.GetRoot();
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
  std::cout << "Вывод анализа АВЛ дерева" << std::endl;
  for (auto& tree : avl_trees) {
    benchmark::UniversalTreeBenchmark bench(tree);
    std::cout << bench.CalculateSize() << ", " << bench.CheckSum() << ", "
              << bench.CalculateHeight() << ", "
              << bench.CalculateAverageDepth() << std::endl;
  }

  std::cout << "Вывод анализа двоичного б дерева поиска" << std::endl;
  for (auto& data_set : data_set_list) {
    implementations::BinaryBTree<int> tree;
    for (auto val : data_set) {
      tree.Insert(val);
    }
    benchmark::UniversalTreeBenchmark bench(tree);
    std::cout << bench.CalculateSize() << ", " << bench.CheckSum() << ", "
              << tree.GetLevels() << ", " << bench.CalculateHeight() << ", "
              << bench.CalculateAverageDepth() << std::endl;
  }
}