#pragma once
#include "definitions.h"
#include <mpir.h>
#include <chrono>

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
	bool IsWithRequiredPrecision();
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
	string MakeNice(string result);
	string RoundNine(string result);
	string TruncateZero(string result);
	void Print(int newLine = 1);
};

static Number PRECISION_VALUE;
static Number SMALL_VALUE;
static Number MAX_VALUE;
static Number MAX_NEGATIVE_VALUE;
static int PRECISION_INT;
static Number DEC_PRECISION;

inline bool IsSmallValue(Number value)
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
	if (v.size() == 0)
		return v;
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

inline bool Number::IsWithRequiredPrecision()
{
	return *this <= PRECISION_VALUE;
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
	mpz_t ten;
	mpz_init(counter);
	mpz_init(denominator);
	mpz_init(ten);
	mpq_get_num(counter, value);
	mpq_get_den(denominator, value);
	mpz_t precision;
	mpz_init(precision);
	mpq_get_num(precision, DEC_PRECISION.value);
	mpz_t res;
	mpz_t fract;
	mpz_init(res);
	mpz_init(fract);

	mpz_mul(res, counter, precision);
	mpz_div(res, res, denominator);

	mpz_set_d(ten, 10);

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

	mpz_t tmp;
	mpz_init(tmp);

	if (mpz_cmp_d(fract, 0) > 0)
	{
		result = result + ".";
		mpz_set(tmp, precision);
		while (mpz_cmp_d(tmp, 1) > 0)
		{
			mpz_div(tmp, tmp, ten);
			if (mpz_cmp(fract, tmp) < 0)
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

	return MakeNice(result);
}

inline string Number::MakeNice(string result)
{
	string unsignedValue = result;
	int isNegative = 0;
	if (result[0] == '-')
	{
		isNegative = 1;
		unsignedValue = StringManager::Substr(result, 1, result.size() - 1);
	}

	string rounded = RoundNine(unsignedValue);
	string truncated = TruncateZero(rounded);

	if (isNegative)
		return "-" + truncated;
	return truncated;
}

inline string Number::RoundNine(string result)
{
	int i = result.length() - 1;

	if (StringManager::FindFirst(result, '.') != result.length() - 6)
	{
		return result;
	}

	if (result[i] != '9')
	{
		if (result[i] == '1')
			result[i] = '0';
		return result;
	}

	for (; i >= 0; i--)
	{
		if (result[i] == '9')
			result[i] = '0';
		else
			break;
		if (i == 0)
			return "1" + result;
	}

	if (result[i] == '.')
		i--;

	for (; i > 0; i--)
	{
		if (result[i] == '9')
			result[i] = '0';
		else
			break;
		if (i == 0)
			return "1" + result;
	}

	result[i] += 1;

	return result;
}

inline string Number::TruncateZero(string result)
{
	if (StringManager::FindFirst(result, '.') < 0)
		return result;
	int i = result.length() - 1;
	int last = i;
	for (; i >= 0; i--)
	{
		if (result[i] == '0')
			last = i - 1;
		else
			break;
	}
	if (result[i] == '.')
		last = i - 1;
	if (last < 0)
		return "0";
	return StringManager::Substr(result, 0, last);
}

inline void Number::Print(int newLine)
{
	cout << ToString();
	if (newLine)
		cout << endl;
}

static Number zero(0);
static Number one(1);
static Number two(2);
static Number oneNeg(-1);
static Number twoNeg(-2);

inline void InitConstants()
{
	mpz_t a, b;
	mpq_t c;
	mpz_init(a);
	mpz_init(b);
	mpq_init(c);
	mpz_set_d(a, 1);
	mpq_set_d(c, -1);
	PRECISION_INT = 6;
	mpz_set_d(b, 1000000);
	mpq_set_num(PRECISION_VALUE.value, a);
	mpq_set_den(PRECISION_VALUE.value, b);

	mpq_set_num(DEC_PRECISION.value, b);
	mpq_set_den(DEC_PRECISION.value, a);

	mpz_pow_ui(b, b, 100);
	mpq_set_num(MAX_VALUE.value, b);
	mpq_set_den(MAX_VALUE.value, a);
	mpq_mul(MAX_NEGATIVE_VALUE.value, MAX_VALUE.value, c);

	mpq_set_num(SMALL_VALUE.value, a);
	mpq_set_den(SMALL_VALUE.value, b);

};

Number numberA;
Number numberB;

inline void SetNumberA(string s, bool isNegative = 0)
{
	numberA = CharsConstants::CharToInt(s[0]);

	for (int i = 1; i < s.length(); i++)
	{
		numberA *= 10;
		numberA = numberA + CharsConstants::CharToInt(s[i]);
	}
	if (isNegative)
		numberA *= oneNeg;
}

inline void SetNumberB(string s, bool isNegative = 0)
{
	numberB = CharsConstants::CharToInt(s[0]);

	for (int i = 1; i < s.length(); i++)
	{
		numberB *= 10;
		numberB = numberB + CharsConstants::CharToInt(s[i]);
	}
	if (isNegative)
		numberB *= oneNeg;
}

inline void SetPrecision(int value)
{
	PRECISION_INT = value;
	PRECISION_VALUE = 1;
	DEC_PRECISION = 1;
	for (int i = 0; i < value; i++)
	{
		DEC_PRECISION *= 10;
		PRECISION_VALUE /= 10;
	}
}

inline int SetValueFromString(string inputS)
{
	if (StringManager::BeginStarts(inputS, "set precision "))
	{
		string value = StringManager::Substr(inputS, 14, inputS.length() - 1);
		if (StringManager::ContainsOnlyDigits(value) == false)
			return 0;
		SetPrecision(atoi(value.c_str()));
		return 0;
	}

	if (StringManager::BeginStarts(inputS, "set a "))
	{
		string value = StringManager::Substr(inputS, 6, inputS.length() - 1);
		bool isNegative = false;
		if (CharsConstants::IsMinus(value[0]))
		{
			value = StringManager::Substr(value, 1, value.length() - 1);
			isNegative = true;
		}
		if (StringManager::ContainsOnlyDigits(value) == false)
			return 0;
		Number copy = numberA;
		SetNumberA(value, isNegative);
		if (numberA >= numberB)
		{
			printf("WARNING: a nie jest mniejsze niz b. Nie dokonano zmiany wartosci a\n");
			numberA = copy;
		}
		return 0;
	}

	if (StringManager::BeginStarts(inputS, "set b "))
	{
		string value = StringManager::Substr(inputS, 6, inputS.length() - 1);
		bool isNegative = false;
		if (CharsConstants::IsMinus(value[0]))
		{
			value = StringManager::Substr(value, 1, value.length() - 1);
			isNegative = true;
		}
		if (StringManager::ContainsOnlyDigits(value) == false)
			return 0;
		Number copy = numberB;
		SetNumberB(value, isNegative);
		if (numberB <= numberA)
		{
			printf("WARNING: b nie jest wieksze niz a. Nie dokonano zmiany wartosci b\n");
			numberB = copy;
		}
		return 0;
	}

	return -1;
}