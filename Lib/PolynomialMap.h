#pragma once
#include "definitions.h"
#include "StringManager.h"
#include "CharsConstants.h"
#include "Number.h"

class PolynomialMap
{
protected:
	vector<PolynomialMap> derivatives;
	vector<PolynomialMap> sturm;
public:
	map<int, Number>m;

	explicit PolynomialMap();
	explicit PolynomialMap(Number number);

	bool Set(string s);
	void Clear();
	bool IsNew();
	bool IsZero();
	int Size();
	int PolynomialDegree();
	pair<int, Number> ValueOfPolynomialDegree();
	map<int, Number> ValuesExceptValueOfPolynomialDegree(int degree);
	Number Value(int power);
	bool ValueEquals(int power, PolynomialMap p2);
	void SetValue(int power, Number number);
	void SetValue(int power, int value);
	void Add(int power, Number number);
	void Sub(int power, Number number);
	static pair<int, Number> Mul(int power1, Number number1, int power2, Number number2);
	static pair<int, Number> Div(int power1, Number number1, int power2, Number number2);

	PolynomialMap Derivative();
	PolynomialMap Nwd(PolynomialMap p1, PolynomialMap p2);
	PolynomialMap PolynomialAfterEliminationOfMultipleRoots();
	pair <PolynomialMap, PolynomialMap> DividePolynomials(PolynomialMap p1, PolynomialMap p2);
	void Normalize();
	Number CoefficientValue(pair<int, Number> pair1, Number a);
	Number PolynomialValue(Number a);
	vector<PolynomialMap> GetDerivatives();
	int NumberOfChangesSign(Number a);
	Number NextNumberFromRange(Number a, Number b);
	int NumberOfRoots(Number a, Number b);
	vector<Number> FindRoots(Number a, Number b);

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

inline PolynomialMap::PolynomialMap(Number number)
{
	isNew = false;
	if (number != 0)
		m.insert(pair<int, Number>(0, number));
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
			
		SetValue(1, Number(1));
		return true;
	}

	Number number(CharsConstants::CharToInt(s[0]));

	for (int i = 1; i < s.length(); i++)
	{
		number *= 10;
		number = number + CharsConstants::CharToInt(s[i]);
	}

