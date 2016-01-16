#pragma once
#include "definitions.h"

class PolynomialMap
{
public:
	std::map<int, int>m;

	explicit PolynomialMap();
	explicit PolynomialMap(int value);

	void Set(string s);
	void Clear();
	bool IsZero() const;
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
	PolynomialMap operator ^ (int power);
	PolynomialMap operator += (PolynomialMap p2);
	PolynomialMap operator -= (PolynomialMap p2);
	PolynomialMap operator *= (PolynomialMap p2);
	PolynomialMap operator /= (PolynomialMap p2);
	PolynomialMap operator ^= (int power);
	void Print(string name) const;
};
