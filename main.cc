#include <map>
#include <random>

#include "naive_bst.h"
#include "universal_tree_benchmark.h"
#include "perfectly_balanced_bst.h"

template <>
auto benchmark::GetRootNodePtr<implementations::NaiveBinarySearchTree<int>>(
    const implementations::NaiveBinarySearchTree<int>& tree) {
  return tree.GetRoot();
}

template <>
auto benchmark::GetRootNodePtr<implementations::PerfectlyBalancedBinaryTree<int>>(
    const implementations::PerfectlyBalancedBinaryTree<int>& tree) {
  return tree.GetRoot();
}

std::vector<int> GenerateRandomData(std::size_t size) {
  std::random_device rd;     // Only used once to initialise (seed) engine
  std::mt19937 rng(rd());    // Random-number engine used (Mersenne-Twister in this case)
  std::uniform_int_distribution<int> uni{-10000, 10000}; // Guaranteed unbiased

  std::vector<int> data;
  while ( data.size() < size ) {
    if (int new_value = uni(rng); 
        std::find(data.begin(), data.end(), new_value) == data.end()) {
      data.emplace_back(new_value);
    }
  }
  return data;
}

int main() {
  std::cout << "Вывод анализа случайного дерева поиска" << std::endl;
  for (auto& data_size : {100u, 200u, 300u, 400u, 500u}) {
    implementations::NaiveBinarySearchTree<int> tree;
    for (auto& value : GenerateRandomData(data_size)) {
      tree.Insert(value);
    }
    benchmark::UniversalTreeBenchmark bench(tree);
    std::cout << bench.CalculateSize() << ", " << bench.CheckSum() << ", "
              << bench.CalculateHeight() << ", " << bench.CalculateAverageDepth() << std::endl;
  }

  std::cout << "Вывод анализа идеально сбалансированного дерева поиска" << std::endl;
  for (auto& data_size : {100u, 200u, 300u, 400u, 500u}) {
    implementations::PerfectlyBalancedBinaryTree<int> tree{GenerateRandomData(data_size)};
    benchmark::UniversalTreeBenchmark bench(tree);
    std::cout << bench.CalculateSize() << ", " << bench.CheckSum() << ", "
              << bench.CalculateHeight() << ", " << bench.CalculateAverageDepth() << std::endl;
  }

}