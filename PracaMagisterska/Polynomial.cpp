#pragma once
#include "Polynomial.h"

int Polynomial::Size()
{
	return iPolynomial.Size();
}

int Polynomial::ValueForPower(int power)
{
	return iPolynomial.ValueForPower(power);
}

Polynomial* Polynomial::CreatePolynomial()
{
	Polynomial* newPolynomial = new Polynomial();

	return newPolynomial;
}

void Polynomial::operator=(Polynomial* p2)
{
	sp = p2->sp;
}

bool Polynomial::operator==(Polynomial* p2)
{
	
}

bool Polynomial::operator!=(Polynomial* p2)
{
}

Polynomial* Polynomial::operator+(Polynomial* p2)
{
}

Polynomial* Polynomial::operator-(Polynomial* p2)
{
}

Polynomial* Polynomial::operator*(Polynomial* p2)
{
}

Polynomial* Polynomial::operator/(Polynomial* p2)
{
}

void Polynomial::operator+=(Polynomial* p2)
{
}

void Polynomial::operator-=(Polynomial* p2)
{
}

void Polynomial::operator*=(Polynomial* p2)
{
}

void Polynomial::operator/=(Polynomial* p2)
{
}