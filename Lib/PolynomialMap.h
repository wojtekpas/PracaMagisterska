#pragma once
#include "definitions.h"
#include "StringManager.h"
#include "CharsConstants.h"

class PolynomialMap
{
public:
	map<int, int>m;

	explicit PolynomialMap();
	explicit PolynomialMap(int value);

	bool Set(string s);
	void Clear();
	bool IsNew();
	bool IsZero();
	int Size();
	int PolynomialDegree();
	pair<int, int> ValueOfPolynomialDegree();
	map<int, int> ValuesExceptValueOfPolynomialDegree(int degree);
	int Value(int power);
	bool ValueEquals(int power, PolynomialMap p2);
	void SetValue(int power, int value);
	void Add(int power, int value);
	void Sub(int power, int value);
	static pair<int, int> Mul(int power1, int value1, int power2, int value2);
	static pair<pair<int, int>, pair<int, int>> Div(int power1, int value1, int power2, int value2);

	PolynomialMap Derivative();
	PolynomialMap Nwd(PolynomialMap p2);
	PolynomialMap PolynomialAfterEliminationOfMultipleRoots();
	pair <PolynomialMap, PolynomialMap> DividePolynomials(PolynomialMap p1, PolynomialMap p2);

	bool operator==(PolynomialMap p2);
	bool operator!=(PolynomialMap p2);
	PolynomialMap operator = (PolynomialMap p2);
	PolynomialMap operator + (PolynomialMap p2);
	PolynomialMap operator - (PolynomialMap p2);
	PolynomialMap operator * (PolynomialMap p2);
	PolynomialMap operator / (PolynomialMap p2);
	PolynomialMap operator % (PolynomialMap p2);
	PolynomialMap operator ^ (int power);
	PolynomialMap operator += (PolynomialMap p2);
	PolynomialMap operator -= (PolynomialMap p2);
	PolynomialMap operator *= (PolynomialMap p2);
	PolynomialMap operator /= (PolynomialMap p2);
	PolynomialMap operator %= (PolynomialMap p2);
	PolynomialMap operator ^= (int power);
	string ToString();
	void Print(string name);

protected:
	bool isNew = true;
};

inline PolynomialMap::PolynomialMap()
{
}

inline PolynomialMap::PolynomialMap(int value)
{
	isNew = false;
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
			
		SetValue(1, 1);
		return true;
	}

	int value = CharsConstants::CharToInt(s[0]);

	for (int i = 1; i < s.length(); i++)
	{
		value *= 10;
		value = value + CharsConstants::CharToInt(s[i]);
	}

	if(value)
		SetValue(0, value);
	return true;
}

inline void PolynomialMap::Clear()
{
	m.clear();
	isNew = true;
}

inline bool PolynomialMap::IsNew()
{
	return isNew;
}

inline bool PolynomialMap::IsZero()
{
	return Size() == 0;
}

inline int PolynomialMap::Size()
{
	return m.size();
}

inline int PolynomialMap::PolynomialDegree()
{
	int max = -1;

	for (auto pair1 : m)
	{
		if (pair1.first > max)
			max = pair1.first;
	}
	return max;
}

inline pair<int, int> PolynomialMap::ValueOfPolynomialDegree()
{
	int polynomialDegree = PolynomialDegree();

	return pair<int, int>(polynomialDegree, Value(polynomialDegree));
}

