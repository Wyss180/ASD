#pragma once
#include "ITable.h"
#include "../lib_list/List.h"

template <typename Tkey, typename Tvalue>
class UnsortedTableOnList : public ITable<Tkey, Tvalue> {
private:
    List<std::pair<Tkey, Tvalue>> _list;

public:
    UnsortedTableOnList() = default;
    ~UnsortedTableOnList() override = default;

    bool is_empty() const noexcept override {
        return _list.isEmpty();
    }

    void insert(const Tkey& key, const Tvalue& val) override {
        _list.push_back({ key, val });
    }

    Tvalue find(const Tkey& key) const override {
        auto& lst = const_cast<List<std::pair<Tkey, Tvalue>>&>(_list);
        for (auto it = lst.begin(); it != lst.end(); ++it) {
            if ((*it).first == key) {
                return (*it).second;
            }
        }
        throw std::logic_error("Key not found");
    }

    void erase(const Tkey& key) override {
        int pos = 0;
        for (auto it = _list.begin(); it != _list.end(); ++it, ++pos) {
            if ((*it).first == key) {
                _list.erase(pos);
                return;
            }
        }
        throw std::logic_error("Can't erase: key not found");
    }

    bool consist(const Tkey& key) const noexcept override {
        auto& lst = const_cast<List<std::pair<Tkey, Tvalue>>&>(_list);
        for (auto it = lst.begin(); it != lst.end(); ++it) {
            if ((*it).first == key) {
                return true;
            }
        }
        return false;
    }

    std::ostream& print(std::ostream& out) const noexcept override {
        auto& lst = const_cast<List<std::pair<Tkey, Tvalue>>&>(_list);
        out << "{ ";
        for (auto it = lst.begin(); it != lst.end(); ++it) {
            out << "(" << (*it).first << ", " << (*it).second << ") ";
        }
        out << "}";
        return out;
    }

    int size() const noexcept {
        return _list.size();
    }
};