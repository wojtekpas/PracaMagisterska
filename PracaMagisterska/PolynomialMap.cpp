#pragma once
#include "PolynomialMap.h"

PolynomialMap::PolynomialMap(int count = 0)
{
	for (int i = 1; i <= count; i++)
	{
		a.insert(pair<int, int>(i, 10*i));
	}
}

int PolynomialMap::Size() const
{
	return a.size();
}

int PolynomialMap::Value(int power)
{
	if (a.count(power))
		return a.at(power);
	return 0;
}

bool PolynomialMap::ValueEquals(int power, PolynomialMap p2)
{
	return Value(power) == p2.Value(power);
}

void PolynomialMap::SetValue(int power, int value)
{
	if (a.count(power))
		a.at(power) = value;
	else
		a.insert(pair<int, int>(power, value));
}

void PolynomialMap::Add(int power, int value)
{
	SetValue(power, Value(power) + value);
}

void PolynomialMap::Sub(int power, int value)
{
	return Add(power, -value);
}

bool PolynomialMap::operator == (PolynomialMap p2)
{
	for(auto pair1 : a)
	{
		if (ValueEquals(pair1.first, p2) == false)
			return false;
	}

	for (auto pair1 : p2.a)
	{
		if (ValueEquals(pair1.first, p2) == false)
			return false;
	}

	return true;
}

bool PolynomialMap::operator != (PolynomialMap p2)
{
	return !(*this == p2);
}

PolynomialMap PolynomialMap::operator + (PolynomialMap p2) const
{
	PolynomialMap result;
	
	result.a = a;

	for (auto pair1 : p2.a)
	{
		result.Add(pair1.first, pair1.second);
	}

	return result;
}

PolynomialMap PolynomialMap::operator - (PolynomialMap p2) const
{
	PolynomialMap result;

	result.a = a;

	for (auto pair1 : p2.a)
	{
		result.Sub(pair1.first, pair1.second);
	}

	return result;
}

PolynomialMap PolynomialMap::operator * (PolynomialMap p2)
{
	return p2;
}

PolynomialMap PolynomialMap::operator / (PolynomialMap p2)
{
	return p2;
}

PolynomialMap PolynomialMap::operator += (PolynomialMap p2) const
{
	return *this + p2;
}

PolynomialMap PolynomialMap::operator -= (PolynomialMap p2) const
{
	return *this - p2;
}

PolynomialMap PolynomialMap::operator *= (PolynomialMap p2)
{
	return *this * p2;
}

PolynomialMap PolynomialMap::operator /= (PolynomialMap p2)
{
	return *this / p2;
}

void PolynomialMap::Print(string name) const
{
	cout << "  " << name << endl;

	int it = 0;
		
	for (auto pair1 : a)
	{		
		printf("#%d = (%d, %d)\n", it++, pair1.first, pair1.second);		
	}
}



