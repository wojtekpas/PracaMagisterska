#pragma once
#include "definitions.h"
#include <mpir.h>

#define SMALL_NUMBER 0.000000000001
#define MAX_VALUE 1000
#define MAX_NEGATIVE_VALUE -1000

static int countNumbers = 0;
static int countNumbers2 = 0;
static int countNumbersDeleted = 0;

class Number
{
public:
	mpq_t value;
	explicit Number();
	explicit Number(double value);
	Number Neg();
	Number Abs();
	Number Copy();
	void SetMaxNegativeValue();
	void SetMaxValue();
	bool IsPlusInfinity();
	bool IsMinusInfinity();
	bool IsInfinity();
	bool IsVerySmallValue();
	bool IsZero();
	int IsInVector(vector<Number> v);

	bool operator == (Number bigNumber);
	bool operator != (Number bigNumber);
	bool operator > (Number bigNumber);
	bool operator < (Number bigNumber);
	bool operator >= (Number bigNumber);
	bool operator <= (Number bigNumber);
	Number operator = (Number bigNumber);
	Number operator + (Number bigNumber);
	Number operator - (Number bigNumber);
	Number operator * (Number bigNumber);
	Number operator / (Number bigNumber);
	Number operator ^ (int power);
	Number operator += (Number bigNumber);
	Number operator -= (Number bigNumber);
	Number operator *= (Number bigNumber);
	Number operator /= (Number bigNumber);
	Number operator ^= (int power);
	bool operator == (double value);
	bool operator != (double value);
	bool operator > (double value);
	bool operator < (double value);
	bool operator >= (double value);
	bool operator <= (double value);
	Number operator = (double value);
	Number operator + (double value);
	Number operator - (double value);
	Number operator * (double value);
	Number operator / (double value);
	Number operator += (double value);
	Number operator -= (double value);
	Number operator *= (double value);
	Number operator /= (double value);
	string ToString();
	void Print();
};

inline void DeleteNumber(Number* number)
{
	countNumbersDeleted++;
	mpq_clear(number->value);
}

inline vector<Number> SortNumbers(vector<Number>v)
{
	vector<Number> result = v;
	for (int i = 0; i < result.size() - 1; i++)
	{
		for (int j = i + 1; j < result.size(); j++)
		{
			if (result[i] > result[j])
			{
				Number copy = result[i].Copy();
				result[i] = result[j];
				result[j] = copy;
			}
		}
	}
	return result;
}

inline Number::Number()
{
	countNumbers++;
	mpq_init(value);
}

inline Number::Number(double value)
{
	countNumbers2++;
	mpq_init(this->value);
	mpq_set_d(this->value, value);
}

inline Number Number::Neg()
{
	Number result;
	mpq_neg(result.value, value);
	return result;
}

inline Number Number::Abs()
{
	Number result;
	mpq_abs(result.value, value);
	return result;
}

inline Number Number::Copy()
{
	Number result;
	mpq_set(result.value, value);
	return result;
}

inline void Number::SetMaxNegativeValue()
{
	*this = MAX_NEGATIVE_VALUE;
}

inline void Number::SetMaxValue()
{
	*this = MAX_VALUE;
}

inline bool Number::IsPlusInfinity()
{
	return *this >= MAX_VALUE;
}

inline bool Number::IsMinusInfinity()
{
	return *this <= MAX_NEGATIVE_VALUE;
}

inline bool Number::IsInfinity()
{
	return IsMinusInfinity() || IsPlusInfinity();
}

inline bool Number::IsVerySmallValue()
{
	return Abs() < SMALL_NUMBER * 200;
}

inline bool Number::IsZero()
{
	return Abs() < SMALL_NUMBER;
}

inline int Number::IsInVector(vector<Number> v)
{
	for (int i = 0; i < v.size(); i++)
	{
		Number interval = v[i] - *this;
		if (interval.IsVerySmallValue())
			return i;
	}
	return -1;
}

inline bool Number::operator==(Number bigNumber)
{
	return mpq_cmp(value, bigNumber.value) == 0;
}

