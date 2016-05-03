#pragma once
#include "Polynomial.h"

class PolynomialMap: public Polynomial
{	
public:
	vector<PolynomialMap> sturm;

	explicit PolynomialMap();
	explicit PolynomialMap(Number number);
	int Size() override;
	void Clear() override;
	bool IsZero() override;
	Polynomial& CreatePolynomial() override;
	Polynomial& CreatePolynomial(Number number) override;
	int PolynomialDegree() override;
	Number Value(int power) override;
	void SetNumberValue(int power, Number number) override;
	map<int, Number> ValuesExceptValueOfPolynomialDegree(int degree) override;
	int NumberOfChangesSign(Number a) override;
	string ToString() override;

	bool operator==(Polynomial& p2) override;
	Polynomial& operator = (Polynomial& p2) override;
	Polynomial& operator + (Polynomial& p2) override;
	Polynomial& operator - (Polynomial& p2) override;
	Polynomial& operator * (Polynomial& p2) override;
	Polynomial& operator / (Polynomial& p2) override;
	Polynomial& operator % (Polynomial& p2) override;
	
	vector<PolynomialMap> GetSturm();
};

inline PolynomialMap ConvertFromPolynomialRef(Polynomial& ref)
{
	PolynomialMap p;
	p.m = ref.m;
	p.isNew = ref.isNew;
	return p;
}

inline Polynomial& CreatePolynomial()
{
	PolynomialMap* polynomialMap = new PolynomialMap();
	return *polynomialMap;
}

inline Polynomial& CreatePolynomial(Number number)
{
	PolynomialMap* polynomialMap = new PolynomialMap(number);
	return *polynomialMap;
}

inline Polynomial& PolynomialMap::CreatePolynomial()
{
	PolynomialMap* polynomialMap = new PolynomialMap();
	return *polynomialMap;
}

inline Polynomial& PolynomialMap::CreatePolynomial(Number number)
{
	PolynomialMap* polynomialMap = new PolynomialMap(number);
	return *polynomialMap;
}


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

inline void PolynomialMap::SetNumberValue(int power, Number number)
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
	Polynomial& newPolynomial = CreatePolynomial();
	newPolynomial.m = p2.m;
	newPolynomial.id = p2.id * 10;
	m = p2.m;
	id = p2.id * 11;
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

inline int PolynomialMap::NumberOfChangesSign(Number a)
{
	sturm = GetSturm();
	int counter = 0;
	int lastValue = 0;
	int curValue;
	Number number = PolynomialValue(a);
	if (number > 0)
		lastValue = 1;
	else if (number < 0)
		lastValue = -1;

	for (int i = 1; i < sturm.size(); i++)
	{
		number = sturm.at(i).PolynomialValue(a);
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

inline vector<PolynomialMap> PolynomialMap::GetSturm()
{
	if (sturm.size())
		return sturm;
	sturm.push_back(*this);
	Polynomial& derivative = Derivative();
	if (derivative.IsZero())
		return sturm;
	sturm.push_back(ConvertFromPolynomialRef(derivative));
	Polynomial& w = *this;
	Polynomial& q = derivative;
	Polynomial& r = w % q;

	while (r.IsZero() == false)
	{
		r = r.NegativePolynomial();
		sturm.push_back(ConvertFromPolynomialRef(r));
		w = q;
		q = r;
		r = w % q;
	}
	return sturm;
}