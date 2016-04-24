#pragma once
#include "definitions.h"
#include "StringManager.h"
#include "CharsConstants.h"

#define NUMBER double

class PolynomialMap
{
public:
	map<int, NUMBER>m;

	explicit PolynomialMap();
	explicit PolynomialMap(NUMBER value);

	bool Set(string s);
	void Clear();
	bool IsNew();
	bool IsZero();
	int Size();
	int PolynomialDegree();
	pair<int, NUMBER> ValueOfPolynomialDegree();
	map<int, NUMBER> ValuesExceptValueOfPolynomialDegree(int degree);
	NUMBER Value(int power);
	bool ValueEquals(int power, PolynomialMap p2);
	void SetValue(int power, NUMBER value);
	void Add(int power, NUMBER value);
	void Sub(int power, NUMBER value);
	static pair<int, NUMBER> Mul(int power1, NUMBER value1, int power2, NUMBER value2);
	static pair<int, NUMBER> Div(int power1, NUMBER value1, int power2, NUMBER value2);

	PolynomialMap Derivative();
	PolynomialMap Nwd(PolynomialMap p1, PolynomialMap p2);
	PolynomialMap PolynomialAfterEliminationOfMultipleRoots();
	pair <PolynomialMap, PolynomialMap> DividePolynomials(PolynomialMap p1, PolynomialMap p2);
	void Normalize();
	NUMBER CoefficientValue(pair<int, NUMBER> pair1, NUMBER a);
	NUMBER PolynomialValue(NUMBER a);

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

inline PolynomialMap::PolynomialMap(NUMBER value)
{
	isNew = false;
	if (value != 0)
		m.insert(pair<int, NUMBER>(0, value));
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

	NUMBER value = CharsConstants::CharToInt(s[0]);

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
	if (Size() == 0)
		return true;
	for (auto pair1 : m)
	{
		if (abs(pair1.second) > 0.0000001)
			return false;
	}
	return true;
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

inline pair<int, NUMBER> PolynomialMap::ValueOfPolynomialDegree()
{
	int polynomialDegree = PolynomialDegree();

	return pair<int, NUMBER>(polynomialDegree, Value(polynomialDegree));
}

inline map<int, NUMBER> PolynomialMap::ValuesExceptValueOfPolynomialDegree(int degree = -1)
{
	map<int, NUMBER> result;
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

inline NUMBER PolynomialMap::Value(int power)
{
	if (m.count(power))
		return m.at(power);
	return 0;
}

inline bool PolynomialMap::ValueEquals(int power, PolynomialMap p2)
{
	return Value(power) == p2.Value(power);
}

inline void PolynomialMap::SetValue(int power, NUMBER value)
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
		m.insert(pair<int, NUMBER>(power, value));
}

inline void PolynomialMap::Add(int power, NUMBER value)
{
	SetValue(power, Value(power) + value);
}

inline void PolynomialMap::Sub(int power, NUMBER value)
{
	return Add(power, -value);
}

inline pair<int, NUMBER> PolynomialMap::Mul(int power1, NUMBER value1, int power2, NUMBER value2)
{
	return pair<int, NUMBER>(power1 + power2, value1 * value2);
	//Add(power1 + power2, value1 * value2);
}

inline pair<int, NUMBER> PolynomialMap::Div(int power1, NUMBER value1, int power2, NUMBER value2)
{
	pair<int, NUMBER> result = pair<int, NUMBER>(power1 - power2, value1 / value2);

	return result;
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

inline PolynomialMap PolynomialMap::Nwd(PolynomialMap p1, PolynomialMap p2)
{
	pair<PolynomialMap, PolynomialMap> divResult = DividePolynomials(p1, p2);
	if (divResult.second.IsZero())
		return p2;
	if (divResult.second.PolynomialDegree() == 0)
	{
		PolynomialMap one;
		one.SetValue(0, 1);
		return one;
	}
	return Nwd(p2, divResult.second);
}

inline PolynomialMap PolynomialMap::PolynomialAfterEliminationOfMultipleRoots()
{
	PolynomialMap derivative = Derivative();
	derivative.Normalize();
	PolynomialMap nwd = Nwd(*this, derivative);
	PolynomialMap normalizeNwd = nwd;
	normalizeNwd.Normalize();
	pair<PolynomialMap, PolynomialMap> divResult = DividePolynomials(*this, nwd);
	if (divResult.first.IsZero())
		divResult.first.SetValue(0, 1);
	return divResult.first;
}

inline pair<PolynomialMap, PolynomialMap> PolynomialMap::DividePolynomials(PolynomialMap p1, PolynomialMap p2)
{
	PolynomialMap result;

	if (p1.IsZero() || p2.IsZero())
		return pair<PolynomialMap, PolynomialMap>(result, result);

	PolynomialMap current = p1;
	int currentDegree = current.PolynomialDegree();
	int degree = p2.PolynomialDegree();
	pair<int, NUMBER> pair2 = pair<int, NUMBER>(degree, p2.Value(degree));
	map<int, NUMBER> map2 = p2.ValuesExceptValueOfPolynomialDegree(degree);

	while (currentDegree >= degree)
	{
		pair<int, NUMBER> pair1 = pair<int, NUMBER>(currentDegree, current.Value(currentDegree));
		map<int, NUMBER> map1 = current.ValuesExceptValueOfPolynomialDegree(currentDegree);

		auto divResult = Div(pair1.first, pair1.second, pair2.first, pair2.second);

		result.SetValue(divResult.first, divResult.second);

		if (divResult.second != 0)
		{
			current.SetValue(currentDegree, 0);
			for (auto curPair : map2)
			{
				auto mulResult = Mul(curPair.first, curPair.second, divResult.first, divResult.second);
				current.Sub(mulResult.first, mulResult.second);
			}
		}
		else
		{
			break;
		}
		currentDegree = current.PolynomialDegree();
	}
	return pair<PolynomialMap, PolynomialMap>(result, current);
}

inline void PolynomialMap::Normalize()
{
	NUMBER coefficient = ValueOfPolynomialDegree().second;
	PolynomialMap divider(coefficient);
	*this /= divider;
}

inline NUMBER PolynomialMap::CoefficientValue(pair<int, NUMBER> pair1, NUMBER a)
{
	NUMBER result = 1;
	for (int i = 0; i < pair1.first; i++)
		result *= a;

	return result * pair1.second;
}

inline NUMBER PolynomialMap::PolynomialValue(NUMBER a)
{
	if (IsZero())
		return 0;
	NUMBER result = 0;
	for (auto pair1 : m)
	{
		result += CoefficientValue(pair1, a);
	}
	return result;
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
		if (abs(pair1.second) > 0.0000001)
		result = result + to_string(pair1.first) + ':' 
			+ to_string(pair1.second) + ',';
	}

	return StringManager::Substr(result, 0, result.length() - 2);
}

inline void PolynomialMap::Print(string name)
{
	printf("\t%s:\n", name.c_str());
	cout << ToString() << endl;
}