inline map<int, int> PolynomialMap::ValuesExceptValueOfPolynomialDegree(int degree = -1)
{
	map <int, int> result;
	int polynomialDegree = degree;

	if (degree == -1)
		polynomialDegree = PolynomialDegree();

	for (auto pair1 : m)
	{
		if (pair1.first != polynomialDegree)
			result.insert(pair1);
	}
	return result;
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
	isNew = false;
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

inline pair<int, int> PolynomialMap::Mul(int power1, int value1, int power2, int value2)
{
	return pair<int, int>(power1 + power2, value1 * value2);
	//Add(power1 + power2, value1 * value2);
}

inline pair<pair<int, int>, pair<int, int>> PolynomialMap::Div(int power1, int value1, int power2, int value2)
{
	pair<int, int> result = pair<int, int>(power1 - power2, value1 / value2);
	pair<int, int> rest = pair<int, int>(power1, value1 % result.second);

	return pair<pair<int, int>, pair<int, int>>(result, rest);
	//Add(power1 - power2, value1 / value2);
}

inline PolynomialMap PolynomialMap::Derivative()
{
	PolynomialMap result;

	for (auto p: m)
	{
		if (p.first > 0)
			result.SetValue(p.first - 1, p.first * p.second);
	}
	return result;
}

inline PolynomialMap PolynomialMap::Nwd(PolynomialMap p2)
{
	pair<PolynomialMap, PolynomialMap> divResult = DividePolynomials(*this, p2);
	return divResult.second;
}

inline PolynomialMap PolynomialMap::PolynomialAfterEliminationOfMultipleRoots()
{
	PolynomialMap nwd = Nwd(Derivative());
	pair<PolynomialMap, PolynomialMap> divResult = DividePolynomials(*this, nwd);
	return divResult.first;
}

inline pair<PolynomialMap, PolynomialMap> PolynomialMap::DividePolynomials(PolynomialMap p1, PolynomialMap p2)
{
	PolynomialMap result;

	if (IsZero() || p2.IsZero())
		return pair<PolynomialMap, PolynomialMap>(result, result);

	PolynomialMap current = p1;
	int currentDegree = current.PolynomialDegree();
	int degree = p2.PolynomialDegree();
	pair <int, int> pair2 = pair<int, int>(degree, p2.Value(degree));
	map <int, int> map2 = ValuesExceptValueOfPolynomialDegree(degree);

	while (currentDegree > degree)
	{
		pair <int, int> pair1 = pair<int, int>(currentDegree, current.Value(currentDegree));
		map <int, int> map1 = ValuesExceptValueOfPolynomialDegree(currentDegree);

		auto divResult = Div(pair1.first, pair1.second, pair2.first, pair2.second).first;

		result.SetValue(divResult.first, divResult.second);

		if (divResult.second != 0)
		{
			current.SetValue(currentDegree, 0);
			for (auto curPair : map1)
			{
				auto mulResult = result.Mul(curPair.first, curPair.second, pair2.first, pair2.second);
				current.Sub(mulResult.first, mulResult.second);
			}
		}

		current = *this - p2;
		currentDegree = current.PolynomialDegree();
	}
	return pair<PolynomialMap, PolynomialMap>(result, current);
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

	if (p2.IsZero())
		return result;

	for (auto pair1 : m)
	{
		for (auto pair2 : p2.m)
		{
			auto mulResult = result.Mul(pair1.first, pair1.second, pair2.first, pair2.second);
			result.Add(mulResult.first, mulResult.second);
		}
	}

	return result;
}

inline PolynomialMap PolynomialMap::operator / (PolynomialMap p2)
{
	pair <PolynomialMap, PolynomialMap> divResult = DividePolynomials(*this, p2);
	return divResult.first;
}

inline PolynomialMap PolynomialMap::operator % (PolynomialMap p2)
{
	pair <PolynomialMap, PolynomialMap> divResult = DividePolynomials(*this, p2);
	return divResult.second;
}

inline PolynomialMap PolynomialMap::operator ^ (int power)
{
	PolynomialMap result;

	if (power == 0)
	{
		if (IsZero())
			return result;

		result.SetValue(0, 1);
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

inline PolynomialMap PolynomialMap::operator %= (PolynomialMap p2)
{
	*this = *this % p2;
	return *this;
}

inline PolynomialMap PolynomialMap::operator ^= (int power)
{
	*this = *this ^ power;
	return *this;
}

inline string PolynomialMap::ToString()
{
	if (IsZero())
	{
		return("Is Zero");
	}

	string result = StringManager::EmptyString();
	for (auto pair1 : m)
	{
		result = result + to_string(pair1.first) + ':' 
			+ to_string(pair1.second) + ',';
	}

	return StringManager::Substr(result, 0, result.length() - 2);
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

