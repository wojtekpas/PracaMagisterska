#pragma once
#include "definitions.h"
#include "StringManager.h"
#include "CharsConstants.h"
#include "Number.h"

#define PAIR pair<int,Number>
#define VECTOR vector<PAIR>
#define MAP map<int,Number>

static int countPolynomialVectors = 0;
static int countPolynomialVectorsDeleted = 0;
static int countPlus = 0;
static int countMinus = 0;
static int countMul = 0;
static int countDiv = 0;
static int countMod = 0;

class Polynomial
{
public:
	MAP m;
	VECTOR v;
	bool isNew = true;
	int type = 0;
	string inputS = "";
	vector<Number> roots;
	int id = 0;

	explicit Polynomial();
	explicit Polynomial(Number number);
	~Polynomial();

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
	virtual void SturmClear() = 0;
	virtual int TheLowestNonZeroValue() = 0;

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
	void SetValue(int power, double value);
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
	int AddNextRoot(Number x);
	vector<Number> FindRoots(Number a, Number b);
	void PrintRoots(Number a, Number b);

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

inline void PrintStats()
{	
	cout << "created = " << countPolynomialVectors << ", deleted = " << countPolynomialVectorsDeleted << 
		", numbers = " << countNumbers << ", numbers2 = " << countNumbers2 << 
		", numbers3 = " << countNumbers3 << 
		", deleted = " << countNumbersDeleted << ", deleted2 = " << countNumbersDeleted2 << endl;
}

inline void DeletePolynomial(Polynomial* p)
{
//	for(auto pair1: p->v)
//	{
//		DeleteNumber(&pair1.second);
//	}
//	for (auto pair1 : p->m)
//	{
//		DeleteNumber(&pair1.second);
//	}
	delete p;
}

inline Polynomial::Polynomial()
{
	countPolynomialVectors++;
}

inline Polynomial::Polynomial(Number number)
{
	countPolynomialVectors++;
	isNew = false;
}

inline Polynomial::~Polynomial()
{
	countPolynomialVectorsDeleted++;
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

inline void Polynomial::SetValue(int power, double value)
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
	return Add(power, number.Neg());
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
	p1.Normalize();
	p2.Normalize();
	//p1.Print();
	//p2.Print();
	auto divResult = DividePolynomials(p1, p2);
	divResult.first.Normalize();
	divResult.second.Normalize();
	//divResult.first.Print();
	//divResult.second.Print();

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
	Polynomial& nwd = Nwd(p2, divResult.second);
	DeletePolynomial(&divResult.first);
	DeletePolynomial(&divResult.second);
	return nwd;
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

	DeletePolynomial(&nwd);
	DeletePolynomial(&derivative);
	DeletePolynomial(&divResult.second);
	return divResult.first;
}

inline void Polynomial::Normalize()
{
	Number coefficient = ValueOfPolynomialDegree().second;
	Polynomial& divider = CreatePolynomial(coefficient);
	*this /= divider;
	//DeletePolynomial(&divider);
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
		if (a == 0)
			return Number(1);
		if (a == 1)
			return Number(2);
		return Number(a * a.Abs());
	}
	if (a * b < 0)
		return Number(0);
	return Number((a + b) / 2);
}

inline int Polynomial::NumberOfRoots(Number a, Number b)
{
	int count1 = NumberOfChangesSign(a);
	int count2 = NumberOfChangesSign(b);
	if (count1 - count2 < 0)
	{
//		cout << " count1 = " << count1 << endl;
//		cout << " count2 = " << count2 << endl;
//		cout << "dupa" << endl;
		int count2 = NumberOfChangesSign(b);
	}
	return count1 - count2;
}

inline int Polynomial::AddNextRoot(Number x)
{
	int posInVector = x.IsInVector(roots);
	if (posInVector < 0)
	{
		roots.push_back(x);
		return 1;
	}
//	if (x > roots[posInVector])
//		roots[posInVector] = x;
	return 0;
}

