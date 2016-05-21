#pragma once
#include "definitions.h"
#include <mpir.h>

#define DEBUG_VALUE 0
#define DEBUG if (DEBUG_VALUE) 
#define SMALL_NUMBER 0.00001
#define MAX_VALUE 1000
#define MAX_NEGATIVE_VALUE -1000

class BigNumber
{
public:
	mpq_t value;
	explicit BigNumber();
	explicit BigNumber(double value);
	BigNumber Abs();
	void SetMaxNegativeValue();
	void SetMaxValue();
	bool IsPlusInfinity();
	bool IsMinusInfinity();
	bool IsInfinity();
	bool IsVerySmallValue();
	bool IsZero();
	bool IsInVector(vector<BigNumber> v);

	bool operator == (BigNumber bigNumber);
	bool operator != (BigNumber bigNumber);
	bool operator > (BigNumber bigNumber);
	bool operator < (BigNumber bigNumber);
	bool operator >= (BigNumber bigNumber);
	bool operator <= (BigNumber bigNumber);
	BigNumber operator = (BigNumber bigNumber);
	BigNumber operator + (BigNumber bigNumber);
	BigNumber operator - (BigNumber bigNumber);
	BigNumber operator * (BigNumber bigNumber);
	BigNumber operator / (BigNumber bigNumber);
	BigNumber operator ^ (int power);
	BigNumber operator += (BigNumber bigNumber);
	BigNumber operator -= (BigNumber bigNumber);
	BigNumber operator *= (BigNumber bigNumber);
	BigNumber operator /= (BigNumber bigNumber);
	BigNumber operator ^= (int power);
	bool operator == (double value);
	bool operator != (double value);
	bool operator > (double value);
	bool operator < (double value);
	bool operator >= (double value);
	bool operator <= (double value);
	BigNumber operator = (double value);
	BigNumber operator + (double value);
	BigNumber operator - (double value);
	BigNumber operator * (double value);
	BigNumber operator / (double value);
	BigNumber operator += (double value);
	BigNumber operator -= (double value);
	BigNumber operator *= (double value);
	BigNumber operator /= (double value);
	string ToString();
	void Print();
};

inline BigNumber::BigNumber()
{
	mpq_init(value);
}

inline BigNumber::BigNumber(double value)
{
	mpq_init(this->value);
	mpq_set_d(this->value, value);
}

inline BigNumber BigNumber::Abs()
{
	BigNumber result;
	mpq_abs(result.value, value);
	return result;
}

inline void BigNumber::SetMaxNegativeValue()
{
	*this = MAX_NEGATIVE_VALUE;
}

inline void BigNumber::SetMaxValue()
{
	*this = MAX_VALUE;
}

inline bool BigNumber::IsPlusInfinity()
{
	return *this >= MAX_VALUE;
}

inline bool BigNumber::IsMinusInfinity()
{
	return *this <= MAX_NEGATIVE_VALUE;
}

inline bool BigNumber::IsInfinity()
{
	return IsMinusInfinity() || IsPlusInfinity();
}

inline bool BigNumber::IsVerySmallValue()
{
	return Abs() < SMALL_NUMBER * 200;
}

inline bool BigNumber::IsZero()
{
	return Abs() < SMALL_NUMBER;
}

inline bool BigNumber::IsInVector(vector<BigNumber> v)
{
	for (int i = 0; i < v.size(); i++)
	{
		BigNumber interval = v[i] - *this;
		if (interval.IsVerySmallValue())
			return true;
	}
	return false;
}

inline bool BigNumber::operator==(BigNumber bigNumber)
{
	return mpq_cmp(value, bigNumber.value) == 0;
}

inline bool BigNumber::operator!=(BigNumber bigNumber)
{
	return mpq_cmp(value, bigNumber.value);
}

inline bool BigNumber::operator>(BigNumber bigNumber)
{
	return mpq_cmp(value, bigNumber.value) > 0;
}

inline bool BigNumber::operator<(BigNumber bigNumber)
{
	return mpq_cmp(value, bigNumber.value) < 0;
}

