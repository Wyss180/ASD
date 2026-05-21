#pragma once
#include "ITable.h"
#include "BSTree.h"

template <typename Tkey, typename Tvalue>
class BSTTable : public ITable<Tkey, Tvalue> {
private:
    BSTree<Tkey, Tvalue> _tree;

public:
    BSTTable() = default;
    ~BSTTable() override = default;

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
        out << _tree.to_string_sorted();
        return out;
    }

    std::string to_string_sorted() const {
        return _tree.to_string_sorted();
    }
};