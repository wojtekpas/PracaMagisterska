#pragma once
#include "definitions.h"
#include "StringManager.h"
#include "CharsConstants.h"

class PolynomialMap
{
public:
	std::map<int, int>m;

	explicit PolynomialMap();
	explicit PolynomialMap(int value);

	bool Set(string s);
	void Clear();
	bool IsZero();
	int Size();
	int Value(int power);
	bool ValueEquals(int power, PolynomialMap p2);
	void SetValue(int power, int value);
	void Add(int power, int value);
	void Sub(int power, int value);
	void Mul(int power1, int value1, int power2, int value2);

	bool operator==(PolynomialMap p2);
	bool operator!=(PolynomialMap p2);
	PolynomialMap operator = (PolynomialMap p2);
	PolynomialMap operator + (PolynomialMap p2);
	PolynomialMap operator - (PolynomialMap p2);
	PolynomialMap operator * (PolynomialMap p2);
	PolynomialMap operator / (PolynomialMap p2);
	PolynomialMap operator ^ (int power);
	PolynomialMap operator += (PolynomialMap p2);
	PolynomialMap operator -= (PolynomialMap p2);
	PolynomialMap operator *= (PolynomialMap p2);
	PolynomialMap operator /= (PolynomialMap p2);
	PolynomialMap operator ^= (int power);
	void Print(string name);
};


inline PolynomialMap::PolynomialMap()
{
}

inline PolynomialMap::PolynomialMap(int value)
{
	if (value != 0)
		m.insert(pair<int, int>(0, value));
}

inline bool PolynomialMap::Set(string s)
{
	Clear();

	if (StringManager::IsEmptyString(s))
		return false;

	if (CharsConstants::IsVar(s[0]))
	{
		if (s.length() > 1)
			return false;
		else
		{
			m.insert(pair<int, int>(1, 1));
			return true;
		}
	}

	int value = CharsConstants::CharToInt(s[0]);

	for (int i = 1; i < s.length(); i++)
	{
		value *= 10;
		value = value + CharsConstants::CharToInt(s[0]);
	}

	m.insert(pair<int, int>(0, value));
	return true;
}

inline void PolynomialMap::Clear()
{
	m.clear();
}

inline bool PolynomialMap::IsZero()
{
	return Size() == 0;
}

inline int PolynomialMap::Size()
{
	return m.size();
}

inline int PolynomialMap::Value(int power)
{
	if (m.count(power))
		return m.at(power);
	return 0;
}

inline bool PolynomialMap::ValueEquals(int power, PolynomialMap p2)
{
	return Value(power) == p2.Value(power);
}

inline void PolynomialMap::SetValue(int power, int value)
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

inline void PolynomialMap::Add(int power, int value)
{
	SetValue(power, Value(power) + value);
}

inline void PolynomialMap::Sub(int power, int value)
{
	return Add(power, -value);
}

inline void PolynomialMap::Mul(int power1, int value1, int power2, int value2)
{
	Add(power1 + power2, value1 * value2);
}

inline bool PolynomialMap::operator == (PolynomialMap p2)
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

inline bool PolynomialMap::operator != (PolynomialMap p2)
{
	return !(*this == p2);
}

inline PolynomialMap PolynomialMap::operator = (PolynomialMap p2)
{
	m = p2.m;
	return *this;
}

inline PolynomialMap PolynomialMap::operator + (PolynomialMap p2)
{
	PolynomialMap result;

	result.m = m;

	for (auto pair1 : p2.m)
	{
		result.Add(pair1.first, pair1.second);
	}

	return result;
}

inline PolynomialMap PolynomialMap::operator - (PolynomialMap p2)
{
	PolynomialMap result;

	result.m = m;

	for (auto pair1 : p2.m)
	{
		result.Sub(pair1.first, pair1.second);
	}

	return result;
}

inline PolynomialMap PolynomialMap::operator * (PolynomialMap p2)
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

inline PolynomialMap PolynomialMap::operator / (PolynomialMap p2)
{
	return *this;
}

inline PolynomialMap PolynomialMap::operator ^ (int power)
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

inline PolynomialMap PolynomialMap::operator += (PolynomialMap p2)
{
	*this = *this + p2;
	return *this;
}

inline PolynomialMap PolynomialMap::operator -= (PolynomialMap p2)
{
	*this = *this - p2;
	return *this;
}

inline PolynomialMap PolynomialMap::operator *= (PolynomialMap p2)
{
	*this = *this * p2;
	return *this;
}

inline PolynomialMap PolynomialMap::operator /= (PolynomialMap p2)
{
	*this = *this / p2;
	return *this;
}

inline PolynomialMap PolynomialMap::operator ^= (int power)
{
	*this = *this ^ power;
	return *this;
}

inline void PolynomialMap::Print(string name)
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

