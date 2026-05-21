#pragma once
#include "ITable.h"
#include "../lib_tree/Tree.h"

template<typename Tkey, typename Tvalue>
class UnsortedTableOnTree : public ITable<Tkey, Tvalue> {
private:
    Tree<Tkey, Tvalue> _tree;
public:
    UnsortedTableOnTree() {}
    ~UnsortedTableOnTree() {}

    void insert(const Tkey& key, const Tvalue& val) override {
        _tree.insert(key, val);
    }

    Tvalue find(const Tkey& key) const override {
        auto& tree = const_cast<Tree<Tkey, Tvalue>&>(_tree);
        const Tvalue* p = tree.find(key);
        if (p == nullptr) throw std::logic_error("didn't find key");
        return *p;
    }

    void erase(const Tkey& key) override {
        _tree.remove(key);
    }

    std::ostream& print(std::ostream& out) const noexcept override {
        auto& tree = const_cast<Tree<Tkey, Tvalue>&>(_tree);
        tree.lcr(out);
        return out;
    }

    bool is_empty() const noexcept override {
        auto& tree = const_cast<Tree<Tkey, Tvalue>&>(_tree);
        return tree.is_empty();
    }

    bool consist(const Tkey& key) const noexcept override {
        try {
            find(key);
            return true;
        }
        catch (...) {
            return false;
        }
    }
};