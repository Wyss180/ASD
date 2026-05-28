#pragma once
#include <iostream>
#include <stdexcept>
#include <sstream>

template <typename TKey, typename TValue>
class BSTree {
private:
    struct Node {
        std::pair<TKey, TValue> data;
        Node* left;
        Node* right;
        Node(const TKey& key, const TValue& val)
            : data(key, val), left(nullptr), right(nullptr) {
        }
    };

    Node* _root;

    Node* insert(Node* node, const TKey& key, const TValue& val) {
        if (!node) return new Node(key, val);
        if (key < node->data.first)
            node->left = insert(node->left, key, val);
        else if (key > node->data.first)
            node->right = insert(node->right, key, val);
        else
            throw std::logic_error("Key already exists");
        return node;
    }

    Node* findMin(Node* node) const {
        while (node && node->left) node = node->left;
        return node;
    }

    Node* erase(Node* node, const TKey& key) {
        if (!node) throw std::logic_error("Key not found");
        if (key < node->data.first)
            node->left = erase(node->left, key);
        else if (key > node->data.first)
            node->right = erase(node->right, key);
        else {
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            }
            else {
                Node* succ = findMin(node->right);
                node->data = succ->data;
                node->right = erase(node->right, succ->data.first);
            }
        }
        return node;
    }

    const TValue* find(Node* node, const TKey& key) const {
        if (!node) return nullptr;
        if (key == node->data.first) return &node->data.second;
        if (key < node->data.first) return find(node->left, key);
        else return find(node->right, key);
    }

    void inOrder(Node* node, std::ostream& out) const {
        if (!node) return;
        inOrder(node->left, out);
        out << node->data.first << ":" << node->data.second << " ";
        inOrder(node->right, out);
    }

    void preOrder(Node* node, std::ostream& out) const {
        if (!node) return;
        out << node->data.first << ":" << node->data.second << " ";
        preOrder(node->left, out);
        preOrder(node->right, out);
    }

    void deleteTree(Node* node) {
        if (!node) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

public:
    BSTree() : _root(nullptr) {}
    ~BSTree() { deleteTree(_root); }

    bool is_empty() const { return _root == nullptr; }

    void insert(const TKey& key, const TValue& val) {
        _root = insert(_root, key, val);
    }

    const TValue& find(const TKey& key) const {
        const TValue* res = find(_root, key);
        if (!res) throw std::logic_error("Key not found");
        return *res;
    }

    void erase(const TKey& key) {
        _root = erase(_root, key);
    }

    std::string to_string() const {
        std::ostringstream oss;
        preOrder(_root, oss);
        return oss.str();
    }

    std::string to_string_sorted() const {
        std::ostringstream oss;
        inOrder(_root, oss);
        return oss.str();
    }

    TKey root() const {
        if (!_root) throw std::logic_error("Tree is empty");
        return _root->data.first;
    }
};