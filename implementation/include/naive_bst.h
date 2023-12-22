#pragma once
#include <memory>
#include <iostream>

namespace implementations {

template<typename T>
class NaiveBinarySearchTree {
    public:
    using ValueType = T; 
    struct Node {
        Node * left;
        Node * right;
        ValueType data;

        Node(ValueType data) : left(nullptr), right(nullptr), data(std::move(data)) {}
        ~Node() {
            delete left;
            delete right;
        }
    };
    
    NaiveBinarySearchTree() : root_(nullptr) {}
    ~NaiveBinarySearchTree() {
        delete root_;
    }
    
    void Insert(ValueType value) {
        if (!root_) {
            root_ = new Node(value);
            return;
        }
        if (value > root_->data) {
            
        }
        if (value < root_->data) {

        }
        // Если одинаковы ничего не делать -- логика сета
    }


    private:
    Node * root_;
    
};



}