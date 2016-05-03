#pragma once
#include "definitions.h"
#include "StringManager.h"
#include "CharsConstants.h"
#include "Number.h"

static int globId = 0;

class Polynomial
{
public:
	map<int, Number>m;
	bool isNew = true;
	int id = 0;

	explicit Polynomial();
	explicit Polynomial(Number number);

	virtual Polynomial& CreatePolynomial() = 0;
	virtual Polynomial& CreatePolynomial(Number number) = 0;
	virtual void Clear() = 0;
	virtual bool IsZero() = 0;
	virtual int Size() = 0;
	virtual int PolynomialDegree() = 0;
	virtual Number Value(int power) = 0;
	virtual void SetNumberValue(int power, Number number) = 0;
	virtual map<int, Number> ValuesExceptValueOfPolynomialDegree(int degree) = 0;
	virtual int NumberOfChangesSign(Number a) = 0;
	virtual Polynomial& NegativePolynomial() = 0;
	virtual Polynomial& Derivative() = 0;
	virtual Number PolynomialValue(Number a) = 0;
	virtual string ToString() = 0;

	virtual bool operator==(Polynomial& p2) = 0;
	virtual Polynomial& operator = (Polynomial& p2) = 0;
	virtual Polynomial& operator + (Polynomial& p2) = 0;
	virtual Polynomial& operator - (Polynomial& p2) = 0;
	virtual Polynomial& operator * (Polynomial& p2) = 0;
	
	bool Set(string s);
	bool IsNew();
	pair<int, Number> ValueOfPolynomialDegree();

	bool ValueEquals(int power, Polynomial& p2);
	void SetValue(int power, int value);
	void Add(int power, Number number);
	void Sub(int power, Number number);
	pair<int, Number> Mul(int power1, Number number1, int power2, Number number2);
	pair<int, Number> Div(int power1, Number number1, int power2, Number number2);
	pair<Polynomial&, Polynomial&> DividePolynomials(Polynomial& p1, Polynomial& p2);
	Polynomial& Nwd(Polynomial& p1, Polynomial& p2);
	Polynomial& PolynomialAfterEliminationOfMultipleRoots();
	void Normalize();
	Number CoefficientValue(pair<int, Number> pair1, Number a);
	Number NextNumberFromRange(Number a, Number b);
	int NumberOfRoots(Number a, Number b);
	vector<Number> FindRoots(Number a, Number b);

	bool operator!=(Polynomial& p2);
	Polynomial& operator / (Polynomial& p2);
	Polynomial& operator % (Polynomial& p2);
	Polynomial& operator ^ (int power);
	Polynomial& operator += (Polynomial& p2);
	Polynomial& operator -= (Polynomial& p2);
	Polynomial& operator *= (Polynomial& p2);
	Polynomial& operator /= (Polynomial& p2);
	Polynomial& operator %= (Polynomial& p2);
	Polynomial& operator ^= (int power);
	void Print(string name);

};

inline Polynomial::Polynomial()
{
	id = globId++;
}

inline Polynomial::Polynomial(Number number)
{
	isNew = false;
	id = globId++;
}

inline bool Polynomial::Set(string s)
{
	Clear();

	if (StringManager::IsEmptyString(s))
		return false;

	if (CharsConstants::IsVar(s[0]))
	{
		if (s.length() > 1)
			return false;
			
		SetNumberValue(1, Number(1));
		return true;
	}

	Number number(CharsConstants::CharToInt(s[0]));

	for (int i = 1; i < s.length(); i++)
	{
		number *= 10;
		number = number + CharsConstants::CharToInt(s[i]);
	}

	if(number != 0)
		SetNumberValue(0, number);
	return true;
}

inline bool Polynomial::IsNew()
{
	return isNew;
}

inline pair<int, Number> Polynomial::ValueOfPolynomialDegree()
{
	int polynomialDegree = PolynomialDegree();
	Number value = Value(polynomialDegree);

	return pair<int, Number>(polynomialDegree, value);
}

inline bool Polynomial::ValueEquals(int power, Polynomial& p2)
{
	return Value(power) == p2.Value(power);
}

inline void Polynomial::SetValue(int power, int value)
{
	Number number(value);
	SetNumberValue(power, number);
}

inline void Polynomial::Add(int power, Number number)
{
	SetNumberValue(power, Value(power) + number);
}

inline void Polynomial::Sub(int power, Number number)
{
	return Add(power, Number(-number.GetValue()));
}

inline pair<int, Number> Polynomial::Mul(int power1, Number number1, int power2, Number number2)
{
	return pair<int, Number>(power1 + power2, number1 * number2);
}

inline pair<int, Number> Polynomial::Div(int power1, Number number1, int power2, Number number2)
{
	return pair<int, Number>(power1 - power2, number1 / number2);
}

