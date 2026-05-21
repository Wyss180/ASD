#include <iostream>
#include <stdexcept>
#include <cmath>
#include <sstream>
#include "../lib_monom/Monom.h"
#include "polynom.h"
#include "../lib_doubly_linked_list/doubly_linked_list.h"

Polynom::Polynom() {
	monoms = DList<Monom>();
}

Polynom::Polynom(const Polynom& other) {
	monoms = other.monoms;
}

Polynom::~Polynom() {
}

Polynom& Polynom::operator=(const Polynom& other) {
	if (this != &other) {
		monoms = other.monoms;
	}
	return *this;
}

Polynom::Polynom(const std::string& s) {
	std::string str = s;
	for (int i = 0; i < s.size(); ++i) {
		if (str[i] == '-') {
			str.insert(i, "+");
			++i;
		}
	}
	std::stringstream ss(str);
	std::string token;
	while (std::getline(ss, token, '+')) {
		if (token.empty()) continue;
		double coeff = 1;
		int degX = 0; int degY = 0; int degZ = 0;

		std::string work = token;
		if (!work.empty() && work[0] == '-') {
			if (work.size() == 1 || std::isalpha(static_cast<unsigned char>(work[1]))) {
				coeff = -1;
				work = work.substr(1);
			}
		}
		if (!work.empty() && (std::isdigit(static_cast<unsigned char>(work[0])) ||
			(work.size() > 1 && work[0] == '-' && std::isdigit(static_cast<unsigned char>(work[1])))))
		{
			std::stringstream tnum(work);
			tnum >> coeff;
			std::string rest;
			std::getline(tnum, rest);
			work = rest;
		}

		std::stringstream t(work);
		char c;
		while (t >> c) {
			if (c == 'x') {
				if (t.peek() == '^') {
					t.get(); t >> degX;
				}
				else { degX = 1; }
			}
			if (c == 'y') {
				if (t.peek() == '^') {
					t.get(); t >> degY;
				}
				else { degY = 1; }
			}
			if (c == 'z') {
				if (t.peek() == '^') {
					t.get(); t >> degZ;
				}
				else { degZ = 1; }
			}
		}
		addMonom(Monom(coeff, degX, degY, degZ));
	}
}

void Polynom::addMonom(const Monom& m) {
	if (m.getCoeff() == 0.0)
		return;

	for (auto it = monoms.begin(); it != monoms.end(); ++it) {
		if (it->getDegX() == m.getDegX() &&
			it->getDegY() == m.getDegY() &&
			it->getDegZ() == m.getDegZ())
		{
			*it += m;
			if (it->getCoeff() == 0.0) {
				monoms.erase(it);
			}
			return;
		}
		if (m > *it) {
			monoms.insert(it, m);
			return;
		}
	}
	monoms.push_back(m);
}

Polynom Polynom::operator+(const Polynom& other) {
	Polynom result(*this);
	for (auto it = other.getMonoms().begin(); it != other.getMonoms().end(); ++it) {
		result.addMonom(*it);
	}
	return result;
}

Polynom Polynom::operator-(const Polynom& other) {
	Polynom result(*this);
	for (auto it = other.getMonoms().begin(); it != other.getMonoms().end(); ++it) {
		Monom neg = *it;
		neg.setCoeff(-neg.getCoeff());
		result.addMonom(neg);
	}
	return result;
}

Polynom Polynom::operator*(const Polynom& other) {
	Polynom result;
	for (auto it1 = this->getMonoms().begin(); it1 != this->getMonoms().end(); ++it1) {
		for (auto it2 = other.getMonoms().begin(); it2 != other.getMonoms().end(); ++it2) {
			Monom m(it1->getCoeff() * it2->getCoeff(), it1->getDegX() + it2->getDegX(), it1->getDegY() + it2->getDegY(), it1->getDegZ() + it2->getDegZ());
			result.addMonom(m);
		}
	}
	return result;
}

