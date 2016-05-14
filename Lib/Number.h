#pragma once
#include "definitions.h"

#define DEBUG_VALUE 0
#define DEBUG if (DEBUG_VALUE) 
#define SMALL_NUMBER 0.00001
#define MAX_VALUE 1000
#define MAX_NEGATIVE_VALUE -1000

class Number
{
private:
	double value = 0;
public:
	explicit Number();
	explicit Number(double value);
	double GetValue();
	double Abs();
	void SetMaxNegativeValue();
	void SetMaxValue();
	bool IsPlusInfinity();
	bool IsMinusInfinity();
	bool IsInfinity();
	bool IsVerySmallValue();
	bool IsZero();
	bool IsInVector(vector<Number> v);

	bool operator == (Number number);
	bool operator != (Number number);
	bool operator > (Number number);
	bool operator < (Number number);
	bool operator >= (Number number);
	bool operator <= (Number number);
	Number operator = (Number number);
	Number operator + (Number number);
	Number operator - (Number number);
	Number operator * (Number number);
	Number operator / (Number number);
	Number operator ^ (int power);
	Number operator += (Number number);
	Number operator -= (Number number);
	Number operator *= (Number number);
	Number operator /= (Number number);
	Number operator ^= (int power);
	bool operator == (int value);
	bool operator != (int value);
	bool operator > (int value);
	bool operator < (int value);
	bool operator >= (int value);
	bool operator <= (int value);
	Number operator = (int value);
	Number operator + (int value);
	Number operator - (int value);
	Number operator * (int value);
	Number operator / (int value);
	Number operator += (int value);
	Number operator -= (int value);
	Number operator *= (int value);
	Number operator /= (int value);
	string ToString();
	void Print();
};

inline Number::Number()
{
}

inline Number::Number(double value)
{
	this->value = value;
}

inline double Number::GetValue()
{
	return value;
}

inline double Number::Abs()
{
	return abs(value);
}

inline void Number::SetMaxNegativeValue()
{
	value = MAX_NEGATIVE_VALUE;
}

inline void Number::SetMaxValue()
{
	value = MAX_VALUE;
}

inline bool Number::IsPlusInfinity()
{
	return value == MAX_NEGATIVE_VALUE;
}

inline bool Number::IsMinusInfinity()
{
	return value == MAX_VALUE;
}

inline bool Number::IsInfinity()
{
	return IsMinusInfinity() || IsPlusInfinity();
}

inline bool Number::IsVerySmallValue()
{
	return Abs() / 200 < SMALL_NUMBER;
}

inline bool Number::IsZero()
{
	return Abs() < SMALL_NUMBER;
}

inline bool Number::IsInVector(vector<Number> v)
{
	for (int i = 0; i < v.size(); i++)
	{
		Number interval = v[i] - *this;
		if (interval.IsVerySmallValue())
			return true;
	}
	return false;
}

inline bool Number::operator==(Number number)
{
	return value == number.GetValue();
}

inline bool Number::operator!=(Number number)
{
	return value != number.GetValue();
}

inline bool Number::operator>(Number number)
{
	return value > number.GetValue();
}

inline bool Number::operator<(Number number)
{
	return value < number.GetValue();
}

inline bool Number::operator>=(Number number)
{
	return value >= number.GetValue();
}

inline bool Number::operator<=(Number number)
{
	return value <= number.GetValue();
}

inline Number Number::operator=(Number number)
{
	value = number.GetValue();
	return *this;
}

inline Number Number::operator+(Number number)
{
	Number result(0);
	result.value = value + number.GetValue();
	return result;
}

inline Number Number::operator-(Number number)
{
	Number result(0);
	result.value = value - number.GetValue();
	return result;
}

inline Number Number::operator*(Number number)
{
	Number result(0);
	result.value = value * number.GetValue();
	return result;
}

inline Number Number::operator/(Number number)
{
	Number result(0);
	result.value = value / number.GetValue();
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

inline Number Number::operator+=(Number number)
{
	*this = *this + number;
	return *this;
}

inline Number Number::operator-=(Number number)
{
	*this = *this - number;
	return *this;
}

inline Number Number::operator*=(Number number)
{
	*this = *this * number;
	return *this;
}

inline Number Number::operator/=(Number number)
{
	*this = *this / number;
	return *this;
}

inline Number Number::operator^=(int power)
{
	*this = *this ^ power;
	return *this;
}

inline bool Number::operator==(int value)
{
	Number number(value);
	return *this == number;
}

inline bool Number::operator!=(int value)
{
	Number number(value);
	return *this != number;
}

inline bool Number::operator>(int value)
{
	Number number(value);
	return *this > number;
}

inline bool Number::operator<(int value)
{
	Number number(value);
	return *this < number;
}

inline bool Number::operator>=(int value)
{
	Number number(value);
	return *this >= number;
}

inline bool Number::operator<=(int value)
{
	Number number(value);
	return *this <= number;
}

inline Number Number::operator=(int value)
{
	this->value = value;
	return *this;
}

inline Number Number::operator+(int value)
{
	Number number(value);
	return *this + number;
}

inline Number Number::operator-(int value)
{
	Number number(value);
	return *this - number;
}

inline Number Number::operator*(int value)
{
	Number number(value);
	return *this * number;
}

inline Number Number::operator/(int value)
{
	Number number(value);
	return *this / number;
}

inline Number Number::operator+=(int value)
{
	*this = *this + value;
	return *this;
}

inline Number Number::operator-=(int value)
{
	*this = *this - value;
	return *this;
}

inline Number Number::operator*=(int value)
{
	*this = *this * value;
	return *this;
}

inline Number Number::operator/=(int value)
{
	*this = *this / value;
	return *this;
}

inline string Number::ToString()
{
	string s = to_string(value);
	return to_string(value);
}

inline void Number::Print()
{
	cout << value << endl;
}
