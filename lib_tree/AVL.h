#pragma once
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <sstream>

template <typename Tkey, typename Tvalue>
class AVL {
private:
    struct Node {
        std::pair<Tkey, Tvalue> data;
        Node* left;
        Node* right;
        int height;

        Node(const Tkey& key, const Tvalue& val)
            : data(key, val), left(nullptr), right(nullptr), height(1) {
        }
    };

    Node* _root;

    int height(Node* node) const {
        return node ? node->height : 0;
    }

    int balanceFactor(Node* node) const {
        return node ? height(node->left) - height(node->right) : 0;
    }

    void updateHeight(Node* node) {
        if (node)
            node->height = 1 + std::max(height(node->left), height(node->right));
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);
        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);
        return y;
    }

    Node* balance(Node* node) {
        if (!node) return nullptr;
        
        //int h1 = node->height;
        updateHeight(node);

        int bf = balanceFactor(node);

        if (bf > 1) {
            if (balanceFactor(node->left) < 0)
                node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (bf < -1) {
            if (balanceFactor(node->right) > 0)
                node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        /*updateHeight(node);
        if (h1 == node->height) {
            return node;
        }*/

        return node;
    }

    Node* insert(Node* node, const Tkey& key, const Tvalue& val) {
        if (!node)
            return new Node(key, val);

        if (key < node->data.first)
            node->left = insert(node->left, key, val);
        else if (key > node->data.first)
            node->right = insert(node->right, key, val);
        else
            throw std::logic_error("Key already exists");

        return balance(node);
    }

    /*Node* insert(Node* node, const Tkey& key, const Tvalue& val, bool& heightChanged) {
        if (!node) {
            heightChanged = true;
            return new Node(key, val);
        }
        if (key < node->data.first) {
            node->left = insert(node->left, key, val, heightChanged);
        }
        else if (key > node->data.first) {
            node->right = insert(node->right, key, val, heightChanged);
        }
        else {
            throw std::logic_error("Key already exists");
        }

        if (!heightChanged) return node;

        int oldHeight = node->height;
        node = balance(node);
        if (node->height == oldHeight)
            heightChanged = false;
        return node;
    }*/

    Node* findMin(Node* node) const {
        while (node && node->left)
            node = node->left;
        return node;
    }

    Node* erase(Node* node, const Tkey& key) {
        if (!node)
            throw std::logic_error("Key not found");

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
                Node* successor = findMin(node->right);
                node->data = successor->data;
                node->right = erase(node->right, successor->data.first);
            }
        }
        return balance(node);
    }

    const Tvalue* find(Node* node, const Tkey& key) const {
        if (!node) return nullptr;
        if (key == node->data.first)
            return &node->data.second;
        if (key < node->data.first)
            return find(node->left, key);
        else
            return find(node->right, key);
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
    AVL() : _root(nullptr) {}
    ~AVL() { deleteTree(_root); }

    void insert(const Tkey& key, const Tvalue& val) {
        _root = insert(_root, key, val);
    }

    const Tvalue& find(const Tkey& key) const {
        const Tvalue* res = find(_root, key);
        if (!res) throw std::logic_error("Key not found");
        return *res;
    }

    void erase(const Tkey& key) {
        _root = erase(_root, key);
    }

    bool is_empty() const {
        return _root == nullptr;
    }

    void print_sorted(std::ostream& out) const {
        inOrder(_root, out);
    }

    void print_preorder(std::ostream& out) const {
        preOrder(_root, out);
    }

    std::string to_string() const {
        std::ostringstream oss;
        print_preorder(oss);
        return oss.str();
    }

    std::string to_string_sorted() const {
        std::ostringstream oss;
        print_sorted(oss);
        return oss.str();
    }

    int height() const {
        return height(_root);
    }

    Tkey root() const {
        if (!_root) throw std::logic_error("Tree is empty");
        return _root->data.first;
    }
};