#pragma once
#include "definitions.h"
#include "StringManager.h"
#include "CharsConstants.h"
#include "Number.h"

class Polynomial
{
protected:
	vector<Polynomial> sturm;
public:
	map<int, Number>m;

	explicit Polynomial();
	explicit Polynomial(Number number);

	bool Set(string s);
	void Clear();
	bool IsNew();
	bool IsZero();
	int Size();
	int PolynomialDegree();
	pair<int, Number> ValueOfPolynomialDegree();
	map<int, Number> ValuesExceptValueOfPolynomialDegree(int degree);
	Number Value(int power);
	bool ValueEquals(int power, Polynomial p2);
	void SetValue(int power, Number number);
	void SetValue(int power, int value);
	void Add(int power, Number number);
	void Sub(int power, Number number);
	static pair<int, Number> Mul(int power1, Number number1, int power2, Number number2);
	static pair<int, Number> Div(int power1, Number number1, int power2, Number number2);
	Polynomial NegativePolynomial();

	Polynomial Derivative();
	Polynomial Nwd(Polynomial p1, Polynomial p2);
	Polynomial PolynomialAfterEliminationOfMultipleRoots();
	pair <Polynomial, Polynomial> DividePolynomials(Polynomial p1, Polynomial p2);
	void Normalize();
	Number CoefficientValue(pair<int, Number> pair1, Number a);
	Number PolynomialValue(Number a);
	vector<Polynomial> GetSturm();
	int NumberOfChangesSign(Number a);
	Number NextNumberFromRange(Number a, Number b);
	int NumberOfRoots(Number a, Number b);
	vector<Number> FindRoots(Number a, Number b);

	bool operator==(Polynomial p2);
	bool operator!=(Polynomial p2);
	Polynomial operator = (Polynomial p2);
	Polynomial operator + (Polynomial p2);
	Polynomial operator - (Polynomial p2);
	Polynomial operator * (Polynomial p2);
	Polynomial operator / (Polynomial p2);
	Polynomial operator % (Polynomial p2);
	Polynomial operator ^ (int power);
	Polynomial operator += (Polynomial p2);
	Polynomial operator -= (Polynomial p2);
	Polynomial operator *= (Polynomial p2);
	Polynomial operator /= (Polynomial p2);
	Polynomial operator %= (Polynomial p2);
	Polynomial operator ^= (int power);
	string ToString();
	void Print(string name);

protected:
	bool isNew = true;
};

inline Polynomial::Polynomial()
{
}

inline Polynomial::Polynomial(Number number)
{
	isNew = false;
	if (number != 0)
		m.insert(pair<int, Number>(0, number));
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

inline void Polynomial::Clear()
{
	m.clear();
	isNew = true;
}

inline bool Polynomial::IsNew()
{
	return isNew;
}

inline bool Polynomial::IsZero()
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

inline int Polynomial::Size()
{
	return m.size();
}

inline int Polynomial::PolynomialDegree()
{
	int max = -1;

	for (auto pair1 : m)
	{
		if (pair1.first > max)
			max = pair1.first;
	}
	return max;
}

inline pair<int, Number> Polynomial::ValueOfPolynomialDegree()
{
	int polynomialDegree = PolynomialDegree();

	return pair<int, Number>(polynomialDegree, Value(polynomialDegree));
}

inline map<int, Number> Polynomial::ValuesExceptValueOfPolynomialDegree(int degree = -1)
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

inline Number Polynomial::Value(int power)
{
	if (m.count(power))
		return m.at(power);
	return Number(0);
}

inline bool Polynomial::ValueEquals(int power, Polynomial p2)
{
	return Value(power) == p2.Value(power);
}

inline void Polynomial::SetValue(int power, Number number)
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

inline void Polynomial::SetValue(int power, int value)
{
	Number number(value);
	SetValue(power, number);
}

inline void Polynomial::Add(int power, Number number)
{
	SetValue(power, Value(power) + number);
}

inline void Polynomial::Sub(int power, Number number)
{
	return Add(power, Number(-number.GetValue()));
}

inline pair<int, Number> Polynomial::Mul(int power1, Number number1, int power2, Number number2)
{
	return pair<int, Number>(power1 + power2, number1 * number2);
	//Add(power1 + power2, value1 * value2);
}

inline pair<int, Number> Polynomial::Div(int power1, Number number1, int power2, Number number2)
{
	pair<int, Number> result = pair<int, Number>(power1 - power2, number1 / number2);

	return result;
}

inline Polynomial Polynomial::NegativePolynomial()
{
	Polynomial result;
	for(auto p: m)
	{
		result.SetValue(p.first, Number(-p.second.GetValue()));
	}
	return result;
}

inline Polynomial Polynomial::Derivative()
{
	Polynomial result;

	for (auto p: m)
	{
		if (p.first > 0)
			result.SetValue(p.first - 1, Number(p.first * p.second.GetValue()));
	}
	return result;
}

inline Polynomial Polynomial::Nwd(Polynomial p1, Polynomial p2)
{
	pair<Polynomial, Polynomial> divResult = DividePolynomials(p1, p2);
	if (divResult.second.IsZero())
		return p2;
	if (divResult.second.PolynomialDegree() == 0)
	{
		Polynomial one;
		one.SetValue(0, Number(1));
		return one;
	}
	return Nwd(p2, divResult.second);
}

inline Polynomial Polynomial::PolynomialAfterEliminationOfMultipleRoots()
{
	Polynomial derivative = Derivative();
	derivative.Normalize();
	Polynomial nwd = Nwd(*this, derivative);
	Polynomial normalizeNwd = nwd;
	normalizeNwd.Normalize();
	pair<Polynomial, Polynomial> divResult = DividePolynomials(*this, nwd);
	if (divResult.first.IsZero())
		divResult.first.SetValue(0, Number(1));
	return divResult.first;
}

inline pair<Polynomial, Polynomial> Polynomial::DividePolynomials(Polynomial p1, Polynomial p2)
{
	Polynomial result;

	if (p1.IsZero() || p2.IsZero())
		return pair<Polynomial, Polynomial>(result, result);

	Polynomial current = p1;
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
	return pair<Polynomial, Polynomial>(result, current);
}

inline void Polynomial::Normalize()
{
	Number coefficient = ValueOfPolynomialDegree().second;
	Polynomial divider(coefficient);
	*this /= divider;
}

inline Number Polynomial::CoefficientValue(pair<int, Number> pair1, Number a)
{
	Number result(1);
	for (int i = 0; i < pair1.first; i++)
		result *= a;

	return result * pair1.second;
}

inline Number Polynomial::PolynomialValue(Number a)
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

inline vector<Polynomial> Polynomial::GetSturm()
{
	if (sturm.size())
		return sturm;
	sturm.push_back(*this);
	Polynomial derivative = Derivative();
	if (derivative.IsZero())
		return sturm;
	sturm.push_back(derivative);
	Polynomial w = *this;
	Polynomial q = derivative;
	Polynomial r = w % q;

	while (r.IsZero() == false)
	{
		r = r.NegativePolynomial();
		sturm.push_back(r);
		w = q;
		q = r;
		r = w % q;
	}
	return sturm;
}

inline int Polynomial::NumberOfChangesSign(Number a)
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
		number = sturm[i].PolynomialValue(a);
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
	return NumberOfChangesSign(a) - NumberOfChangesSign(b);
}

