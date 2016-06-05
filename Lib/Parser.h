#pragma once
#include "CharsConstants.h"
#include "Polynomial.h"
#include "PolynomialMap.h"
#include "PolynomialVector.h"
#include "StringManager.h"

#define NUMBER_OF_TYPES 2

inline Polynomial& CreatePolynomial(int type = 0)
{
	if (type == 0)
		return CreatePolynomialVector();
	return CreatePolynomialMap();
}

class Parser
{
public:
	string s;

	explicit Parser();
	explicit Parser(string s);

	Polynomial& ConvertToPolynomial(string inputS, int type = 0);
	string UniformInputString(string s);
};

inline Parser::Parser()
{
	s = StringManager::EmptyString();
}

inline Parser::Parser(string s)
{
	this->s = s;
}

inline Polynomial& Parser::ConvertToPolynomial(string inputS, int type)
{
	Polynomial& emptyPolynomial = CreatePolynomial(type); // = polynomialMap.CreatePolynomial();

	string s = UniformInputString(inputS);

	if (StringManager::IsEmptyString(s))
		emptyPolynomial;

	Polynomial& sumElement = CreatePolynomial(type);// = polynomialMap.CreatePolynomial();
	Polynomial& mulElement = CreatePolynomial(type);// = polynomialMap.CreatePolynomial();
	Polynomial& curElement = CreatePolynomial(type);// = polynomialMap.CreatePolynomial();

	bool sumOp = true;
	bool mulOp = true;
	bool skip = false;

	string element = StringManager::EmptyString();
	int first = 0;

	for (int i = 0; i < s.length(); i++)
	{
		if (CharsConstants::IsOperator(s[i]))
		{
			if (skip == false)
				curElement.Set(StringManager::Substr(s, first, i - 1));
			else
				skip = false;

			first = i + 1;
			
			if(CharsConstants::IsPlus(s[i]))
			{
				if (mulElement.IsZero() == false)
				{
					curElement *= mulElement;
					mulElement.Clear();
				}

				if (sumOp)
					sumElement += curElement;
				else
					sumElement -= curElement;
				sumOp = true;
			}
			else if(CharsConstants::IsMinus(s[i]))
			{
				if (mulElement.IsZero() == false)
				{
					curElement *= mulElement;
					mulElement.Clear();
				}

				if (sumOp)
					sumElement += curElement;
				else
					sumElement -= curElement;
				sumOp = false;
			}
			else if(CharsConstants::IsMul(s[i]))
			{
				if (mulElement.IsNew())
					mulElement.Add(0, Number(1));

				if (mulOp)
					mulElement *= curElement;
				else
					mulElement /= curElement;

				mulOp = true;
			}
			else if(CharsConstants::IsDiv(s[i]))
			{
				if (mulElement.IsZero())
					mulElement.Add(0, Number(1));

				if (mulOp)
					mulElement *= curElement;
				else
					mulElement /= curElement;

				mulOp = false;
			}
			else if(CharsConstants::IsExp(s[i]))
			{
				i++;
				if (CharsConstants::IsDigit(s[i]) == false)
					return emptyPolynomial;

				int power = CharsConstants::CharToInt(s[i]);
				i++;

				while (i < s.length() && CharsConstants::IsDigit(s[i]))
				{
					power *= 10;
					power += CharsConstants::CharToInt(s[i]);
					i++;
				}

				i--;
				curElement ^= power;
				skip = true;
			}
			else if(CharsConstants::IsOpeningParenthesis(s[i]))
			{
				int closingParenthesis = StringManager::FindClosingParenthesis(StringManager::Substr(s, i, s.length() - 1));
				curElement = ConvertToPolynomial(StringManager::Substr(s, i + 1, i + closingParenthesis - 1), type);
				i += closingParenthesis;
				skip = true;
			}
			else
			{
				return emptyPolynomial;
			}
		}
	}

	if (skip == false)
		curElement.Set(StringManager::Substr(s, first, s.length()));

	if (mulElement.IsNew() == false)
	{
		curElement *= mulElement;
		mulElement.Clear();
	}
	if (sumOp)
		sumElement += curElement;
	else
		sumElement -= curElement;

	sumElement.inputS = s;
	DeletePolynomial(&emptyPolynomial);
	DeletePolynomial(&curElement);
	DeletePolynomial(&mulElement);
	return sumElement;
}

inline string Parser::UniformInputString(string s)
{
	string result = StringManager::EmptyString();
	int countParenthesis = 0;

	if (s.length() == 0)
		return StringManager::EmptyString();

	if (CharsConstants::IsLegalValue(s[0]) == false)
		return StringManager::EmptyString();

	if (CharsConstants::IsOperator(s[0])
		&& CharsConstants::IsLegalOpeningOperator(s[0]) == false)
		return StringManager::EmptyString();

	for (int i = 0; i < s.length(); i++)
	{
		if (CharsConstants::IsWhitespace(s[i]) == false)
		{
			if (CharsConstants::IsLegalValue(s[i]) == false)
				return StringManager::EmptyString();

			if (CharsConstants::IsDigit(s[i]))
			{
				if (StringManager::LastCharIsALetter(result)
					|| CharsConstants::IsClosingParenthesis(StringManager::ReturnLastChar(result)))
					result += CharsConstants::Exp;
				result += s[i];
			}
			else if (CharsConstants::IsLetter(s[i]))
			{
				if (StringManager::LastCharIsADigit(result))
				{
					result += CharsConstants::Mul;
					result += CharsConstants::Var;
				}
				else if (StringManager::LastCharIsALetter(result) == false)
					result += CharsConstants::Var;
				else
					return StringManager::EmptyString();
			}
			else if(CharsConstants::IsOpeningParenthesis(s[i]))
			{
				if (StringManager::LastCharIsADigitOrALetter(result)
					|| CharsConstants::IsClosingParenthesis(StringManager::ReturnLastChar(result)))
					result += CharsConstants::Mul;
				result += s[i];
			}
			else if (CharsConstants::IsMinus(s[i]))
			{
				if (StringManager::IsEmptyString(result)
					|| StringManager::LastCharIsAdigitOrALetterOrAParenthesis(result))
					result += s[i];	
				else
					return StringManager::EmptyString();
			}
			else if (CharsConstants::IsOperator(s[i]))
			{
				if (StringManager::LastCharIsAdigitOrALetterOrAParenthesis(result))
					result += s[i];
				else
					return StringManager::EmptyString();
			}
			else
				result += s[i];
		}
	}

	if (countParenthesis != 0)
		return StringManager::EmptyString();

	return result;
}