Polynom& Polynom::operator*=(const Polynom& other) {
	Polynom temp;
	for (auto it1 = this->getMonoms().begin(); it1 != this->getMonoms().end(); ++it1) {
		for (auto it2 = other.getMonoms().begin(); it2 != other.getMonoms().end(); ++it2) {
			Monom m(it1->getCoeff() * it2->getCoeff(), it1->getDegX() + it2->getDegX(), it1->getDegY() + it2->getDegY(), it1->getDegZ() + it2->getDegZ());
			temp.addMonom(m);
		}
	}
	*this = temp;
	return *this;
}

Polynom& Polynom::operator+=(const Polynom& other) {
	for (auto it = other.getMonoms().begin(); it != other.getMonoms().end(); ++it) {
		addMonom(*it);
	}
	return *this;
}

Polynom& Polynom::operator-=(const Polynom& other) {
	for (auto it = other.getMonoms().begin(); it != other.getMonoms().end(); ++it) {
		Monom neg = *it;
		neg.setCoeff(-neg.getCoeff());
		addMonom(neg);
	}
	return *this;
}

Polynom Polynom::operator/(const Polynom& other) {
	throw std::logic_error("Polynomial division is not implemented");
}

Polynom& Polynom::operator/=(const Polynom& other) {
	throw std::logic_error("Polynomial division is not implemented");
}

Polynom Polynom::operator*(double k) const {
	Polynom result;
	for (auto it = this->getMonoms().begin(); it != this->getMonoms().end(); ++it) {
		Monom m = *it;
		m.setCoeff(m.getCoeff() * k);
		result.addMonom(m);
	}
	return result;
}

Polynom& Polynom::operator*=(double k) {
	Polynom temp;
	for (auto it = this->getMonoms().begin(); it != this->getMonoms().end(); ++it) {
		Monom m = *it;
		m.setCoeff(m.getCoeff() * k);
		temp.addMonom(m);
	}
	*this = temp;
	return *this;
}

Polynom Polynom::operator/(double k) const {
	if (k == 0) throw std::logic_error("Division by zero");
	Polynom result;
	for (auto it = this->getMonoms().begin(); it != this->getMonoms().end(); ++it) {
		Monom m = *it;
		m.setCoeff(m.getCoeff() / k);
		result.addMonom(m);
	}
	return result;
}

Polynom& Polynom::operator/=(double k) {
	if (k == 0) throw std::logic_error("Division by zero");
	Polynom temp;
	for (auto it = this->getMonoms().begin(); it != this->getMonoms().end(); ++it) {
		Monom m = *it;
		m.setCoeff(m.getCoeff() / k);
		temp.addMonom(m);
	}
	*this = temp;
	return *this;
}

double Polynom::value(double x, double y, double z) const {
	double result = 0.0;
	for (auto it = this->getMonoms().begin(); it != this->getMonoms().end(); ++it) {
		result += it->value(x, y, z);
	}
	return result;
}

std::ostream& operator<<(std::ostream& os, const Polynom& p) {
	if (p.monoms.empty()) {
		os << "0";
		return os;
	}

	bool first = true;
	for (auto it = p.monoms.begin(); it != p.monoms.end(); ++it) {
		if (it->getCoeff() > 0 && !first) {
			os << " + ";
		}
		else if (it->getCoeff() < 0) {
			os << " - ";
		}
		else if (first && it->getCoeff() > 0) {
		}

		if (std::abs(it->getCoeff()) != 1.0 ||
			(it->getDegX() == 0 && it->getDegY() == 0 && it->getDegZ() == 0)) {
			os << std::abs(it->getCoeff());
		}
		else if (std::abs(it->getCoeff()) == 1.0 &&
			(it->getDegX() == 0 && it->getDegY() == 0 && it->getDegZ() == 0)) {
			os << std::abs(it->getCoeff());
		}

		if (it->getDegX() > 0) {
			os << "x";
			if (it->getDegX() > 1) os << "^" << it->getDegX();
		}
		if (it->getDegY() > 0) {
			os << "y";
			if (it->getDegY() > 1) os << "^" << it->getDegY();
		}
		if (it->getDegZ() > 0) {
			os << "z";
			if (it->getDegZ() > 1) os << "^" << it->getDegZ();
		}

		first = false;
	}
	return os;
}

std::istream& operator>>(std::istream& is, Polynom& p) {
	std::string str;
	std::getline(is, str);
	p = Polynom(str);
	return is;
}