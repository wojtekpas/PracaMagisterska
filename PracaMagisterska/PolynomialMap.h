#pragma once
#include "definitions.h"
#include <map>

class PolynomialMap
{
public:
	std::map<int, int>m;

	explicit PolynomialMap(int count);

	int Size() const;
	int Value(int power);
	bool ValueEquals(int power, PolynomialMap p2);
	void SetValue(int power, int value);
	void Add(int power, int value);
	void Sub(int power, int value);
	void Mul(int power1, int value1, int power2, int value2);

	bool operator==(PolynomialMap p2);
	bool operator!=(PolynomialMap p2);
	PolynomialMap operator = (PolynomialMap p2);
	PolynomialMap operator + (PolynomialMap p2) const;
	PolynomialMap operator - (PolynomialMap p2) const;
	PolynomialMap operator * (PolynomialMap p2) const;
	PolynomialMap operator / (PolynomialMap p2);
	PolynomialMap operator += (PolynomialMap p2);
	PolynomialMap operator -= (PolynomialMap p2);
	PolynomialMap operator *= (PolynomialMap p2);
	PolynomialMap operator /= (PolynomialMap p2);
	void Print(string name) const;
};

