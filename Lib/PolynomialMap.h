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


PolynomialMap::PolynomialMap()
{
}

PolynomialMap::PolynomialMap(int value)
{
	if (value != 0)
		m.insert(pair<int, int>(0, value));
}

void PolynomialMap::Set(string s)
{
	Clear();

	if (s.length() == 0)
		assert("empty string");

	if (s[0] == 'a')
	{
		if (s.length() > 1)
			assert("ambigous variable");
		else
		{
			m.insert(pair<int, int>(1, 1));
			return;
		}
	}

	int value = s[0] - '0';

	for (int i = 1; i < s.length(); i++)
	{
		value *= 10;
		value = value + s[i] - '0';
	}

	m.insert(pair<int, int>(0, value));
}

void PolynomialMap::Clear()
{
	m.clear();
}

bool PolynomialMap::IsZero() const
{
	return Size() == 0;
}

int PolynomialMap::Size() const
{
	return m.size();
}

int PolynomialMap::Value(int power)
{
	if (m.count(power))
		return m.at(power);
	return 0;
}

bool PolynomialMap::ValueEquals(int power, PolynomialMap p2)
{
	return Value(power) == p2.Value(power);
}

void PolynomialMap::SetValue(int power, int value)
{
	if (value == 0)
	{
		if (m.count(power))
			m.erase(power);
		return;
	}

	if (m.count(power))
		m.at(power) = value;
	else
		m.insert(pair<int, int>(power, value));
}

void PolynomialMap::Add(int power, int value)
{
	SetValue(power, Value(power) + value);
}

void PolynomialMap::Sub(int power, int value)
{
	return Add(power, -value);
}

void PolynomialMap::Mul(int power1, int value1, int power2, int value2)
{
	Add(power1 + power2, value1 * value2);
}

bool PolynomialMap::operator == (PolynomialMap p2)
{
	for (auto pair1 : m)
	{
		if (ValueEquals(pair1.first, p2) == false)
			return false;
	}

	for (auto pair1 : p2.m)
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

PolynomialMap PolynomialMap::operator = (PolynomialMap p2)
{
	m = p2.m;
	return *this;
}

PolynomialMap PolynomialMap::operator + (PolynomialMap p2) const
{
	PolynomialMap result;

	result.m = m;

	for (auto pair1 : p2.m)
	{
		result.Add(pair1.first, pair1.second);
	}

	return result;
}

PolynomialMap PolynomialMap::operator - (PolynomialMap p2) const
{
	PolynomialMap result;

	result.m = m;

	for (auto pair1 : p2.m)
	{
		result.Sub(pair1.first, pair1.second);
	}

	return result;
}

PolynomialMap PolynomialMap::operator * (PolynomialMap p2) const
{
	PolynomialMap result;

	for (auto pair1 : m)
	{
		for (auto pair2 : p2.m)
		{
			result.Mul(pair1.first, pair1.second, pair2.first, pair2.second);
		}
	}

	return result;
}

PolynomialMap PolynomialMap::operator / (PolynomialMap p2)
{
	return *this;
}

PolynomialMap PolynomialMap::operator ^ (int power)
{
	PolynomialMap result;

	if (power == 0)
	{
		result.Clear();
		return result;
	}

	result = *this;

	for (int i = 1; i < power; i++)
	{
		result *= *this;
	}

	return result;
}

PolynomialMap PolynomialMap::operator += (PolynomialMap p2)
{
	*this = *this + p2;
	return *this;
}

PolynomialMap PolynomialMap::operator -= (PolynomialMap p2)
{
	*this = *this - p2;
	return *this;
}

PolynomialMap PolynomialMap::operator *= (PolynomialMap p2)
{
	*this = *this * p2;
	return *this;
}

PolynomialMap PolynomialMap::operator /= (PolynomialMap p2)
{
	*this = *this / p2;
	return *this;
}

PolynomialMap PolynomialMap::operator^=(int power)
{
	*this = *this ^ power;
	return *this;
}

void PolynomialMap::Print(string name) const
{
	printf("\t%s:\n", name.c_str());


	if (IsZero())
	{
		printf("is Zero\n");
		return;
	}

	int it = 0;

	for (auto pair1 : m)
	{
		printf("#%d = (%d, %d)\n", it++, pair1.first, pair1.second);
	}


}

