#pragma once
#include "PolynomialMap.h"

PolynomialMap::PolynomialMap(int count = 0)
{
	for (int i = 1; i < count; i++)
	{
		a.insert(pair<int, int>(i, 10*i));
	}
}

int PolynomialMap::Size()
{
	return a.size();
}

int PolynomialMap::ValueForPower(int power)
{
	return a.at(power);
}

pair<int, int> PolynomialMap::Add(int power, int value)
{
	pair<int, int> pair1;

	try
	{
		pair1 = pair<int, int>(power, ValueForPower(power));
		printf("try ok\n");
	}
	catch (exception e)
	{
		printf("catch\n");
		pair1 = pair<int, int>(power, 0);
	}

	return pair<int, int> (power, pair1.second + value);
}

pair<int, int> PolynomialMap::Sub(int power, int value)
{
	return Add(power, -value);
}

PolynomialMap* PolynomialMap::operator=(PolynomialMap* p2)
{
	a = p2->a;

	return this;
}

bool PolynomialMap::operator==(Polynomial* p2)
{
	return true;
}

bool PolynomialMap::operator!=(Polynomial* p2)
{
	return true;
}

PolynomialMap* PolynomialMap::operator + (PolynomialMap* p2)
{
	PolynomialMap* result = new PolynomialMap();
	
	result->a = a;

	for (auto pair1 : p2->a)
	{
		result->Add(pair1.first, pair1.second);
	}

	return result;
}

PolynomialMap* PolynomialMap::operator - (PolynomialMap* p2)
{
	return NULL;
}

PolynomialMap* PolynomialMap::operator * (PolynomialMap* p2)
{
	return NULL;
}

PolynomialMap* PolynomialMap::operator / (PolynomialMap* p2)
{
	return NULL;
}

PolynomialMap* PolynomialMap::operator += (PolynomialMap* p2)
{
	return *this + p2;
}

PolynomialMap* PolynomialMap::operator -= (PolynomialMap* p2)
{
	return *this - p2;
}

PolynomialMap* PolynomialMap::operator *= (PolynomialMap* p2)
{
	return *this * p2;
}

PolynomialMap* PolynomialMap::operator /= (PolynomialMap* p2)
{
	return *this / p2;
}

void PolynomialMap::Print(string name)
{
	cout << "  " << name << endl;

	int it = 0;
		
	for (auto pair1 : a)
	{		
		printf("#%d = (%d, %d)\n", it++, pair1.first, pair1.second);		
	}
}