inline bool Number::operator!=(Number bigNumber)
{
	return mpq_cmp(value, bigNumber.value) != 0;
}

inline bool Number::operator>(Number bigNumber)
{
	return mpq_cmp(value, bigNumber.value) > 0;
}

inline bool Number::operator<(Number bigNumber)
{
	return mpq_cmp(value, bigNumber.value) < 0;
}

inline bool Number::operator>=(Number bigNumber)
{
	return mpq_cmp(value, bigNumber.value) >= 0;
}

inline bool Number::operator<=(Number bigNumber)
{
	return mpq_cmp(value, bigNumber.value) <= 0;
}

inline Number Number::operator=(Number bigNumber)
{
	mpq_set(value, bigNumber.value);
	return *this;
}

inline Number Number::operator+(Number bigNumber)
{
	Number result(0);
	mpq_add(result.value, value, bigNumber.value);
	return result;
}

inline Number Number::operator-(Number bigNumber)
{
	Number result(0);
	mpq_sub(result.value, value, bigNumber.value);
	return result;
}

inline Number Number::operator*(Number bigNumber)
{
	Number result(0);
	mpq_mul(result.value, value, bigNumber.value);
	return result;
}

inline Number Number::operator/(Number bigNumber)
{
	Number result(0);
	mpq_div(result.value, value, bigNumber.value);
	return result;
}

inline Number Number::operator^(int power)
{
	if (power == 0)
	{
		Number result(1);
		return result;
	}
	Number result = *this;
	for (int i = 1; i < power; i++)
	{
		result *= *this;
	}
	return result;
}

inline Number Number::operator+=(Number bigNumber)
{
	*this = *this + bigNumber;
	return *this;
}

inline Number Number::operator-=(Number bigNumber)
{
	*this = *this - bigNumber;
	return *this;
}

inline Number Number::operator*=(Number bigNumber)
{
	*this = *this * bigNumber;
	return *this;
}

inline Number Number::operator/=(Number bigNumber)
{
	*this = *this / bigNumber;
	return *this;
}

inline Number Number::operator^=(int power)
{
	*this = *this ^ power;
	return *this;
}

inline bool Number::operator==(double value)
{
	Number bigNumber(value);
	return *this == bigNumber;
}

inline bool Number::operator!=(double value)
{
	Number bigNumber(value);
	return *this != bigNumber;
}

inline bool Number::operator>(double value)
{
	Number bigNumber(value);
	return *this > bigNumber;
}

inline bool Number::operator<(double value)
{
	Number bigNumber(value);
	return *this < bigNumber;
}

inline bool Number::operator>=(double value)
{
	Number bigNumber(value);
	return *this >= bigNumber;
}

inline bool Number::operator<=(double value)
{
	Number bigNumber(value);
	return *this <= bigNumber;
}

inline Number Number::operator=(double value)
{
	mpq_set_d(this->value, value);
	return *this;
}

inline Number Number::operator+(double value)
{
	Number bigNumber(value);
	return *this + bigNumber;
}

inline Number Number::operator-(double value)
{
	Number bigNumber(value);
	return *this - bigNumber;
}

inline Number Number::operator*(double value)
{
	Number bigNumber(value);
	return *this * bigNumber;
}

inline Number Number::operator/(double value)
{
	Number bigNumber(value);
	return *this / bigNumber;
}

inline Number Number::operator+=(double value)
{
	*this = *this + value;
	return *this;
}

inline Number Number::operator-=(double value)
{
	*this = *this - value;
	return *this;
}

inline Number Number::operator*=(double value)
{
	*this = *this * value;
	return *this;
}

inline Number Number::operator/=(double value)
{
	*this = *this / value;
	return *this;
}

inline string Number::ToString()
{
	char* charArray = new char[100];
	mpq_get_str(charArray, 10, value);
	string result(charArray);
	//if (value->_mp_num._mp_d == value->_mp_den._mp_d + 1)

	return result;
}

inline void Number::Print()
{
	cout << ToString() << endl;
}

static Number zero(0);
static Number one(1);
static Number two(2);
static Number oneNeg(-1);
static Number twoNeg(-2);

