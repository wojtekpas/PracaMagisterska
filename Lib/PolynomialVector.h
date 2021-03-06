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
	void SturmClear() override;
	int TheLowestNonZeroValue() override;

	bool operator==(Polynomial& p2) override;
	Polynomial& operator = (Polynomial& p2) override;
	Polynomial& operator + (Polynomial& p2) override;
	Polynomial& operator - (Polynomial& p2) override;
	Polynomial& operator * (Polynomial& p2) override;
	
	VECTOR VectorValuesExceptValueOfPolynomialDegree(int degree) override;
	vector<PolynomialVector> GetSturm();
	void PrintSturm();
};

inline PolynomialVector ConvertToPolynomialVectorFromPolynomialRef(Polynomial& ref)
{
	PolynomialVector p;
	for (int i = 0; i < ref.v.size(); i++)
	{
		Number copy = ref.v[i].second.Copy();
		p.SetNumberValue(i, copy);
	}
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
	type = 1;
}

inline PolynomialVector::PolynomialVector(Number number) : Polynomial(number)
{
	type = 1;
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
	VECTOR vector2 = p2.VectorValuesExceptValueOfPolynomialDegree(degree);

	while (currentDegree >= degree)
	{
		PAIR pair1 = PAIR(currentDegree, current.Value(currentDegree));
		VECTOR vector1 = current.VectorValuesExceptValueOfPolynomialDegree(currentDegree);

		auto divResult = Div(pair1.first, pair1.second, pair2.first, pair2.second);

		if (divResult.second != 0)
		{
			result.SetNumberValue(divResult.first, divResult.second);
			current.SetNumberValue(currentDegree, Number(0));
			for (auto curPair : vector2)
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
	DeletePolynomial(&rest);

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

	string result = "";
	string tmp = "";
	for (auto pair1 : v)
	{
		if (pair1.second.IsZero() == false)
		{
			tmp = "";
			string fir = to_string(pair1.first);
			string sec = pair1.second.ToString();
			if (pair1.first == 0)
				tmp = sec;
			else
			{
				if (pair1.second == 1)
					tmp = "x";
				else if (pair1.second == -1)
					tmp = "-x";
				else
					tmp = sec + "x";
				if (pair1.first != 1)
				{
					tmp = tmp + "^" + fir;
				}
			}
			if (tmp[0] != '-')
				tmp = "+" + tmp;
			result = tmp + result;
		}
	}
	if (result[0] == '+')
		return StringManager::Substr(result, 1, result.length() - 1);
	return result;
}

inline void PolynomialVector::SturmClear()
{
	sturm.clear();
}

inline int PolynomialVector::TheLowestNonZeroValue()
{
	int size = Size();
	if (size == 0)
		return -1;
	for (int i = 0; i < size; i++)
	{
		if (Value(i).IsZero() == false)
			return i;
	}
	return -2;
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
	v.clear();
	for (int i = 0; i < p2.v.size(); i++)
	{
		Number copy = p2.v[i].second.Copy();
		SetNumberValue(i, copy);
	}
	inputS = p2.inputS;
	return *this;
}

inline Polynomial& PolynomialVector::operator + (Polynomial& p2)
{
	Polynomial& result = CreatePolynomial();
	countPlus++;
	result.v = v;
	for (auto pair1 : p2.v)
		result.Add(pair1.first, pair1.second);
	return result;
}

inline Polynomial& PolynomialVector::operator - (Polynomial& p2)
{
	Polynomial& result = CreatePolynomial();
	countMinus++;
	result.v = v;
	for (auto pair1 : p2.v)
		result.Sub(pair1.first, pair1.second);
	return result;
}

inline Polynomial& PolynomialVector::operator * (Polynomial& p2)
{
	Polynomial& result = CreatePolynomial();
	countMul++;
	if (p2.IsZero())
		return result;
	for (auto pair1: v)
	{
		for (auto pair2: p2.v)
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
	{
		DeletePolynomial(&derivative);
		PrintSturm();
		return sturm;
	}
	sturm.push_back(ConvertToPolynomialVectorFromPolynomialRef(derivative));
	Polynomial& w = CreatePolynomial();
	Polynomial& q = CreatePolynomial();
	Polynomial& r = CreatePolynomial();
	w = *this;
	q = derivative;
	r = w % q;

	while (r.IsZero() == false)
	{
		Polynomial* tmp = &(r.NegativePolynomial());
		r = *tmp;
		DeletePolynomial(tmp);
		sturm.push_back(ConvertToPolynomialVectorFromPolynomialRef(r));
		w = q;
		q = r;
		tmp = &(w % q);
		r = *tmp;
		DeletePolynomial(tmp);
	}
	DeletePolynomial(&w);
	DeletePolynomial(&q);
	DeletePolynomial(&r);
	DeletePolynomial(&derivative);
	PrintSturm();
	return sturm;
}

inline void PolynomialVector::PrintSturm()
{
	if (DISPLAYING_STURM == 0)
		return;

	printf("Wyrazy ciagu Sturma:\n");
	for (int i = 0; i < sturm.size(); i++)
	{
		sturm[i].Print(1);
	}
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

inline Number PolynomialVector::PolynomialValue(Number x)
{
	if (IsZero())
		return Number(0);
	Number result(0);
	for (auto pair1 : v)
	{
		result += CoefficientValue(pair1, x);
	}
	return result;
}
