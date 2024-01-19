#pragma once
#include <algorithm>
#include <type_traits>

namespace implementations {

// Общая структура для узла дерева
// Автоматически освобождает всё дерево при деконструкции
// При копировании от другой ноды копирует значение но не встраивается в дерево
// При перемещении забирает владение значением и нодами потомками
template<typename T>
struct Node {
    using ValueType = T;
    Node* left;
    Node* right;
    ValueType data;

    Node(ValueType value) noexcept(noexcept(std::is_nothrow_move_constructible_v<ValueType>)) 
        : left(nullptr), right(nullptr), data(std::move(value)) 
        {} 
    
    Node(const Node& other) noexcept(noexcept(std::is_nothrow_constructible_v<ValueType>))
     : left(nullptr), right(nullptr), data(other.data) {}

    Node(Node&& other) noexcept(noexcept(std::is_nothrow_move_constructible_v<ValueType>))
     : left(other.left), right(other.right), data(std::move(data)) {
        other.left = nullptr;
        other.right = nullptr;
    }
    Node& operator=(const Node& other) noexcept(noexcept(std::is_nothrow_copy_assignable_v<ValueType>)) {
        delete left;
        delete right;
        left = nullptr;
        right = nullptr;
        data = other.data;
        return *this;
    }
    Node& operator=(Node&& other) noexcept(noexcept(std::is_nothrow_move_assignable_v<ValueType>)) {
        data = std::move(other.data);
        delete left;
        delete right;
        left = other.left;
        right = other.right;
        other.left = nullptr;
        other.right = nullptr;
        return *this;
    }
    ~Node() {
      delete left;
      delete right;
    }
  };
  

  template<typename T>
  const Node<T> * FindByKey (const Node<T>* node, const typename Node<T>::ValueType& key) {
    if (!node) return nullptr;
    if (node->data == key) return node;
    auto left_try = FindByKey(node->left, key);
    if (left_try) return left_try;
    auto right_try = FindByKey(node->right, key);
    if (right_try) return right_try;
    // Не найдено элемента
    return nullptr;
  }

  // Вызвать функтор, передав данные в каждой ноде
  template<typename T>
  void UniformTraversing(Node<T>* node, std::function<void(typename Node<T>::ValueType &)> func) {
    if (!node) return;
    UniformTraversing(node->left, func);
    func(node->data);
    UniformTraversing(node->right, func);
  }

}  // namespace implementations