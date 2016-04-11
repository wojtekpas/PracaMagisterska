#pragma onceNumber
#include "definitions.h"

#define MAX_VALUE 65536
#define MAX_VALUE_NUMBER_OF_BITS 16
#include "Number.h"

class Fraction
{
private:
	Number counter;
	Number denominator;
	bool isNegative = false;
	int Equal(Fraction fraction1, Fraction fraction2);
	Number CommonDenominator(Fraction fraction1, Fraction fraction2);
	Fraction AddTwoPositives(Fraction fraction1, Fraction fraction2);
	Fraction AddAbsolutelyGreaterPositiveAndNegative(Fraction fraction1, Fraction fraction2);
	Fraction Mul(Number counter1, Number denominator1, Number counter2, Number denominator2);
public:
	explicit Fraction(Number number, bool isNegative = false);
	explicit Fraction(int value = 0, bool isNegative = false);
	bool IsPositive();
	bool IsNegative();
	bool operator == (Fraction fraction);
	bool operator != (Fraction fraction);
	bool operator > (Fraction fraction);
	bool operator < (Fraction fraction);
	bool operator >= (Fraction fraction);
	bool operator <= (Fraction fraction);
	Fraction operator = (Fraction fraction);
	Fraction operator + (Fraction fraction);
	Fraction operator - (Fraction fraction);
	Fraction operator * (Fraction fraction);
	Fraction operator / (Fraction fraction);
	Fraction operator ^ (int power);
	Fraction operator += (Fraction fraction);
	Fraction operator -= (Fraction fraction);
	Fraction operator *= (Fraction fraction);
	Fraction operator /= (Fraction fraction);
	Fraction operator ^= (int power);
	Fraction operator = (Number number);
	Fraction operator = (int number);
	string ToString();

};

inline int Fraction::Equal(Fraction fraction1, Fraction fraction2)
{
	if (fraction1.IsNegative() == false && fraction2.IsNegative())
		return 1;

	if (fraction1.IsNegative() && fraction2.IsNegative() == false)
		return -1;

	int sign = 1;

	if (fraction1.IsNegative())
		sign = -1;

	Fraction result = fraction1 / fraction2;

	if (result.counter == result.denominator)
		return 0;

	return sign * (result.counter > result.denominator);
}

inline Number Fraction::CommonDenominator(Fraction fraction1, Fraction fraction2)
{
	return fraction1.denominator.NWW(fraction2.denominator);
}

inline Fraction Fraction::AddTwoPositives(Fraction fraction1, Fraction fraction2)
{
	Fraction result;
	Number commonDenominator = CommonDenominator(fraction1, fraction2);
	Number factor1(commonDenominator/fraction1.denominator);
	Number factor2(commonDenominator/fraction2.denominator);

	result.counter = fraction1.counter * factor1 + fraction2.counter * factor2;
	result.denominator = commonDenominator;

	if(result.counter.IsNegative())
	{
		result.counter.SetSign(false);
		result.isNegative = true;
	}

	return result;
}

inline Fraction Fraction::Mul(Number counter1, Number denominator1, Number counter2, Number denominator2)
{
	Fraction result(1);

	result.counter = counter1 * counter2;
	result.denominator = denominator1 * denominator2;

	return result;
}

inline Fraction::Fraction(Number number, bool isNegative)
{
	counter = number;
	denominator = 1;
	this->isNegative = number.IsNegative();
}

inline Fraction::Fraction(int value = 0, bool isNegative = false)
{
	Number number(value);
	Fraction(number, isNegative);
}

inline bool Fraction::IsPositive()
{
	return !isNegative;
}

inline bool Fraction::IsNegative()
{
	return isNegative;
}


inline bool Fraction::operator==(Fraction fraction)
{
	return Equal(*this, fraction) == 0;
}

inline bool Fraction::operator!=(Fraction fraction)
{
	return Equal(*this, fraction) != 0;
}

inline bool Fraction::operator>(Fraction fraction)
{
	return Equal(*this, fraction) > 0;
}

inline bool Fraction::operator<(Fraction fraction)
{
	return Equal(*this, fraction) < 0;
}

inline bool Fraction::operator>=(Fraction fraction)
{
	return Equal(*this, fraction) >= 0;
}

inline bool Fraction::operator<=(Fraction fraction)
{
	return Equal(*this, fraction) <= 0;
}

inline Fraction Fraction::operator=(Fraction fraction)
{
	counter = fraction.counter;
	denominator = denominator;
	isNegative = isNegative;
	return *this;
}

inline Fraction Fraction::operator+(Fraction fraction)
{
	Fraction fraction1 = *this;
	Fraction fraction2 = fraction;
	Fraction absFraction1 = *this;
	Fraction absFraction2 = fraction;
	absFraction1.isNegative = false;
	absFraction2.isNegative = false;
	bool isGreater = absFraction1 > absFraction2;

	if (fraction1.IsPositive() && fraction2.IsPositive())
		return AddTwoPositives(fraction1, fraction2);
	if (fraction1.IsNegative() && fraction2.IsNegative())
	{
		Fraction result = AddTwoPositives(fraction1, fraction2);
		result.isNegative = true;
		return result;
	}
	if (fraction1.IsPositive())
	{
		if (isGreater)
		{
			return AddAbsolutelyGreaterPositiveAndNegative(fraction1, fraction2);
		}
		Fraction result = AddAbsolutelyGreaterPositiveAndNegative(fraction2, fraction1);
		result.isNegative = true;
		return result;
	}
	if (isGreater)
	{
		Fraction result = AddAbsolutelyGreaterPositiveAndNegative(fraction1, fraction2);
		result.isNegative = true;
		return result;
	}
	return AddAbsolutelyGreaterPositiveAndNegative(fraction2, fraction1);
}

inline Fraction Fraction::operator-(Fraction fraction)
{
	fraction.isNegative = !fraction.IsNegative();
	return *this + fraction;
}

inline Fraction Fraction::operator*(Fraction fraction)
{
	Fraction result = Mul(counter, denominator, fraction.counter, fraction.denominator);
	result.isNegative = IsNegative() ^ fraction.IsNegative();
	return result;
}

inline Fraction Fraction::operator/(Fraction fraction)
{
	Fraction result = Mul(counter, denominator, fraction.denominator, fraction.counter);
	result.isNegative = IsNegative() ^ fraction.IsNegative();
	return result;
}

inline Fraction Fraction::operator^(int power)
{
	if (power == 0)
	{
		Fraction result(1);
		return result;
	}
	Fraction result = *this;
	for (int i = 1; i < power; i++)
	{
		result *= *this;
	}
	return result;
}

inline Fraction Fraction::operator+=(Fraction fraction)
{
	*this = *this + fraction;
	return *this;
}

inline Fraction Fraction::operator-=(Fraction fraction)
{
	*this = *this - fraction;
	return *this;
}

inline Fraction Fraction::operator*=(Fraction fraction)
{
	*this = *this * fraction;
	return *this;
}

inline Fraction Fraction::operator/=(Fraction fraction)
{
	*this = *this / fraction;
	return *this;
}

inline Fraction Fraction::operator^=(int power)
{
	*this = *this ^ power;
	return *this;
}

inline Fraction Fraction::operator=(Number number)
{
	counter = number;
	denominator = 1;
	isNegative = number.IsNegative();
	return *this;
}

inline Fraction Fraction::operator=(int value)
{
	Number number(value);
	*this = number;
	return *this;
}

inline string Fraction::ToString()
{
	return "empty";
}