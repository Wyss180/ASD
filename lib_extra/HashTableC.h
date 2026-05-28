#pragma once
#include <iostream>
#include <stdexcept>
#include "../lib_ITable/ITable.h"
#include "../lib_list/List.h"
#include "../lib_tvector/TVector.h"

template <typename Tvalue>
class HashTableC : public ITable<std::string, Tvalue> {
private:
    TVector<List<std::pair<std::string, Tvalue>>> _rows;

    size_t h(const std::string& key) const noexcept {
        size_t hashvalue = 0;
        for (char sym : key) {
            hashvalue = (hashvalue + sym) % _rows.size();
        }
        return hashvalue;
    }

public:
    HashTableC(size_t capacity = 16) : _rows(capacity) {}
    ~HashTableC() override = default;

    void insert(const std::string& key, const Tvalue& val) override {
        size_t index = h(key);
        for (auto it = _rows[index].begin(); it != _rows[index].end(); ++it) {
            if ((*it).first == key) {
                (*it).second = val;
                return;
            }
        }
        _rows[index].push_back({ key, val });
    }

    Tvalue find(const std::string& key) const override {
        size_t index = h(key);
        auto& lst = const_cast<List<std::pair<std::string, Tvalue>>&>(_rows[index]);
        for (auto it = lst.begin(); it != lst.end(); ++it) {
            if ((*it).first == key) return (*it).second;
        }
        throw std::runtime_error("Key not found");
    }

    void erase(const std::string& key) override {
        size_t index = h(key);
        size_t pos = 0;
        for (auto it = _rows[index].begin(); it != _rows[index].end(); ++it, ++pos) {
            if ((*it).first == key) {
                _rows[index].erase(pos);
                return;
            }
        }
    }

    bool consist(const std::string& key) const noexcept override {
        size_t index = h(key);
        auto& lst = const_cast<List<std::pair<std::string, Tvalue>>&>(_rows[index]);
        for (auto it = lst.begin(); it != lst.end(); ++it) {
            if ((*it).first == key) return true;
        }
        return false;
    }

    std::ostream& print(std::ostream& out) const noexcept override {
        out << "HashTableC (size=" << _rows.size() << ")\n";
        for (size_t i = 0; i < _rows.size(); ++i) {
            auto& lst = const_cast<List<std::pair<std::string, Tvalue>>&>(_rows[i]);
            if (!lst.isEmpty()) {
                out << "  bucket[" << i << "]: ";
                for (auto it = lst.begin(); it != lst.end(); ++it) {
                    out << "(" << (*it).first << "," << (*it).second << ") ";
                }
                out << "\n";
            }
        }
        return out;
    }

    void merge(const HashTableC<Tvalue>& other) {
        for (size_t i = 0; i < other._rows.size(); ++i) {
            auto& lst = const_cast<List<std::pair<std::string, Tvalue>>&>(other._rows[i]);
            for (auto it = lst.begin(); it != lst.end(); ++it) {
                this->insert((*it).first, (*it).second);
            }
        }
    }

    bool is_empty() const noexcept override {
        for (size_t i = 0; i < _rows.size(); ++i) {
            if (!_rows[i].isEmpty()) return false;
        }
        return true;
    }
};