inline pair<Polynomial&, Polynomial&> Polynomial::DividePolynomials(Polynomial& p1, Polynomial& p2)
{
	Polynomial& result = CreatePolynomial();
	Polynomial& rest = CreatePolynomial();

	if (p1.IsZero() || p2.IsZero())
		return pair<Polynomial&, Polynomial&>(result, rest);

	Polynomial& current = CreatePolynomial();
	current = p1;
	int currentDegree = current.PolynomialDegree();
	int degree = p2.PolynomialDegree();
	pair<int, Number> pair2 = pair<int, Number>(degree, p2.Value(degree));
	map<int, Number> map2 = p2.ValuesExceptValueOfPolynomialDegree(degree);

	while (currentDegree >= degree)
	{
		pair<int, Number> pair1 = pair<int, Number>(currentDegree, current.Value(currentDegree));
		map<int, Number> map1 = current.ValuesExceptValueOfPolynomialDegree(currentDegree);

		auto divResult = Div(pair1.first, pair1.second, pair2.first, pair2.second);

		result.SetNumberValue(divResult.first, divResult.second);

		if (divResult.second != 0)
		{
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

inline Polynomial& Polynomial::Nwd(Polynomial& p1, Polynomial& p2)
{
	auto divResult = DividePolynomials(p1, p2);
	if (divResult.second.IsZero())
	{
		Polynomial& result = CreatePolynomial();
		result = p2;
		return result;
	}
	if (divResult.second.PolynomialDegree() == 0)
	{
		Polynomial& one = CreatePolynomial();
		one.SetNumberValue(0, Number(1));
		return one;
	}
	return Nwd(p2, divResult.second);
}

inline Polynomial& Polynomial::PolynomialAfterEliminationOfMultipleRoots()
{
	Polynomial& derivative = Derivative();
	derivative.Normalize();
	Polynomial& nwd = Nwd(*this, derivative);
	nwd.Normalize();
	pair<Polynomial&, Polynomial&> divResult = DividePolynomials(*this, nwd);
	if (divResult.first.IsZero())
		divResult.first.SetNumberValue(0, Number(1));
	return divResult.first;
}

inline void Polynomial::Normalize()
{
	Number coefficient = ValueOfPolynomialDegree().second;
	Polynomial& divider = CreatePolynomial(coefficient);
	*this /= divider;
}

inline Number Polynomial::CoefficientValue(pair<int, Number> pair1, Number a)
{
	Number result(1);
	for (int i = 0; i < pair1.first; i++)
		result *= a;

	return result * pair1.second;
}

inline Number Polynomial::NextNumberFromRange(Number a, Number b)
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
	if (a * b < 0)
		return Number(0);
	return Number((a + b) / 2);
}

inline int Polynomial::NumberOfRoots(Number a, Number b)
{
	int count1 = NumberOfChangesSign(a);
	int count2 = NumberOfChangesSign(b);
	return count1 - count2;
}

inline vector<Number> Polynomial::FindRoots(Number a, Number b)
{
	vector<Number> roots;
	int aIsRoot = 0;
	int cIsRoot = 0;

	if (PolynomialValue(a).IsZero())
		roots.push_back(a);
	if (PolynomialValue(b).IsZero())
	{
		roots.push_back(b);
	}
	//int tmpDebug1 = NumberOfRoots(a, b);
	if (NumberOfRoots(a, b) == aIsRoot)
		return roots;

	Number c = NextNumberFromRange(a, b);
	//Number tmpDebu2 = PolynomialValue(c);
	//int chA = NumberOfChangesSign(a);
	//int chB = NumberOfChangesSign(b);
	//int chC = NumberOfChangesSign(c);
	//int debug3 = NumberOfRoots(a, c);
	//int debug4 = NumberOfRoots(c, b);
	if (PolynomialValue(c).IsZero())
	{
		cIsRoot = 1;
		roots.push_back(c);
	}
	if(NumberOfRoots(a, c) > aIsRoot)
	{
		vector<Number> rootsInRange = FindRoots(a, c);
		for (int i = 0; i < rootsInRange.size(); i++)
		{
			Number potentialRoot = rootsInRange[i];
			Number diff1(potentialRoot.GetValue() - a.GetValue());
			Number diff2(potentialRoot.GetValue() - c.GetValue());
			if (diff1.IsZero() == false && diff2.IsZero() == false)
				roots.push_back(potentialRoot);
		}
	}
	if(NumberOfRoots(c, b) > cIsRoot)
	{
		vector<Number> rootsInRange = FindRoots(c, b);
		for (int i = 0; i < rootsInRange.size(); i++)
		{
			Number potentialRoot = rootsInRange[i];
			Number diff1(potentialRoot.GetValue() - c.GetValue());
			Number diff2(potentialRoot.GetValue() - b.GetValue());
			if (diff1.IsZero() == false && diff2.IsZero() == false)
				roots.push_back(potentialRoot);
		}
	}
	return roots;
}

inline bool Polynomial::operator != (Polynomial& p2)
{
	return !(*this == p2);
}

inline Polynomial& Polynomial::operator / (Polynomial& p2)
{
	auto divResult = DividePolynomials(*this, p2);
	return divResult.first;
}

inline Polynomial& Polynomial::operator % (Polynomial& p2)
{
	auto divResult = DividePolynomials(*this, p2);
	return divResult.second;
}

inline Polynomial& Polynomial::operator ^ (int power)
{
	Polynomial& result = CreatePolynomial();

	if (power == 0)
	{
		if (IsZero())
			return result;

		result.SetNumberValue(0, Number(1));
		return result;
	}

	result = *this;

	for (int i = 1; i < power; i++)
	{
		result *= *this;
	}

	return result;
}

inline Polynomial& Polynomial::operator += (Polynomial& p2)
{
	*this = *this + p2;
	return *this;
}

inline Polynomial& Polynomial::operator -= (Polynomial& p2)
{
	*this = *this - p2;
	return *this;
}

inline Polynomial& Polynomial::operator *= (Polynomial& p2)
{
	*this = *this * p2;
	return *this;
}

inline Polynomial& Polynomial::operator /= (Polynomial& p2)
{
	*this = *this / p2;
	return *this;
}

inline Polynomial& Polynomial::operator %= (Polynomial& p2)
{
	*this = *this % p2;
	return *this;
}

inline Polynomial& Polynomial::operator ^= (int power)
{
	*this = *this ^ power;
	return *this;
}

inline void Polynomial::Print(string name)
{
	printf("\t%s:\n", name.c_str());
	cout << ToString() << endl;
}

