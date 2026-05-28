#pragma once
#include <iostream>
#include <stdexcept>
#include "../lib_ITable/ITable.h"
#include "../lib_tvector/TVector.h"

template <typename Tvalue>
class HashTableD : public ITable<std::string, Tvalue> {
private:
    TVector<std::pair<std::string, Tvalue>> _data;
    TVector<int> _flags;
    size_t _size;

    size_t h1(const std::string& key) const {
        size_t hash = 0;
        for (char ch : key) hash = (hash * 131 + ch) % _data.size();
        return hash;
    }

    size_t h2(const std::string& key) const {
        size_t hash = 0;
        for (char ch : key) hash = (hash * 131 + ch);
        return 1 + (hash % (_data.size() - 1));
    }

    int find_index(const std::string& key) const {
        size_t idx = h1(key);
        size_t step = h2(key);
        for (size_t i = 0; i < _data.size(); ++i) {
            size_t pos = (idx + i * step) % _data.size();
            if (_flags[pos] == 0) return -1;
            if (_flags[pos] == 2) continue;
            if (_data[pos].first == key) return pos;
        }
        return -1;
    }

public:
    HashTableD(size_t capacity = 16) : _data(capacity), _size(0) {
        for (size_t i = 0; i < capacity; ++i) {
            _flags.push_back(0);
        }
    }
    ~HashTableD() override = default;

    void insert(const std::string& key, const Tvalue& val) override {
        int pos = find_index(key);
        if (pos != -1) {
            _data[pos].second = val;
            return;
        }

        size_t idx = h1(key);
        size_t step = h2(key);
        int first_deleted = -1;
        for (size_t i = 0; i < _data.size(); ++i) {
            size_t p = (idx + i * step) % _data.size();
            if (_flags[p] == 0) {
                if (first_deleted != -1) p = first_deleted;
                _data[p] = { key, val };
                _flags[p] = 1;
                _size++;
                return;
            }
            if (_flags[p] == 2 && first_deleted == -1) {
                first_deleted = p;
            }
        }
        if (first_deleted != -1) {
            _data[first_deleted] = { key, val };
            _flags[first_deleted] = 1;
            _size++;
            return;
        }
        throw std::runtime_error("Hash table is full");
    }

    Tvalue find(const std::string& key) const override {
        int pos = find_index(key);
        if (pos != -1) return _data[pos].second;
        throw std::runtime_error("Key not found");
    }

    void erase(const std::string& key) override {
        int pos = find_index(key);
        if (pos != -1) {
            _flags[pos] = 2;
            _size--;
        }
    }

    bool consist(const std::string& key) const noexcept override {
        return find_index(key) != -1;
    }

    bool is_empty() const noexcept override {
        return _size == 0;
    }

    std::ostream& print(std::ostream& out) const noexcept override {
        out << "HashTableD (capacity=" << _data.size() << ", size=" << _size << ")\n";
        for (size_t i = 0; i < _data.size(); ++i) {
            if (_flags[i] == 1) {
                out << "  [" << i << "] (" << _data[i].first << "," << _data[i].second << ")\n";
            }
            else if (_flags[i] == 2) {
                out << "  [" << i << "] (deleted)\n";
            }
            else {
                out << "  [" << i << "] (empty)\n";
            }
        }
        return out;
    }
};