inline bool BigNumber::operator>=(BigNumber bigNumber)
{
	return mpq_cmp(value, bigNumber.value) >= 0;
}

inline bool BigNumber::operator<=(BigNumber bigNumber)
{
	return mpq_cmp(value, bigNumber.value) <= 0;
}

inline BigNumber BigNumber::operator=(BigNumber bigNumber)
{
	mpq_set(value, bigNumber.value);
	return *this;
}

inline BigNumber BigNumber::operator+(BigNumber bigNumber)
{
	BigNumber result(0);
	mpq_add(result.value, value, bigNumber.value);
	return result;
}

inline BigNumber BigNumber::operator-(BigNumber bigNumber)
{
	BigNumber result(0);
	mpq_sub(result.value, value, bigNumber.value);
	return result;
}

inline BigNumber BigNumber::operator*(BigNumber bigNumber)
{
	BigNumber result(0);
	mpq_mul(result.value, value, bigNumber.value);
	return result;
}

inline BigNumber BigNumber::operator/(BigNumber bigNumber)
{
	BigNumber result(0);
	mpq_div(result.value, value, bigNumber.value);
	return result;
}

inline BigNumber BigNumber::operator^(int power)
{
	if (power == 0)
	{
		BigNumber result(1);
		return result;
	}
	BigNumber result = *this;
	for (int i = 1; i < power; i++)
	{
		result *= *this;
	}
	return result;
}

inline BigNumber BigNumber::operator+=(BigNumber bigNumber)
{
	*this = *this + bigNumber;
	return *this;
}

inline BigNumber BigNumber::operator-=(BigNumber bigNumber)
{
	*this = *this - bigNumber;
	return *this;
}

inline BigNumber BigNumber::operator*=(BigNumber bigNumber)
{
	*this = *this * bigNumber;
	return *this;
}

inline BigNumber BigNumber::operator/=(BigNumber bigNumber)
{
	*this = *this / bigNumber;
	return *this;
}

inline BigNumber BigNumber::operator^=(int power)
{
	*this = *this ^ power;
	return *this;
}

inline bool BigNumber::operator==(double value)
{
	BigNumber bigNumber(value);
	return *this == bigNumber;
}

inline bool BigNumber::operator!=(double value)
{
	BigNumber bigNumber(value);
	return *this != bigNumber;
}

inline bool BigNumber::operator>(double value)
{
	BigNumber bigNumber(value);
	return *this > bigNumber;
}

inline bool BigNumber::operator<(double value)
{
	BigNumber bigNumber(value);
	return *this < bigNumber;
}

inline bool BigNumber::operator>=(double value)
{
	BigNumber bigNumber(value);
	return *this >= bigNumber;
}

inline bool BigNumber::operator<=(double value)
{
	BigNumber bigNumber(value);
	return *this <= bigNumber;
}

inline BigNumber BigNumber::operator=(double value)
{
	mpq_set_d(this->value, value);
	return *this;
}

inline BigNumber BigNumber::operator+(double value)
{
	BigNumber bigNumber(value);
	return *this + bigNumber;
}

inline BigNumber BigNumber::operator-(double value)
{
	BigNumber bigNumber(value);
	return *this - bigNumber;
}

inline BigNumber BigNumber::operator*(double value)
{
	BigNumber bigNumber(value);
	return *this * bigNumber;
}

inline BigNumber BigNumber::operator/(double value)
{
	BigNumber bigNumber(value);
	return *this / bigNumber;
}

inline BigNumber BigNumber::operator+=(double value)
{
	*this = *this + value;
	return *this;
}

inline BigNumber BigNumber::operator-=(double value)
{
	*this = *this - value;
	return *this;
}

inline BigNumber BigNumber::operator*=(double value)
{
	*this = *this * value;
	return *this;
}

inline BigNumber BigNumber::operator/=(double value)
{
	*this = *this / value;
	return *this;
}

inline string BigNumber::ToString()
{
	return to_string(1);
}

inline void BigNumber::Print()
{
	cout << value << endl;
}
