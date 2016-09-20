#pragma once
#include "definitions.h"
#include <mpir.h>

#define MAX_VALUE 100000000
#define MAX_NEGATIVE_VALUE -1000000000

static int countNumbers = 0;
static int countNumbers2 = 0;
static int countNumbers3 = 0;
static int countNumbersDeleted = 0;
static int countNumbersDeleted2 = 0;

class Number
{
public:
	mpq_t value;
	explicit Number();
	explicit Number(double value);
	Number(const Number &bigNumber);
	~Number();
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

Number SMALL_VALUE;

bool IsSmallValue(Number value)
{
	return value <= SMALL_VALUE;
}

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

inline int VectorsAreEqual(vector<Number>v1, vector<Number>v2)
{
	if (v1.size() != v2.size())
		return 0;

	for (int i = 0; i < v1.size(); i++)
	{
		Number diff;
		diff = v1[i] - v2[i];
		if (IsSmallValue(diff.Abs()) == false)
			return 0;
	}
	return 1;
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

inline Number::Number(const Number& bigNumber)
{
	mpq_init(value);
	mpq_set(value, bigNumber.value);
}

inline Number::~Number()
{
	countNumbersDeleted2++;
	//mpq_init(value);
	//cout << value << endl;
	//cout << "ptr = " << &value << endl;
	mpq_clear(value);
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
	return IsSmallValue(Abs());
}

inline bool Number::IsZero()
{
	return IsSmallValue(Abs());
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
	return mpq_equal(value, bigNumber.value) != 0;
}

inline bool Number::operator!=(Number bigNumber)
{
	return mpq_equal(value, bigNumber.value) == 0;
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
	countNumbers3++;
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
	countNumbers3++;
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
	char* charArray = new char[100000];
	int neededSize = mpz_sizeinbase(mpq_numref(value), 10) + mpz_sizeinbase(mpq_denref(value), 10) + 3;
	if (neededSize > 100000)
	{
		printf("To small buffer - needed size = %d", neededSize);
		return " ";
	}
	mpq_get_str(charArray, 10, value);
	string result(charArray);
	int isSlash = StringManager::FindFirst(result, CharsConstants::Div);
	if (isSlash < 0)
		return result;

	mpz_t counter;
	mpz_t denominator;
	mpz_init(counter);
	mpz_init(denominator);
	mpq_get_num(counter, value);
	mpq_get_den(denominator, value);
	mpz_t precision;
	mpz_init(precision);
	int dec_precision = 100000;
	mpz_set_d(precision, dec_precision);
	mpz_t res;
	mpz_t fract;
	mpz_init(res);
	mpz_init(fract);

	mpz_mul(res, counter, precision);
	mpz_div(res, res, denominator);

	result = "";
	if (mpz_cmp_d(res, 0) < 0)
	{
		mpz_mul_si(res, res, -1);
		result = "-";
	}

	mpz_mod(fract, res, precision);
	mpz_div(res, res, precision);

	mpz_get_str(charArray, 10, res);
	result = result + string(charArray);
	if (mpz_cmp_d(fract, 0) > 0)
	{
		result = result + ".";
		int tmp = dec_precision;
		while (tmp > 1)
		{
			tmp /= 10;
			if (mpz_cmp_d(fract, tmp) < 0)
				result = result + "0";
		}
		mpz_get_str(charArray, 10, fract);
		result = result + string(charArray);
		while (true)
		{
			char lastChar = StringManager::ReturnLastChar(result);
			if (lastChar != '0')
				break;
			result = StringManager::Substr(result, 0, result.size() - 2);
		}
	}

	mpz_clear(counter);
	mpz_clear(denominator);
	mpz_clear(precision);
	mpz_clear(res);
	mpz_clear(fract);
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

