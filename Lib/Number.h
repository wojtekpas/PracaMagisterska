#pragma once
#include "definitions.h"

#define MAX_VALUE 65536
#define MAX_VALUE_NUMBER_OF_BITS 16

class Number
{
private:
	vector<int>vectorValues;
	bool isNegative = false;
	int Equal(Number number1, Number number2);
	Number AddTwoPositives(Number number1, Number number2);
	Number AddGreaterPositiveAndNegative(Number number1, Number number2);
public:
	bool IsNegative();
	int NumberOfTheHighestBit(int position = 0);
	int Size();
	int SizeInBits();
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
	string ToString();

};

inline int Number::Equal(Number number1, Number number2)
{
	if (IsNegative() == false && number2.IsNegative())
		return 1;

	if (IsNegative() && number2.IsNegative() == false)
		return -1;

	int sign = 1;

	if (IsNegative())
		sign = -1;

	if (SizeInBits() != number2.SizeInBits())
	{
		if (SizeInBits() > number2.SizeInBits())
			return sign;
		return -sign;
	}

	for (int i = Size() - 1; i >= 0; i++)
	{
		if (vectorValues[i] != number2.vectorValues[i])
		{
			if (vectorValues[i] > number2.vectorValues[i])
				return sign;
			return -sign;
		}
	}
	return 0;
}

inline Number Number::AddTwoPositives(Number number1, Number number2)
{
	int size1 = number1.Size();
	int size2 = number2.Size();
	Number result;

	for (int i = 0; i < max(size1, size2); i++)
	{
		int tmp = 0;
		if (number1.Size() > i)
			tmp += number1.vectorValues[i];
		if (number2.Size() > i)
			tmp += number2.vectorValues[i];
		int value = tmp % MAX_VALUE;

		if (result.Size() <= i)
			result.vectorValues.push_back(0);		
		result.vectorValues[i] += value;

		int carryBit = result.vectorValues[i] / MAX_VALUE;
		if (carryBit)
			result.vectorValues.push_back(1);
	}
	return result;
}

inline Number Number::AddGreaterPositiveAndNegative(Number number1, Number number2)
{
	int size1 = number1.Size();
	int size2 = number2.Size();
	Number result = number1;
	int carryBit = 0;

	for (int i = 0; i < size2; i++)
	{
		int currentValue = number1.vectorValues[i] - number2.vectorValues[i] - carryBit;
		if (currentValue < 0)
		{
			currentValue += MAX_VALUE;
			carryBit = 1;
		}
		else
		{
			carryBit = 0;
		}
		number1.vectorValues[i] = currentValue;
	}
	for (int i = size2; i < size1; i++)
	{
		if (carryBit == 0)
			break;
		number1.vectorValues[i]--;
		if (number1.vectorValues[i] >= 0)
		{
			number1.vectorValues[i] += MAX_VALUE;
		}
		else
		{
			break;
		}
	}

	for (int i = size1; i > 0; i--)
	{
		if (number1.vectorValues[i] == 0)
			number1.vectorValues.pop_back();
	}
	return result;
}

inline bool Number::IsNegative()
{
	return isNegative;
}

inline int Number::NumberOfTheHighestBit(int position = 0)
{
	int value = vectorValues[position];
	int result = 0;

	while(true)
	{
		int mask = 1 << result;
		if (value & mask)
			return result;
		result++;
	}
}

inline int Number::Size()
{
	return vectorValues.size();
}

inline int Number::SizeInBits()
{
	int size = Size();
	if (size == 0)
		return 0;

	return MAX_VALUE_NUMBER_OF_BITS * (size - 1) + NumberOfTheHighestBit(size - 1);
}

inline bool Number::operator==(Number number)
{
	return Equal(*this, number) == 0;
}

inline bool Number::operator!=(Number number)
{
	return Equal(*this, number) != 0;
}

inline bool Number::operator>(Number number)
{
	return Equal(*this, number) > 0;
}

inline bool Number::operator<(Number number)
{
	return Equal(*this, number) < 0;
}

inline bool Number::operator>=(Number number)
{
	return Equal(*this, number) >= 0;
}

inline bool Number::operator<=(Number number)
{
	return Equal(*this, number) <= 0;
}

inline Number Number::operator=(Number number)
{
	vectorValues = number.vectorValues;
	isNegative = isNegative;
	return *this;
}

inline Number Number::operator+(Number number)
{
	int size1 = Size();
	int size2 = number.Size();

	for (int i = 0; i < min(size1, size2); i++)
	{
		if (vectorValues[i] != number.vectorValues[i])
			return *this;
	}
}

inline Number Number::operator-(Number number)
{
}

inline Number Number::operator*(Number number)
{
}

inline Number Number::operator/(Number number)
{
	
}

inline Number Number::operator^(int power)
{
	Number result;
	if (power == 0)
	{
		return result;
	}
}

inline Number Number::operator+=(Number number)
{
}

inline Number Number::operator-=(Number number)
{
}

inline Number Number::operator*=(Number number)
{
}

inline Number Number::operator/=(Number number)
{
}

inline Number Number::operator^=(int power)
{
}

inline string Number::ToString()
{
}