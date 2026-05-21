#pragma once
#include <iostream>

template <typename Tkey, typename Tvalue>
class ITable {
public:
    virtual ~ITable() = default;
    virtual void insert(const Tkey& key, const Tvalue& val) = 0;
    virtual Tvalue find(const Tkey& key) const = 0;
    virtual void erase(const Tkey& key) = 0;
    virtual bool is_empty() const noexcept = 0;
    virtual bool consist(const Tkey& key) const noexcept = 0;
    virtual std::ostream& print(std::ostream& out) const noexcept = 0;
};
