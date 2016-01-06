#pragma once
#include "definitions.h"

class PolynomialMap
{
public:
	map<int, int>a;

	PolynomialMap(int count);

	int Size() const;
	int Value(int power);
	bool ValueEquals(int power, PolynomialMap p2);
	void SetValue(int power, int value);
	void Add(int power, int value);
	void Sub(int power, int value);

	bool operator==(PolynomialMap p2);
	bool operator!=(PolynomialMap p2);
	PolynomialMap operator + (PolynomialMap p2) const;
	PolynomialMap operator - (PolynomialMap p2) const;
	PolynomialMap operator * (PolynomialMap p2);
	PolynomialMap operator / (PolynomialMap p2);
	PolynomialMap operator += (PolynomialMap p2) const;
	PolynomialMap operator -= (PolynomialMap p2) const;
	PolynomialMap operator *= (PolynomialMap p2);
	PolynomialMap operator /= (PolynomialMap p2);
	void Print(string name) const;
};

