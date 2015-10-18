#pragma once
#include "IPolynomial.h"

class Polynomial: IPolynomial
{
	StructPolynomial sp;
	IPolynomial iPolynomial;

public:
	int Size() override;
	int ValueForPower(int power) override;
	static Polynomial* CreatePolynomial();

	void operator=(Polynomial* p2);
	bool operator==(Polynomial* p2);
	bool operator!=(Polynomial* p2);
	Polynomial* operator+(Polynomial* p2);
	Polynomial* operator-(Polynomial* p2);
	Polynomial* operator*(Polynomial* p2);
	Polynomial* operator/(Polynomial* p2);
	void operator+=(Polynomial* p2);
	void operator-=(Polynomial* p2);
	void operator*=(Polynomial* p2);
	void operator/=(Polynomial* p2);

/*	void operator=(Polynomial p2);
	bool operator==(Polynomial p2);
	bool operator!=(Polynomial p2);
	Polynomial operator+(Polynomial p2);
	Polynomial operator-(Polynomial p2);
	Polynomial operator*(Polynomial p2);
	Polynomial operator/(Polynomial p2);
	void operator+=(Polynomial p2);
	void operator-=(Polynomial p2);
	void operator*=(Polynomial p2);
	void operator/=(Polynomial p2);*/

};

