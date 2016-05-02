#pragma once
#include "Polynomial.h"

class PolynomialMap: Polynomial
{
	/*
public:
	explicit PolynomialMap();
	explicit PolynomialMap(Number number);
	int Size() override;
	void Clear() override;
	bool IsZero() override;
	Polynomial& CreatePolynomial() override;
	Polynomial& CreatePolynomial(Number number) override;
	int PolynomialDegree() override;
	Number Value(int power) override;
	void SetValue(int power, Number number) override;
	map<int, Number> ValuesExceptValueOfPolynomialDegree(int degree) override;
	pair <Polynomial&, Polynomial&> DividePolynomials(Polynomial& p1, Polynomial& p2) override;
	string ToString() override;

	bool operator==(Polynomial& p2) override;
	Polynomial& operator = (Polynomial& p2) override;
	Polynomial& operator + (Polynomial& p2) override;
	Polynomial& operator - (Polynomial& p2) override;
	Polynomial& operator * (Polynomial& p2) override;
	Polynomial& operator / (Polynomial& p2) override;
	Polynomial& operator % (Polynomial& p2) override;
	*/
};
/*
inline PolynomialMap::PolynomialMap() : Polynomial()
{
}

inline PolynomialMap::PolynomialMap(Number number) : Polynomial(number)
{
	if (number != 0)
		m.insert(pair<int, Number>(0, number));
}

inline int PolynomialMap::Size()
{
	return m.size();
}

inline void PolynomialMap::Clear()
{
	m.clear();
	isNew = true;
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

inline Polynomial& PolynomialMap::CreatePolynomial()
{
	PolynomialMap polynomialMap;
	return polynomialMap;
}

inline Polynomial& PolynomialMap::CreatePolynomial(Number number)
{
	PolynomialMap polynomialMap;
	return polynomialMap;
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

inline pair<Polynomial&, Polynomial&> PolynomialMap::DividePolynomials(Polynomial& p1, Polynomial& p2)
{
	Polynomial& result = CreatePolynomial();

	if (p1.IsZero() || p2.IsZero())
		return pair<Polynomial&, Polynomial&>(result, result);

	Polynomial& current = p1;
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
	return pair<Polynomial&, Polynomial&>(result, current);
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

inline bool PolynomialMap::operator == (Polynomial& p2)
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

inline Polynomial& PolynomialMap::operator = (Polynomial& p2)
{
	m = p2.m;
	return *this;
}

inline Polynomial& PolynomialMap::operator + (Polynomial& p2)
{
	Polynomial& result = CreatePolynomial();

	result.m = m;

	for (auto pair1 : p2.m)
	{
		result.Add(pair1.first, pair1.second);
	}

	return result;
}

inline Polynomial& PolynomialMap::operator - (Polynomial& p2)
{
	Polynomial& result = CreatePolynomial();

	result.m = m;

	for (auto pair1 : p2.m)
	{
		result.Sub(pair1.first, pair1.second);
	}

	return result;
}

inline Polynomial& PolynomialMap::operator * (Polynomial& p2)
{
	Polynomial& result = CreatePolynomial();

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

inline Polynomial& PolynomialMap::operator / (Polynomial& p2)
{
	auto divResult = DividePolynomials(*this, p2);
	return divResult.first;
}

inline Polynomial& PolynomialMap::operator % (Polynomial& p2)
{
	auto divResult = DividePolynomials(*this, p2);
	return divResult.second;
}
*/