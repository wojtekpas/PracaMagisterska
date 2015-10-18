#pragma once
#include "Polynomial.h"

class PolynomialMap :
	public Polynomial
{
public:
	map<int, int>a;

	PolynomialMap(int count);

	int Size() override;
	int ValueForPower(int power) override;
	virtual pair<int, int> Add(int power, int value) override;
	virtual pair<int, int> Sub(int power, int value) override;

	PolynomialMap* operator=(PolynomialMap* p2);
	bool operator==(Polynomial* p2) override;
	bool operator!=(Polynomial* p2) override;
	PolynomialMap* operator + (PolynomialMap* p2);
	PolynomialMap* operator - (PolynomialMap* p2);
	PolynomialMap* operator * (PolynomialMap* p2);
	PolynomialMap* operator / (PolynomialMap* p2);
	PolynomialMap* operator += (PolynomialMap* p2);
	PolynomialMap* operator -= (PolynomialMap* p2);
	PolynomialMap* operator *= (PolynomialMap* p2);
	PolynomialMap* operator /= (PolynomialMap* p2);
	void Print(string name) override;
};

