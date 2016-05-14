#pragma once
#include "definitions.h"
#include "StringManager.h"
#include "CharsConstants.h"
#include "Number.h"

#define PAIR pair<int,Number>
#define VECTOR vector<PAIR>
#define MAP map<int,Number>

class Polynomial
{
public:
	MAP m;
	VECTOR v;
	bool isNew = true;
	string inputS = "";

	explicit Polynomial();
	explicit Polynomial(Number number);

	virtual Polynomial& CreatePolynomial() = 0;
	virtual Polynomial& CreatePolynomial(Number number) = 0;
	virtual void Clear() = 0;
	virtual bool IsZero() = 0;
	virtual int Size() = 0;
	virtual int PolynomialDegree() = 0;
	virtual Number Value(int power) = 0;
	virtual pair<Polynomial&, Polynomial&> DividePolynomials(Polynomial& p1, Polynomial& p2) = 0;
	virtual void SetNumberValue(int power, Number number) = 0;
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

	virtual VECTOR VectorValuesExceptValueOfPolynomialDegree(int degree) { return{}; };
	virtual MAP MapValuesExceptValueOfPolynomialDegree(int degree) { return{}; };
	
	bool Set(string s);
	bool IsNew();
	PAIR ValueOfPolynomialDegree();

	bool ValueEquals(int power, Polynomial& p2);
	void SetValue(int power, int value);
	void Add(int power, Number number);
	void Sub(int power, Number number);
	PAIR Mul(int power1, Number number1, int power2, Number number2);
	PAIR Div(int power1, Number number1, int power2, Number number2);
	Polynomial& Nwd(Polynomial& p1, Polynomial& p2);
	Polynomial& PolynomialAfterEliminationOfMultipleRoots();
	void Normalize();
	Number CoefficientValue(PAIR pair1, Number a);
	Number NextNumberFromRange(Number a, Number b);
	int NumberOfRoots(Number a, Number b);
	void AddNextRoot(vector<Number>& roots, Number x);
	vector<Number> FindRoots(Number a, Number b);
	void PrintRoots(double a, double b);

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
	void Print();
	void PrintInput();
};

inline Polynomial::Polynomial()
{
}

inline Polynomial::Polynomial(Number number)
{
	isNew = false;
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

inline PAIR Polynomial::ValueOfPolynomialDegree()
{
	int polynomialDegree = PolynomialDegree();
	Number value = Value(polynomialDegree);

	return PAIR(polynomialDegree, value);
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

inline PAIR Polynomial::Mul(int power1, Number number1, int power2, Number number2)
{
	return PAIR(power1 + power2, number1 * number2);
}

inline PAIR Polynomial::Div(int power1, Number number1, int power2, Number number2)
{
	return PAIR(power1 - power2, number1 / number2);
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

inline Number Polynomial::CoefficientValue(PAIR pair1, Number a)
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

inline void Polynomial::AddNextRoot(vector<Number>& roots, Number x)
{
	if (x.IsInVector(roots) == false)
		roots.push_back(x);
}

inline vector<Number> Polynomial::FindRoots(Number a, Number b)
{
	vector<Number> roots;
	int cIsRoot = 0;

	if (PolynomialValue(a).IsZero())
	{
		AddNextRoot(roots, a);
	}
	if (PolynomialValue(b).IsZero())
	{
		AddNextRoot(roots, b);
	}
	if (NumberOfRoots(a, b) == 0)
		return roots;

	Number c = NextNumberFromRange(a, b);
	int ab = NumberOfRoots(a, b);
	int ac = NumberOfRoots(a, c);
	int bc = NumberOfRoots(c, b);
	if (PolynomialValue(c).IsZero())
	{
		cIsRoot = 1;
		AddNextRoot(roots, c);
	}

	Number interval = b - a;
	if (interval.IsZero())
	{
		AddNextRoot(roots, a);
		return roots;
	}
	
	interval /= 2;

	if(NumberOfRoots(a, c))
	{
		vector<Number> rootsInRange = FindRoots(a, c);
		for (int i = 0; i < rootsInRange.size(); i++)
		{
			Number potentialRoot = rootsInRange[i];
			AddNextRoot(roots, potentialRoot);
		}
	}
	if(NumberOfRoots(c, b) > cIsRoot)
	{
		vector<Number> rootsInRange = FindRoots(c, b);
		for (int i = 0; i < rootsInRange.size(); i++)
		{
			Number potentialRoot = rootsInRange[i];
			AddNextRoot(roots, potentialRoot);
		}
	}
	return roots;
}

inline void Polynomial::PrintRoots(double a, double b)
{
	if(a > b)
	{
		cout << "Niepoprawny przedzial: <" << a << ", " << b << ">" << endl;
		return;
	}
	if (IsZero())
	{
		cout << "Wielomian zerowy - brak pierwiastkow" << endl;
		return;
	}
	cout << "Pierwiastki w przedziale: <" << a << ", " << b << ">" << endl;
	Number numberA = Number(a);
	Number numberB = Number(b);
	vector<Number> roots = FindRoots(numberA, numberB);

	for (int i = 0; i < roots.size(); i++)
	{
		cout << "x" << i << " = ";
		roots[i].Print();
	}
	if (roots.size() == 0)
		cout << "Brak pierwiastkow rzeczywistych" << endl;
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

inline void Polynomial::Print()
{
	cout << "Polynomial: '" << ToString() << "'" << endl;
}

inline void Polynomial::PrintInput()
{
	cout << "Input: '" << inputS << "'" << endl;
}
