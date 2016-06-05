#pragma once
#include "Polynomial.h"

class PolynomialMap: public Polynomial
{
public:
	vector<PolynomialMap> sturm;

	explicit PolynomialMap();
	explicit PolynomialMap(Number number);
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
	void CleanBeforeDelete() override;

	bool operator==(Polynomial& p2) override;
	Polynomial& operator = (Polynomial& p2) override;
	Polynomial& operator + (Polynomial& p2) override;
	Polynomial& operator - (Polynomial& p2) override;
	Polynomial& operator * (Polynomial& p2) override;
	
	MAP MapValuesExceptValueOfPolynomialDegree(int degree) override;
	vector<PolynomialMap> GetSturm();
};

inline PolynomialMap ConvertToPolynomialMapFromPolynomialRef(Polynomial& ref)
{
	PolynomialMap p;
	for (auto m : ref.m)
	{
		Number copy = m.second.Copy();
		p.SetNumberValue(m.first, copy);
	}
	p.inputS = ref.inputS;
	return p;
}

inline Polynomial& CreatePolynomialMap()
{
	PolynomialMap* polynomialMap = new PolynomialMap();
	countPolynomialVectors++;
	return *polynomialMap;
}

inline Polynomial& CreatePolynomialMap(Number number)
{
	PolynomialMap* polynomialMap = new PolynomialMap(number);
	countPolynomialVectors++;
	return *polynomialMap;
}

inline Polynomial& PolynomialMap::CreatePolynomial()
{
	PolynomialMap* polynomialMap = new PolynomialMap();
	countPolynomialVectors++;
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
		m.insert(PAIR(0, number));
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
		if (pair1.second.IsVerySmallValue() == false)
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
inline MAP PolynomialMap::MapValuesExceptValueOfPolynomialDegree(int degree = -1)
{
	MAP result;
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
		m.insert(PAIR(power, number));
}

inline string PolynomialMap::ToString()
{
	if (IsZero())
		return("Type = 0: Is Zero");

	string result = "Type = 0: ";
	string tmp = "";
	for (auto pair1 : m)
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
					tmp = pair1.second.ToString() + "*x^" + to_string(pair1.first);
			}
			if (tmp[0] != '-' && result != "")
				tmp = "-" + tmp;
			result += tmp;
		}
	}
	return result;
}

inline void PolynomialMap::CleanBeforeDelete()
{
	if (sturm.size() == 0)
		return;
	for (int i = 1; i < sturm.size(); i++)
	{
		cout << "p = " << &sturm[i] << " this = " << this << endl;
		//DeletePolynomial(&sturm[i]);
	}
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
	m.clear();
	for (auto m: p2.m)
	{
		Number copy = m.second.Copy();
		SetNumberValue(m.first, copy);
	}
	inputS = p2.inputS;
	return *this;
}

inline Polynomial& PolynomialMap::operator + (Polynomial& p2)
{
	Polynomial& result = CreatePolynomial();
	result.m = m;
	for (auto pair1 : p2.m)
		result.Add(pair1.first, pair1.second);
	return result;
}

inline Polynomial& PolynomialMap::operator - (Polynomial& p2)
{
	Polynomial& result = CreatePolynomial();
	result.m = m;
	for (auto pair1 : p2.m)
		result.Sub(pair1.first, pair1.second);
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
	{
		DeletePolynomial(&derivative);
		return sturm;
	}
	sturm.push_back(ConvertToPolynomialMapFromPolynomialRef(derivative));
	//PrintStats();
	Polynomial& w = CreatePolynomial();
	Polynomial& q = CreatePolynomial();
	w = *this;
	q = derivative;
	Polynomial& r = w % q;

	while (r.IsZero() == false)
	{
		Polynomial* tmp = &(NegativePolynomial());
		r = *tmp;
		DeletePolynomial(tmp);
		cout << "negative" << endl;
		sturm.push_back(ConvertToPolynomialMapFromPolynomialRef(r));
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
	return sturm;
}

inline Polynomial& PolynomialMap::NegativePolynomial()
{
	Polynomial& result = CreatePolynomial();
	for (auto p : m)
	{
		result.SetNumberValue(p.first, p.second.Neg());
	}
	return result;
}

inline Polynomial& PolynomialMap::Derivative()
{
	Polynomial& result = CreatePolynomial();

	for (auto p : m)
	{
		if (p.first > 0)
			result.SetNumberValue(p.first - 1, p.second * p.first);
	}
	return result;
}

inline Number PolynomialMap::PolynomialValue(Number x)
{
	if (IsZero())
		return Number(0);
	Number result(0);
	for (auto pair1 : m)
	{
		result += CoefficientValue(pair1, x);
	}
	return result;
}
inline pair<Polynomial&, Polynomial&> PolynomialMap::DividePolynomials(Polynomial& p1, Polynomial& p2)
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
	MAP map2 = p2.MapValuesExceptValueOfPolynomialDegree(degree);

	while (currentDegree >= degree)
	{
		PAIR pair1 = PAIR(currentDegree, current.Value(currentDegree));
		MAP map1 = current.MapValuesExceptValueOfPolynomialDegree(currentDegree);

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
	DeletePolynomial(&rest);
	return pair<Polynomial&, Polynomial&>(result, current);
}
