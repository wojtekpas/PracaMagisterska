#pragma once
#include "definitions.h"

class Polynomial
{
public:
	virtual int Size() = 0;
	virtual int ValueForPower(int power) = 0;
	virtual pair<int, int> Add(int power, int value) = 0;
	virtual pair<int, int> Sub(int power, int value) = 0;

	virtual Polynomial* operator = (Polynomial* p2) { return NULL; }
	virtual bool operator == (Polynomial* p2) = 0;
	virtual bool operator != (Polynomial* p2) = 0;
	virtual Polynomial* operator + (Polynomial* p2) { return NULL; }
	virtual Polynomial* operator - (Polynomial* p2) { return NULL; }
	virtual Polynomial* operator * (Polynomial* p2) { return NULL; }
	virtual Polynomial* operator / (Polynomial* p2) { return NULL; }
	virtual Polynomial* operator += (Polynomial* p2) { return NULL; }
	virtual Polynomial* operator -= (Polynomial* p2) { return NULL; }
	virtual Polynomial* operator *= (Polynomial* p2) { return NULL; }
	virtual Polynomial* operator /= (Polynomial* p2) { return NULL; }
	virtual void Print(string name) = 0;

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

