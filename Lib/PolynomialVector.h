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
	pair<Polynomial&, Polynomial&> DividePolynomials(Polynomial& p1, Polynomial& p2) override;
	void SetNumberValue(int power, Number number) override;
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
	
	VECTOR VectorValuesExceptValueOfPolynomialDegree(int degree) override;
	vector<PolynomialVector> GetSturm();
};

inline PolynomialVector ConvertToPolynomialVectorFromPolynomialRef(Polynomial& ref)
{
	PolynomialVector p;
	p.v = ref.v;
	p.isNew = ref.isNew;
	p.inputS = ref.inputS;
	return p;
}

inline Polynomial& CreatePolynomialVector()
{
	PolynomialVector* polynomialVector = new PolynomialVector();
	return *polynomialVector;
}

inline Polynomial& CreatePolynomialVector(Number number)
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
		v.push_back(PAIR(0, number));
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
		if (pair1.second.IsVerySmallValue() == false)
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

inline Number PolynomialVector::Value(int power)
{
	if (power >= Size())
		return Number(0);
	return v[power].second;
}

inline VECTOR PolynomialVector::VectorValuesExceptValueOfPolynomialDegree(int degree = -1)
{
	VECTOR result;
	int polynomialDegree = degree;

	if (degree == -1)
		polynomialDegree = PolynomialDegree();

	for (auto pair1 : v)
	{
		if (pair1.first != polynomialDegree)
			result.push_back(pair1);
	}
	return result;
}

inline pair<Polynomial&, Polynomial&> PolynomialVector::DividePolynomials(Polynomial& p1, Polynomial& p2)
{
	Polynomial& result = CreatePolynomial();
	Polynomial& rest = CreatePolynomial();

	if (p1.IsZero() || p2.IsZero())
		return pair<Polynomial&, Polynomial&>(result, rest);

	Polynomial& current = CreatePolynomial();
	current = p1;
	int currentDegree = current.PolynomialDegree();
	int degree = p2.PolynomialDegree();
	PAIR pair2 = PAIR(degree, p2.Value(degree));
	VECTOR map2 = p2.VectorValuesExceptValueOfPolynomialDegree(degree);

	while (currentDegree >= degree)
	{
		PAIR pair1 = PAIR(currentDegree, current.Value(currentDegree));
		VECTOR map1 = current.VectorValuesExceptValueOfPolynomialDegree(currentDegree);

		auto divResult = Div(pair1.first, pair1.second, pair2.first, pair2.second);

		if (divResult.second != 0)
		{
			result.SetNumberValue(divResult.first, divResult.second);
			current.SetNumberValue(currentDegree, Number(0));
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

inline void PolynomialVector::SetNumberValue(int power, Number number)
{
	isNew = false;

	if (power >= Size())
	{
		if (number.IsZero() == false)
		{
			while (power > Size())
				v.push_back(PAIR(Size(), Number(0)));
			v.push_back(PAIR(power, number));
		}
		return;
	}
	v[power] = PAIR(power, number);
	if (power == (Size() - 1) && number.IsZero())
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
	string tmp = "";
	for (auto pair1 : v)
	{
		if (pair1.second.IsZero() == false)
		{
			tmp = "";
			if (pair1.first == 0)
				tmp = pair1.second.ToString();
			else
			{
				if (pair1.first == 1)
					tmp = pair1.second.ToString() + "*x";
				else
					tmp = pair1.second.ToString()+ "*x^" + to_string(pair1.first);
			}
			if (tmp[0] != '-' && result != "")
				tmp = "+" + tmp;
			result += tmp;
		}
	}
	return result;
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
	m = p2.m;
	inputS = p2.inputS;
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
	DEBUG cout << "For: " << a.ToString() << ":" << endl;
	Number number = PolynomialValue(a);
	DEBUG cout << number.ToString() << endl;
	if (number > 0)
		lastValue = 1;
	else if (number < 0)
		lastValue = -1;

	for (int i = 1; i < sturm.size(); i++)
	{
		number = sturm.at(i).PolynomialValue(a);
		DEBUG cout << number.ToString() << endl;
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
	sturm.push_back(ConvertToPolynomialVectorFromPolynomialRef(derivative));
	Polynomial& w = CreatePolynomial();
	Polynomial& q = CreatePolynomial();
	Polynomial& r = CreatePolynomial();
	w.v = v;
	q = derivative;
	r = w % q;

	while (r.IsZero() == false)
	{
		r = r.NegativePolynomial();
		sturm.push_back(ConvertToPolynomialVectorFromPolynomialRef(r));
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
		result.SetNumberValue(p.first, p.second.Neg());
	}
	return result;
}

inline Polynomial& PolynomialVector::Derivative()
{
	Polynomial& result = CreatePolynomial();

	for (auto p : v)
	{
		if (p.first > 0)
			result.SetNumberValue(p.first - 1, p.second * p.first);
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
