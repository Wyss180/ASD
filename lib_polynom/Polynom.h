#pragma once
#include <iostream>
#include <stdexcept>
#include <cmath>
#include "../lib_monom/Monom.h"
#include "../lib_doubly_linked_list/doubly_linked_list.h"

class Polynom {
private:
	DList<Monom> monoms;
public:
	Polynom();
	Polynom(const Polynom& other);
	Polynom(const std::string& str);
	~Polynom();
	
	Polynom& operator=(const Polynom& other);
	
	void addMonom(const Monom& m);
	Polynom operator+(const Polynom& other);
	Polynom operator-(const Polynom& other);
	Polynom operator*(const Polynom& other);
	Polynom operator/(const Polynom& other);
	Polynom& operator+=(const Polynom& other);
	Polynom& operator-=(const Polynom& other);
	Polynom& operator*=(const Polynom& other);
	Polynom& operator/=(const Polynom& other);
	Polynom operator*(double k) const;
	Polynom operator/(double k) const;
	Polynom& operator*=(double k);
	Polynom& operator/=(double k);
	double value(double x, double y, double z) const;
	const DList<Monom>& getMonoms() const { return monoms; }
	friend std::ostream& operator<<(std::ostream& os, const Polynom& p);
	friend std::istream& operator>>(std::istream& is, Polynom& p);
	bool isEmpty() const { return monoms.empty(); }
	int size() const { return monoms.size(); }
};