inline vector<Number> Polynomial::FindRoots(Number a, Number b)
{
	vector<Number> roots;
	int aIsRoot = 0;
	int bIsRoot = 0;
	int cIsRoot = 0;

	if (PolynomialValue(a).IsZero())
		roots.push_back(a);
	if (PolynomialValue(b).IsZero())
	{
		bIsRoot = 1;
		roots.push_back(b);
	}
	int tmpDebug1 = NumberOfRoots(a, b);
	if (NumberOfRoots(a, b) == aIsRoot)
		return roots;

	Number c = NextNumberFromRange(a, b);
	Number tmpDebu2 = PolynomialValue(c);
	int chA = NumberOfChangesSign(a);
	int chB = NumberOfChangesSign(b);
	int chC = NumberOfChangesSign(c);
	int debug3 = NumberOfRoots(a, c);
	int debug4 = NumberOfRoots(c, b);
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

inline bool Polynomial::operator == (Polynomial p2)
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

inline bool Polynomial::operator != (Polynomial p2)
{
	return !(*this == p2);
}

inline Polynomial Polynomial::operator = (Polynomial p2)
{
	m = p2.m;
	return *this;
}

inline Polynomial Polynomial::operator + (Polynomial p2)
{
	Polynomial result;

	result.m = m;

	for (auto pair1 : p2.m)
	{
		result.Add(pair1.first, pair1.second);
	}

	return result;
}

inline Polynomial Polynomial::operator - (Polynomial p2)
{
	Polynomial result;

	result.m = m;

	for (auto pair1 : p2.m)
	{
		result.Sub(pair1.first, pair1.second);
	}

	return result;
}

inline Polynomial Polynomial::operator * (Polynomial p2)
{
	Polynomial result;

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

inline Polynomial Polynomial::operator / (Polynomial p2)
{
	pair <Polynomial, Polynomial> divResult = DividePolynomials(*this, p2);
	return divResult.first;
}

inline Polynomial Polynomial::operator % (Polynomial p2)
{
	pair <Polynomial, Polynomial> divResult = DividePolynomials(*this, p2);
	return divResult.second;
}

inline Polynomial Polynomial::operator ^ (int power)
{
	Polynomial result;

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

inline Polynomial Polynomial::operator += (Polynomial p2)
{
	*this = *this + p2;
	return *this;
}

inline Polynomial Polynomial::operator -= (Polynomial p2)
{
	*this = *this - p2;
	return *this;
}

inline Polynomial Polynomial::operator *= (Polynomial p2)
{
	*this = *this * p2;
	return *this;
}

inline Polynomial Polynomial::operator /= (Polynomial p2)
{
	*this = *this / p2;
	return *this;
}

inline Polynomial Polynomial::operator %= (Polynomial p2)
{
	*this = *this % p2;
	return *this;
}

inline Polynomial Polynomial::operator ^= (int power)
{
	*this = *this ^ power;
	return *this;
}

inline string Polynomial::ToString()
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

inline void Polynomial::Print(string name)
{
	printf("\t%s:\n", name.c_str());
	cout << ToString() << endl;
}

