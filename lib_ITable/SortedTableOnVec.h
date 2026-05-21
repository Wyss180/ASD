#pragma once
#include "ITable.h"
#include "../lib_tvector/TVector.h"

template <typename Tkey, typename Tvalue>
class SortedTableOnVec : public ITable<Tkey, Tvalue> {
private:
    TVector<std::pair<Tkey, Tvalue>> _rows;

    std::pair<bool, int> binary_find(const Tkey& key) const {
        if (_rows.size() == 0) return { false, 0 };
        int lo = 0, hi = _rows.size() - 1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (_rows[mid].first == key) return { true, mid };
            if (_rows[mid].first < key) lo = mid + 1;
            else hi = mid - 1;
        }
        return { false, lo };
    }

public:
    SortedTableOnVec() = default;
    ~SortedTableOnVec() override = default;

    bool is_empty() const noexcept override {
        return _rows.size() == 0;
    }

    void insert(const Tkey& key, const Tvalue& val) override {
        auto res = binary_find(key);
        if (res.first) {
            _rows[res.second].second = val;
            return;
        }
        int pos = res.second;
        _rows.insert(pos, { key, val });
    }

    Tvalue find(const Tkey& key) const override {
        if (_rows.size() == 0) throw std::logic_error("Key not found");
        auto res = binary_find(key);
        if (res.first) return _rows[res.second].second;
        throw std::logic_error("Key not found");
    }

    void erase(const Tkey& key) override {
        if (_rows.size() == 0) throw std::logic_error("Can't erase: empty");
        auto res = binary_find(key);
        if (!res.first) throw std::logic_error("Can't erase: key not found");
        _rows.erase(res.second, 1);
    }

    bool consist(const Tkey& key) const noexcept override {
        if (_rows.size() == 0) return false;
        auto res = binary_find(key);
        return res.first;
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