#pragma once
#include "Polynomial.h"

class PolynomialVector: public Polynomial
{	
public:
	vector<PolynomialVector> sturm;

	explicit PolynomialVector();
	explicit PolynomialVector(Number number);
	Polynomial& CreatePolynomial() override;
	Polynomial& CreatePolynomial(Number number) override;
	void Clear() override;
	bool IsZero() override;
	int Size() override;
	int PolynomialDegree() override;
	Number Value(int power) override;
	void SetNumberValue(int power, Number number) override;
	map<int, Number> ValuesExceptValueOfPolynomialDegree(int degree) override;
	int NumberOfChangesSign(Number a) override;
	Polynomial& NegativePolynomial() override;
	Polynomial& Derivative() override;
	Number PolynomialValue(Number a) override;
	string ToString() override;

	bool operator==(Polynomial& p2) override;
	Polynomial& operator = (Polynomial& p2) override;
	Polynomial& operator + (Polynomial& p2) override;
	Polynomial& operator - (Polynomial& p2) override;
	Polynomial& operator * (Polynomial& p2) override;
	
	vector<PolynomialVector> GetSturm();
};

inline PolynomialVector ConvertFromPolynomialRef(Polynomial& ref)
{
	PolynomialVector p;
	p.v = ref.v;
	p.isNew = ref.isNew;
	return p;
}

inline Polynomial& CreatePolynomial()
{
	PolynomialVector* polynomialVector = new PolynomialVector();
	return *polynomialVector;
}

inline Polynomial& CreatePolynomial(Number number)
{
	PolynomialVector* polynomialVector = new PolynomialVector(number);
	return *polynomialVector;
}

inline Polynomial& PolynomialVector::CreatePolynomial()
{
	PolynomialVector* polynomialVector = new PolynomialVector();
	return *polynomialVector;
}

inline Polynomial& PolynomialVector::CreatePolynomial(Number number)
{
	PolynomialVector* polynomialVector = new PolynomialVector(number);
	return *polynomialVector;
}


inline PolynomialVector::PolynomialVector() : Polynomial()
{
}

inline PolynomialVector::PolynomialVector(Number number) : Polynomial(number)
{
	if (number != 0)
		v.push_back(pair<int, Number>(0, number));
}

inline int PolynomialVector::Size()
{
	return v.size();
}

inline void PolynomialVector::Clear()
{
	v.clear();
	isNew = true;
}

inline bool PolynomialVector::IsZero()
{
	if (Size() == 0)
		return true;
	for (auto pair1 : v)
	{
		if (pair1.second.Abs() > 0.0000001)
			return false;
	}
	return true;
}

inline int PolynomialVector::PolynomialDegree()
{
	int size = Size();
	if (size)
		return size - 1;
	return 0;
}

inline map<int, Number> PolynomialVector::ValuesExceptValueOfPolynomialDegree(int degree = -1)
{
	map<int, Number> result;
	int polynomialDegree = degree;

	if (degree == -1)
		polynomialDegree = PolynomialDegree();

	for (auto pair1 : v)
	{
		if (pair1.first != polynomialDegree)
			result.insert(pair1);
	}
	return result;
}

inline Number PolynomialVector::Value(int power)
{
	if (power >= Size())
		return Number(0);
	return v[power].second;
}

inline void PolynomialVector::SetNumberValue(int power, Number number)
{
	isNew = false;

	if (power >= Size())
	{
		if (number.IsZero() == false)
		{
			while (power > Size())
				v.push_back(pair<int, Number>(Size(), Number(0)));
			v.push_back(pair<int, Number>(power, number));
		}
		return;
	}
	v[power] = pair<int, Number>(power, number);
	if (power == (Size() - 1) && number.IsZero() == false)
	{
		v.pop_back();
		for (int i = power - 1; i >= 0; i--)
		{
			if (v[i].second.IsZero())
				v.pop_back();
			else
				break;
		}
	}

}

inline string PolynomialVector::ToString()
{
	if (IsZero())
		return("Is Zero");

	string result = StringManager::EmptyString();
	for (auto pair1 : v)
	{
		if (pair1.second.Abs() > 0.0000001)
			result = result + to_string(pair1.first) + ':'
			+ to_string(pair1.second.GetValue()) + ',';
	}

	return StringManager::Substr(result, 0, result.length() - 2);
}

inline bool PolynomialVector::operator == (Polynomial& p2)
{
	for (auto pair1 : v)
	{
		if (ValueEquals(pair1.first, p2) == false)
			return false;
	}

	for (auto pair1 : p2.v)
	{
		if (ValueEquals(pair1.first, p2) == false)
			return false;
	}

	return true;
}

inline Polynomial& PolynomialVector::operator = (Polynomial& p2)
{
	v = p2.v;
	id = p2.id;
	return *this;
}

inline Polynomial& PolynomialVector::operator + (Polynomial& p2)
{
	Polynomial& result = CreatePolynomial();
	result.v = v;
	for (auto pair1 : p2.v)
		result.Add(pair1.first, pair1.second);
	return result;
}

inline Polynomial& PolynomialVector::operator - (Polynomial& p2)
{
	Polynomial& result = CreatePolynomial();
	result.v = v;
	for (auto pair1 : p2.v)
		result.Sub(pair1.first, pair1.second);
	return result;
}

inline Polynomial& PolynomialVector::operator * (Polynomial& p2)
{
	Polynomial& result = CreatePolynomial();
	if (p2.IsZero())
		return result;
	for (auto pair1 : v)
	{
		for (auto pair2 : p2.v)
		{
			auto mulResult = result.Mul(pair1.first, pair1.second, pair2.first, pair2.second);
			result.Add(mulResult.first, mulResult.second);
		}
	}
	return result;
}

inline int PolynomialVector::NumberOfChangesSign(Number a)
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

inline vector<PolynomialVector> PolynomialVector::GetSturm()
{
	if (sturm.size())
		return sturm;
	sturm.push_back(*this);
	Polynomial& derivative = Derivative();
	if (derivative.IsZero())
		return sturm;
	sturm.push_back(ConvertFromPolynomialRef(derivative));
	Polynomial& w = CreatePolynomial();
	Polynomial& q = CreatePolynomial();
	Polynomial& r = CreatePolynomial();
	w.v = v;
	q = derivative;
	r = w % q;

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

inline Polynomial& PolynomialVector::NegativePolynomial()
{
	Polynomial& result = CreatePolynomial();
	for (auto p : v)
	{
		result.SetNumberValue(p.first, Number(-p.second.GetValue()));
	}
	return result;
}

inline Polynomial& PolynomialVector::Derivative()
{
	Polynomial& result = CreatePolynomial();

	for (auto p : v)
	{
		if (p.first > 0)
			result.SetNumberValue(p.first - 1, Number(p.first * p.second.GetValue()));
	}
	return result;
}

inline Number PolynomialVector::PolynomialValue(Number a)
{
	if (IsZero())
		return Number(0);
	Number result(0);
	for (auto pair1 : v)
	{
		result += CoefficientValue(pair1, a);
	}
	return result;
}
