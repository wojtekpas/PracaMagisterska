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
	Number AddAbsolutelyGreaterPositiveAndNegative(Number number1, Number number2);
public:
	Number(int value = 0, bool isNegative = false);
	bool IsPositive();
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

inline Number Number::AddAbsolutelyGreaterPositiveAndNegative(Number number1, Number number2)
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

inline Number::Number(int value = 0, bool isNegative = false)
{
	vectorValues.push_back(abs(value));
	if (value < 0 || isNegative)
		this->isNegative = true;
}

inline bool Number::IsPositive()
{
	return !isNegative;
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
	Number number1 = *this;
	Number number2 = number;
	Number absNumber1 = *this;
	Number absNumber2 = number;
	absNumber1.isNegative = false;
	absNumber2.isNegative = false;
	bool isGreater = absNumber1 > absNumber2;

	if (number1.IsPositive() && number2.IsPositive())
		return AddTwoPositives(number1, number2);
	if (number1.IsNegative() && number2.IsNegative())
	{
		Number result = AddTwoPositives(number1, number2);
		result.isNegative = true;
		return result;
	}
	if (number1.IsPositive())
	{
		if (isGreater)
		{
			return AddAbsolutelyGreaterPositiveAndNegative(number1, number2);
		}
		Number result = AddAbsolutelyGreaterPositiveAndNegative(number2, number1);
		result.isNegative = true;
		return result;
	}
	if (isGreater)
	{
		Number result = AddAbsolutelyGreaterPositiveAndNegative(number1, number2);
		result.isNegative = true;
		return result;
	}
	return AddAbsolutelyGreaterPositiveAndNegative(number2, number1);
}

inline Number Number::operator-(Number number)
{
	number.isNegative = !number.IsNegative();
	return *this + number;
}

inline Number Number::operator*(Number number)
{
	Number result;
	Number number1;
	Number number2;

	for (int i = 0; i <= number1.Size(); i++)
	{
		for (int j = 0; j <= number2.Size(); j++)
		{
			if (i + j >= result.Size())
				result.vectorValues.push_back(0);
			uint64_t value1 = number.vectorValues[i];
			uint64_t value2 = number.vectorValues[j];
			uint64_t tmp = value1 * value2;
			int value = tmp % MAX_VALUE;
			int carry = tmp / MAX_VALUE;
			result.vectorValues[i + j] += value;
			if (carry)
			{
				if (i + j + 1 >= result.Size())
					result.vectorValues.push_back(0);
				result.vectorValues[i + j + 1] += carry;
			}
		}
	}
	return result;
}

inline Number Number::operator/(Number number)
{
	
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

inline string Number::ToString()
{
	return "empty";
}