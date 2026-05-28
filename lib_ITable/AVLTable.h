#pragma once
#include "ITable.h"
#include "../lib_tree/AVL.h"

template <typename Tkey, typename Tvalue>
class AVLTable : public ITable<Tkey, Tvalue> {
private:
    AVL<Tkey, Tvalue> _tree;

public:
    AVLTable() = default;
    ~AVLTable() override = default;

    bool is_empty() const noexcept override {
        return _tree.is_empty();
    }

    void insert(const Tkey& key, const Tvalue& val) override {
        _tree.insert(key, val);
    }

    Tvalue find(const Tkey& key) const override {
        return _tree.find(key);
    }

    void erase(const Tkey& key) override {
        _tree.erase(key);
    }

    bool consist(const Tkey& key) const noexcept override {
        try {
            _tree.find(key);
            return true;
        }
        catch (...) {
            return false;
        }
    }

    std::ostream& print(std::ostream& out) const noexcept override {
        _tree.print_sorted(out);
        return out;
    }

    Tkey root() const {
        return _tree.root(); 
    }
};