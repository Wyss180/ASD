#include <iostream>
#include <stdexcept>
#include <cmath>
#include "monom.h"

Monom::Monom(double coeff, int degX, int degY, int degZ) {
    this->coeff = coeff;
    deg[0] = degX;
    deg[1] = degY;
    deg[2] = degZ;
}

Monom::Monom(const Monom& other) {
    deg[0] = other.deg[0];
    deg[1] = other.deg[1];
    deg[2] = other.deg[2];
    coeff = other.coeff;
}

bool Monom::operator==(const Monom& other) const {
    return coeff == other.coeff &&
        deg[0] == other.deg[0] &&
        deg[1] == other.deg[1] &&
        deg[2] == other.deg[2];
}

bool Monom::operator!=(const Monom& other) const {
    return !(*this == other);
}

bool Monom::operator>(const Monom& other) const {
    if (deg[0] != other.deg[0]) return deg[0] > other.deg[0];
    if (deg[1] != other.deg[1]) return deg[1] > other.deg[1];
    if (deg[2] != other.deg[2]) return deg[2] > other.deg[2];
    return coeff > other.coeff;
}

Monom Monom::operator+(const Monom& other) const {
    if (deg[0] != other.deg[0] || deg[1] != other.deg[1] || deg[2] != other.deg[2])
        throw std::invalid_argument("Cannot add monoms with different degrees");
    return Monom(coeff + other.coeff, deg[0], deg[1], deg[2]);
}

Monom Monom::operator-(const Monom& other) const {
    if (deg[0] != other.deg[0] || deg[1] != other.deg[1] || deg[2] != other.deg[2])
        throw std::invalid_argument("Cannot subtract monoms with different degrees");
    return Monom(coeff - other.coeff, deg[0], deg[1], deg[2]);
}

Monom Monom::operator*(const Monom& other) const {
    return Monom(coeff * other.coeff,
        deg[0] + other.deg[0],
        deg[1] + other.deg[1],
        deg[2] + other.deg[2]);
}

Monom Monom::operator/(const Monom& other) const {
    if (other.coeff == 0.0)
        throw std::invalid_argument("Division by zero monom");
    if (deg[0] < other.deg[0] || deg[1] < other.deg[1] || deg[2] < other.deg[2])
        throw std::invalid_argument("Resulting monom has negative degree");
    return Monom(coeff / other.coeff,
        deg[0] - other.deg[0],
        deg[1] - other.deg[1],
        deg[2] - other.deg[2]);
}

Monom& Monom::operator+=(const Monom& other) {
    if (deg[0] != other.deg[0] || deg[1] != other.deg[1] || deg[2] != other.deg[2])
        throw std::invalid_argument("Cannot add monoms with different degrees");
    coeff += other.coeff;
    return *this;
}

Monom& Monom::operator-=(const Monom& other) {
    if (deg[0] != other.deg[0] || deg[1] != other.deg[1] || deg[2] != other.deg[2])
        throw std::invalid_argument("Cannot subtract monoms with different degrees");
    coeff -= other.coeff;
    return *this;
}

Monom& Monom::operator*=(const Monom& other) {
    coeff *= other.coeff;
    deg[0] += other.deg[0];
    deg[1] += other.deg[1];
    deg[2] += other.deg[2];
    return *this;
}

Monom& Monom::operator/=(const Monom& other) {
    if (other.coeff == 0.0)
        throw std::invalid_argument("Division by zero monom");
    if (deg[0] < other.deg[0] || deg[1] < other.deg[1] || deg[2] < other.deg[2])
        throw std::invalid_argument("Resulting monom has negative degree");
    coeff /= other.coeff;
    deg[0] -= other.deg[0];
    deg[1] -= other.deg[1];
    deg[2] -= other.deg[2];
    return *this;
}

Monom Monom::operator*(double k) const {
    return Monom(coeff * k, deg[0], deg[1], deg[2]);
}

Monom Monom::operator/(double k) const {
    if (k == 0.0) throw std::invalid_argument("Division by zero");
    return Monom(coeff / k, deg[0], deg[1], deg[2]);
}

Monom& Monom::operator*=(double k) {
    coeff *= k;
    return *this;
}

Monom& Monom::operator/=(double k) {
    if (k == 0.0) throw std::invalid_argument("Division by zero");
    coeff /= k;
    return *this;
}

Monom Monom::operator-() const {
    return Monom(-coeff, deg[0], deg[1], deg[2]);
}

double Monom::value(double x, double y, double z) const {
    return coeff * std::pow(x, deg[0]) * std::pow(y, deg[1]) * std::pow(z, deg[2]);
}

std::ostream& operator<<(std::ostream& os, const Monom& m) {
    if (m.coeff == 0) {
        os << "0";
        return os;
    }
    if (m.coeff != 1 || (m.deg[0] == 0 && m.deg[1] == 0 && m.deg[2] == 0))
        os << m.coeff;
    else if (m.coeff == -1)
        os << "-";

    if (m.deg[0] > 0) {
        os << "x";
        if (m.deg[0] > 1) os << "^" << m.deg[0];
    }
    if (m.deg[1] > 0) {
        os << "y";
        if (m.deg[1] > 1) os << "^" << m.deg[1];
    }
    if (m.deg[2] > 0) {
        os << "z";
        if (m.deg[2] > 1) os << "^" << m.deg[2];
    }
    return os;
}

std::istream& operator>>(std::istream& is, Monom& m) {
    std::cout << "Enter coefficient: ";
    is >> m.coeff;
    std::cout << "Enter degree for x: ";
    is >> m.deg[0];
    std::cout << "Enter degree for y: ";
    is >> m.deg[1];
    std::cout << "Enter degree for z: ";
    is >> m.deg[2];
    return is;
}