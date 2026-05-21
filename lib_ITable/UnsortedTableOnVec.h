#pragma once
#include "ITable.h"
#include "../lib_tvector/TVector.h"

template <typename Tkey, typename Tvalue>
class UnsortedTableOnVec : public ITable<Tkey, Tvalue> {
private:
    TVector<std::pair<Tkey, Tvalue>> _rows;

public:
    UnsortedTableOnVec() = default;
    ~UnsortedTableOnVec() override = default;

    bool is_empty() const noexcept override {
        return _rows.size() == 0;
    }

    void insert(const Tkey& key, const Tvalue& val) override {
        _rows.push_back({ key, val });
    }

    Tvalue find(const Tkey& key) const override {
        for (int i = 0; i < _rows.size(); ++i) {
            if (_rows[i].first == key) {
                return _rows[i].second;
            }
        }
        throw std::logic_error("Key not found");
    }

    void erase(const Tkey& key) override {
        for (int i = 0; i < _rows.size(); ++i) {
            if (_rows[i].first == key) {
                _rows.erase(i, 1);
                return;
            }
        }
        throw std::logic_error("Can't erase: key not found");
    }

    bool consist(const Tkey& key) const noexcept override {
        for (int i = 0; i < _rows.size(); ++i) {
            if (_rows[i].first == key) {
                return true;
            }
        }
        return false;
    }

    std::ostream& print(std::ostream& out) const noexcept override {
        out << "{ ";
        for (int i = 0; i < _rows.size(); ++i) {
            out << "(" << _rows[i].first << ", " << _rows[i].second << ") ";
        }
        out << "}";
        return out;
    }
};