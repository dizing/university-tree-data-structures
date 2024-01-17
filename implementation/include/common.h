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

    Node(ValueType data) noexcept(noexcept(std::is_nothrow_move_constructible_v<ValueType>)) 
        : left(nullptr), right(nullptr), data(std::move(data)) 
        {} 
    
    Node(const Node& other) noexcept(noexcept(std::is_nothrow_constructible_v<ValueType>))
     : left(nullptr), right(nullptr), data(other.data) {}

    Node(Node&& other) noexcept(noexcept(std::is_nothrow_move_constructible_v<ValueType>))
     : left(other.left), right(other.right), data(std::move(data)) {
        other.left = nullptr;
        other.right = nullptr;
    }
    Node& operator=(const Node& other) noexcept(noexcept(std::is_nothrow_assignable_v<ValueType>)) {
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

}  // namespace implementations