inline vector<Number> Polynomial::FindRoots(Number a, Number b)
{
	int theLowest = TheLowestNonZeroValue();
	if (theLowest > 0)
	{
		AddNextRoot(Number(0));
		Polynomial& tmp = CreatePolynomial();
		tmp.SetValue(theLowest, 1);
		*this /= tmp;
		DeletePolynomial(&tmp);
		SturmClear();
	}
	int numberOfRoots = NumberOfRoots(a, b);
//	cout << numberOfRoots << " in " << "("
//		<< a.ToString() << "," << b.ToString() << ")" << endl;
//	Print();
	if (numberOfRoots == 0)
		return roots;
	Number aValue;
	aValue = PolynomialValue(a);
	//cout << "aValue = " << aValue.ToString() << endl;
	if (aValue.IsZero())
	{
		int aIsRoot = AddNextRoot(a);
		if (aIsRoot == numberOfRoots)
			return roots;
	}
	Number bValue;
	bValue = PolynomialValue(b);
	//cout << "bValue = " << bValue.ToString() << endl;
	if (bValue.IsZero())
	{
		AddNextRoot(b);
		if (numberOfRoots == 1)
			return roots;
	}

	if (numberOfRoots == 0)
		return roots;

	Number c = NextNumberFromRange(a, b);
	Number cValue;
	cValue = PolynomialValue(c);
	//cout << "cValue = " << cValue.ToString() << endl;
	if (cValue.IsZero())
	{
		int cIsRoot = AddNextRoot(c);
		if (cIsRoot == numberOfRoots)
			return roots;
	}

	Number interval = b - a;
	if (interval.IsWithRequiredPrecision())
	{
		//cout << "interval" << endl;
		AddNextRoot(b);
		return roots;
	}
	
	interval /= 2;

	int numberOfRootsAC = NumberOfRoots(a, c);
	
	if(numberOfRootsAC)
	{
		vector<Number> rootsInRange = FindRoots(a, c);
		for (int i = 0; i < rootsInRange.size(); i++)
		{
			Number potentialRoot = rootsInRange[i];
			AddNextRoot(potentialRoot);
		}
	}
	int numberOfRootsCB = NumberOfRoots(c, b);
	
	if(numberOfRootsCB)
	{
		vector<Number> rootsInRange = FindRoots(c, b);
		for (int i = 0; i < rootsInRange.size(); i++)
		{
			Number potentialRoot = rootsInRange[i];
			AddNextRoot(potentialRoot);
		}
	}
	return roots;
}

inline void Polynomial::PrintRoots(Number a, Number b)
{
	if(a > b)
	{
		cout << "Niepoprawny przedzial: <" << a.ToString() << ", " << b.ToString() << ">" << endl;
		return;
	}
	if (IsZero())
	{
		cout << "Wielomian zerowy - brak pierwiastkow" << endl;
		return;
	}
	cout << "Pierwiastki w przedziale: <" << a.ToString() << ", " << b.ToString() << ">" << endl;
	Number numberA = a;
	Number numberB = b;
	vector<Number> roots = FindRoots(numberA, numberB);
	roots = SortNumbers(roots);
	for (int i = 0; i < roots.size(); i++)
	{
		cout << "x" << i+1 << " = ";
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
	countDiv++;
	auto divResult = DividePolynomials(*this, p2);
	DeletePolynomial(&divResult.second);
	return divResult.first;
}

inline Polynomial& Polynomial::operator % (Polynomial& p2)
{
	countMod++;
	auto divResult = DividePolynomials(*this, p2);
	DeletePolynomial(&divResult.first);
	return divResult.second;
}

inline Polynomial& Polynomial::operator ^ (int power)
{
	Polynomial& result = CreatePolynomial();
	Polynomial& tmp = CreatePolynomial();

	if (power == 0)
	{
		if (IsZero())
			return result;

		result.SetNumberValue(0, Number(1));
		return result;
	}

	result = *this;
	tmp = *this;

	for (int i = 1; i < power; i++)
	{
		result *= tmp;
	}

	DeletePolynomial(&tmp);
	return result;
}

inline Polynomial& Polynomial::operator += (Polynomial& p2)
{
	Polynomial* result = &(*this + p2);
	*this = *result;
	DeletePolynomial(result);
	return *this;
}

inline Polynomial& Polynomial::operator -= (Polynomial& p2)
{
	Polynomial* result = &(*this - p2);
	*this = *result;
	DeletePolynomial(result);
	return *this;
}

inline Polynomial& Polynomial::operator *= (Polynomial& p2)
{
	Polynomial* result = &(*this * p2);
	*this = *result;
	DeletePolynomial(result);
	return *this;
}

inline Polynomial& Polynomial::operator /= (Polynomial& p2)
{
	Polynomial* result = &(*this / p2);
	*this = *result;
	DeletePolynomial(result);
	return *this;
}

inline Polynomial& Polynomial::operator %= (Polynomial& p2)
{
	Polynomial* result = &(*this % p2);
	*this = *result;
	DeletePolynomial(result);
	return *this;
}

inline Polynomial& Polynomial::operator ^= (int power)
{
	Polynomial* result = &(*this ^ power);
	*this = *result;
	DeletePolynomial(result);
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