	if(number != 0)
		SetValue(0, number);
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
		if (pair1.second.Abs() > 0.0000001)
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

inline pair<int, Number> PolynomialMap::ValueOfPolynomialDegree()
{
	int polynomialDegree = PolynomialDegree();

	return pair<int, Number>(polynomialDegree, Value(polynomialDegree));
}

inline map<int, Number> PolynomialMap::ValuesExceptValueOfPolynomialDegree(int degree = -1)
{
	map<int, Number> result;
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

inline Number PolynomialMap::Value(int power)
{
	if (m.count(power))
		return m.at(power);
	return Number(0);
}

inline bool PolynomialMap::ValueEquals(int power, PolynomialMap p2)
{
	return Value(power) == p2.Value(power);
}

inline void PolynomialMap::SetValue(int power, Number number)
{
	isNew = false;
	if (number == 0)
	{
		if (m.count(power))
			m.erase(power);
		return;
	}

	if (m.count(power))
		m.at(power) = number;
	else
		m.insert(pair<int, Number>(power, number));
}

inline void PolynomialMap::SetValue(int power, int value)
{
	Number number(value);
	SetValue(power, number);
}

inline void PolynomialMap::Add(int power, Number number)
{
	SetValue(power, Value(power) + number);
}

inline void PolynomialMap::Sub(int power, Number number)
{
	return Add(power, Number(-number.GetValue()));
}

inline pair<int, Number> PolynomialMap::Mul(int power1, Number number1, int power2, Number number2)
{
	return pair<int, Number>(power1 + power2, number1 * number2);
	//Add(power1 + power2, value1 * value2);
}

inline pair<int, Number> PolynomialMap::Div(int power1, Number number1, int power2, Number number2)
{
	pair<int, Number> result = pair<int, Number>(power1 - power2, number1 / number2);

	return result;
}

inline PolynomialMap PolynomialMap::Derivative()
{
	PolynomialMap result;

	for (auto p: m)
	{
		if (p.first > 0)
			result.SetValue(p.first - 1, Number(p.first * p.second.GetValue()));
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
		one.SetValue(0, Number(1));
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
		divResult.first.SetValue(0, Number(1));
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
	pair<int, Number> pair2 = pair<int, Number>(degree, p2.Value(degree));
	map<int, Number> map2 = p2.ValuesExceptValueOfPolynomialDegree(degree);

	while (currentDegree >= degree)
	{
		pair<int, Number> pair1 = pair<int, Number>(currentDegree, current.Value(currentDegree));
		map<int, Number> map1 = current.ValuesExceptValueOfPolynomialDegree(currentDegree);

		auto divResult = Div(pair1.first, pair1.second, pair2.first, pair2.second);

		result.SetValue(divResult.first, divResult.second);

		if (divResult.second != 0)
		{
			current.SetValue(currentDegree, Number(0));
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
	Number coefficient = ValueOfPolynomialDegree().second;
	PolynomialMap divider(coefficient);
	*this /= divider;
}

inline Number PolynomialMap::CoefficientValue(pair<int, Number> pair1, Number a)
{
	Number result(1);
	for (int i = 0; i < pair1.first; i++)
		result *= a;

	return result * pair1.second;
}

inline Number PolynomialMap::PolynomialValue(Number a)
{
	if (IsZero())
		return Number(0);
	Number result(0);
	for (auto pair1 : m)
	{
		result += CoefficientValue(pair1, a);
	}
	return result;
}

inline vector<PolynomialMap> PolynomialMap::GetDerivatives()
{
	if (derivatives.size())
		return derivatives;
	PolynomialMap derivative = Derivative();
	while (derivative.IsZero() == false)
	{
		derivatives.push_back(derivative);
		derivative = derivative.Derivative();
	}
	return derivatives;
}

inline int PolynomialMap::NumberOfChangesSign(Number a)
{
	derivatives = GetDerivatives();
	int counter = 0;
	int lastValue = 0;
	int curValue;
	Number number = PolynomialValue(a);
	if (number > 0)
		lastValue = 1;
	else if (number < 0)
		lastValue = -1;

	for (int i = 1; i < derivatives.size(); i++)
	{
		number = derivatives[i].PolynomialValue(a);
		if (number > 0)
			curValue = 1;
		else if (number < 0)
			curValue = -1;
		else
			curValue = 0;

		if (lastValue * curValue < 0)
			counter++;
		if (curValue)
			lastValue = curValue;
	}
	return counter;
}

inline Number PolynomialMap::NextNumberFromRange(Number a, Number b)
{
	if (a.IsInfinity() && b.IsInfinity())
		return Number(0);
	if (a.IsInfinity())
	{
		if (b > 0)
			return Number(0);
		if (b == 0)
			return Number(-1);
		if (b == -1)
			return Number(-2);
		return Number(b * b.Abs());
	}
	if (b.IsInfinity())
	{
		if (a < 0)
			return Number(0);
		if (b == 0)
			return Number(1);
		if (b == 1)
			return Number(2);
		return Number(b * b);
	}
	return Number((a + b) / 2);
}

inline int PolynomialMap::NumberOfRoots(Number a, Number b)
{
	return NumberOfChangesSign(b) - NumberOfChangesSign(a);
}

inline vector<Number> PolynomialMap::FindRoots(Number a, Number b)
{
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

		result.SetValue(0, Number(1));
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
		if (pair1.second.Abs() > 0.0000001)
		result = result + to_string(pair1.first) + ':' 
			+ to_string(pair1.second.GetValue()) + ',';
	}

	return StringManager::Substr(result, 0, result.length() - 2);
}

inline void PolynomialMap::Print(string name)
{
	printf("\t%s:\n", name.c_str());
	cout << ToString() << endl;
}

