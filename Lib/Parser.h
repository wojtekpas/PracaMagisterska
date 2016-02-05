#pragma once
#include "CharsConstants.h"
#include "PolynomialMap.h"
#include "StringManager.h"

class Parser
{
public:
	string s;

	explicit Parser(string s);

	vector<string> SeparateElementsSum(string s);
	vector<string> SeperateElementsMul(string s);
	pair<string, string> SeperatePowerAndExp(string s);
	PolynomialMap ConvertToPolynomialMap(string s);
	string UniformInputString(string s);
};


inline Parser::Parser(string s)
{
	this->s = s;
}

inline vector<string> Parser::SeparateElementsSum(string s)
{
	vector<string>v;
	return v;
}

inline vector<string> Parser::SeperateElementsMul(string s)
{
	vector<string>v;
	return v;
}

inline pair<string, string> Parser::SeperatePowerAndExp(string s)
{
	return pair<string, string>("1", "2");
}

inline PolynomialMap Parser::ConvertToPolynomialMap(string inputS)
{
	string s = UniformInputString(inputS);
	PolynomialMap sumElement;
	PolynomialMap mulElement;
	PolynomialMap curElement;

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
			switch (s[i])
			{
			case CharsConstants::Plus:
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
				break;
			}
			case CharsConstants::Minus:
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
				break;
			}
			case CharsConstants::Mul:
			{
				if (mulElement.IsZero())
					mulElement.Add(0, 1);

				if (mulOp)
					mulElement *= curElement;
				else
					mulElement /= curElement;

				mulOp = true;
				break;
			}
			case CharsConstants::Div:
			{
				if (mulElement.IsZero())
					mulElement.Add(0, 1);

				if (mulOp)
					mulElement *= curElement;
				else
					mulElement /= curElement;

				mulOp = false;
				break;
			}
			case CharsConstants::Exp:
			{
				i++;
				assert(CharsConstants::IsDigit(s[i]));

				int power = CharsConstants::CharToInt(s[i]);
				i++;

				while (i < s.length() && CharsConstants::IsDigit(s[i]))
				{
					power *= 10;
					power = power + s[i] - '0';
					i++;
				}

				i--;
				curElement ^= power;
				skip = true;
				break;
			}
			case CharsConstants::OpeningParenthesis:
			{
				int closingParenthesis = StringManager::FindClosingParenthesis(StringManager::Substr(s, i, s.length() - 1));
				curElement = ConvertToPolynomialMap(StringManager::Substr(s, i, closingParenthesis));
				break;
			}
			default:
			{
				assert(false);
				break;
			}
			}
		}
	}
	if (skip == false)
		curElement.Set(StringManager::Substr(s, first, s.length()));

	if (mulElement.IsZero() == false)
	{
		curElement *= mulElement;
		mulElement.Clear();
	}

	if (sumOp)
		sumElement += curElement;
	else
		sumElement -= curElement;

	return sumElement;
}

inline string Parser::UniformInputString(string s)
{
	string result = StringManager::EmptyString();
	int countParenthesis = 0;

	assert(s.length());

	assert(CharsConstants::IsLegalValue(s[0]) && 
		(CharsConstants::IsOperator(s[0]) == false
			|| CharsConstants::IsLegalOpeningOperator(s[0])));

	if (CharsConstants::IsPlus == false)
		result += s[0];

	for (int i = 1; i < s.length(); i++)
	{
		if (CharsConstants::IsWhitespace(s[i]) == false)
		{

			assert(CharsConstants::IsLegalValue(s[i]));

			if (CharsConstants::IsDigit(s[i]))
			{
				if (CharsConstants::IsLetter(s[i - 1]))
					result += CharsConstants::Exp;
			}
			else if (CharsConstants::IsLetter(s[i]))
			{
				if (CharsConstants::IsDigit(s[i - 1]))
					result += CharsConstants::Mul;
			}

			if (CharsConstants::IsLetter(s[i]))
				result += CharsConstants::Var;
			else
				result += s[i];
		}
	}

	assert(countParenthesis == 0);

	cout << result << endl;

	return result;
}