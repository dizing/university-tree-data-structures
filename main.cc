#include <map>

#include "naive_bst.h"
#include "universal_tree_benchmark.h"

template <>
auto benchmark::GetRootNodePtr<implementations::NaiveBinarySearchTree<int>>(
    const implementations::NaiveBinarySearchTree<int>& tree) {
  return tree.GetRoot();
}

int main() {
  implementations::NaiveBinarySearchTree<int> a;
  a.Insert(70);
  a.Insert(234);
  a.Insert(2);
  a.Insert(3);
  a.Insert(1);
  a.Insert(40);
  a.Insert(37);

  benchmark::UniversalTreeBenchmark b(a);
  b.PrintHorizontally();
}