#pragma once
#include <iostream>
#include <queue>
#include <stdexcept>

template <typename Tkey, typename Tvalue>
class Tree {
private:
    struct Node {
        std::pair<Tkey, Tvalue> data;
        Node* left;
        Node* right;
        Node(const Tkey& key, const Tvalue& value)
            : data(key, value), left(nullptr), right(nullptr) {
        }
    };

    Node* _root;

    void deleteTree(Node* node) {
        if (!node) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

    void lcr_rec(Node* node, std::ostream& out) const {
        if (!node) return;
        lcr_rec(node->left, out);
        out << "(" << node->data.first << ":" << node->data.second << ") ";
        lcr_rec(node->right, out);
    }

    void lrc_rec(Node* node, std::ostream& out) const {
        if (!node) return;
        lrc_rec(node->left, out);
        lrc_rec(node->right, out);
        out << "(" << node->data.first << ":" << node->data.second << ") ";
    }

    void clr_rec(Node* node, std::ostream& out) const {
        if (!node) return;
        out << "(" << node->data.first << ":" << node->data.second << ") ";
        clr_rec(node->left, out);
        clr_rec(node->right, out);
    }

    void width_rec(std::ostream& out) const {
        if (is_empty()) {
            out << "WIDTH: Tree is empty" << std::endl;
            return;
        }
        out << "WIDTH: ";
        std::queue<Node*> q;
        q.push(_root);
        int level = 0;
        while (!q.empty()) {
            int levelSize = (int)q.size();
            out << "Level " << level << ": ";
            for (int i = 0; i < levelSize; ++i) {
                Node* node = q.front(); q.pop();
                out << "(" << node->data.first << ":" << node->data.second << ") ";
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            out << std::endl;
            ++level;
        }
    }

public:
    Tree() : _root(nullptr) {}
    ~Tree() { deleteTree(_root); }

    bool is_empty() const { return _root == nullptr; }

    void insert(const Tkey& key, const Tvalue& value) {
        if (is_empty()) {
            _root = new Node(key, value);
            return;
        }
        std::queue<Node*> q;
        q.push(_root);
        while (!q.empty()) {
            Node* node = q.front(); q.pop();
            if (node->data.first == key) {
                node->data.second = value;
                return;
            }
            if (!node->left) {
                node->left = new Node(key, value);
                return;
            }
            else q.push(node->left);

            if (!node->right) {
                node->right = new Node(key, value);
                return;
            }
            else q.push(node->right);
        }
    }

    const Tvalue* find(const Tkey& key) const {
        if (is_empty()) return nullptr;
        std::queue<Node*> q;
        q.push(_root);
        while (!q.empty()) {
            Node* node = q.front(); q.pop();
            if (node->data.first == key)
                return &node->data.second;
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        return nullptr;
    }

    void remove(const Tkey& key) {
        if (is_empty()) return;

        Node* to_delete = nullptr;
        Node* last = nullptr;
        Node* parent_of_last = nullptr;

        std::queue<std::pair<Node*, Node*>> q;
        q.push({ _root, nullptr });

        while (!q.empty()) {
            auto [node, parent] = q.front(); q.pop();
            last = node;
            parent_of_last = parent;
            if (node->data.first == key)
                to_delete = node;

            if (node->left) q.push({ node->left, node });
            if (node->right) q.push({ node->right, node });
        }

        if (!to_delete) return;

        if (to_delete == last) {
            if (parent_of_last) {
                if (parent_of_last->left == last) parent_of_last->left = nullptr;
                else parent_of_last->right = nullptr;
            }
            else {
                _root = nullptr;
            }
            delete last;
            return;
        }

        to_delete->data = last->data;
        if (parent_of_last) {
            if (parent_of_last->left == last) parent_of_last->left = nullptr;
            else parent_of_last->right = nullptr;
        }
        else {
            _root = nullptr;
        }
        delete last;
    }

    void lcr(std::ostream& out) const {
        out << "LCR: ";
        lcr_rec(_root, out);
        out << std::endl;
    }

    void lrc(std::ostream& out) const {
        out << "LRC: ";
        lrc_rec(_root, out);
        out << std::endl;
    }

    void clr(std::ostream& out) const {
        out << "CLR: ";
        clr_rec(_root, out);
        out << std::endl;
    }

    void width(std::ostream& out) const {
        width_rec(out);
    }

    void lcr() const { lcr(std::cout); }
    void lrc() const { lrc(std::cout); }
    void clr() const { clr(std::cout); }
    void width() const { width(std::cout); }
};