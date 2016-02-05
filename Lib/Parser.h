#pragma once
#include "CharsConstants.h"
#include "PolynomialMap.h"

class Parser
{
public:
	string const stringEmpty = "";
	string const operators = "+-*/^()";
	string s;

	explicit Parser(string s);

	int FindFirst(string s, char c);
	int FindLast(string s, char c);
	string Substr(string s, int firstInclusive, int lastExclusive);
	vector<string> Split(string s, string operators);
	string BracketsContent(string s);
	vector<string> SeparateElementsSum(string s);
	vector<string> SeperateElementsMul(string s);
	pair<string, string> SeperatePowerAndExp(string s);
	int FindClosingBracket(string s);
	PolynomialMap ConvertToPolynomialMap(string s);
	bool IsOperator(char c);
	bool IsLegalValue(char c);
	bool IsLegalOpeningOperator(char c);
	string UniformInputString(string s);
};


inline Parser::Parser(string s)
{
	this->s = s;
}

inline int Parser::FindFirst(string s, char c)
{
	return s.find_first_of(c);
}

inline int Parser::FindLast(string s, char c)
{
	return s.find_last_of(c);
}

inline string Parser::Substr(string s, int first, int last)
{
	return s.substr(first, last - first + 1);
}

inline vector<string> Parser::Split(string s, string operators)
{
	vector<string> v;

	if (s == stringEmpty)
		return v;

	string element = "";
	int first = 0;

	for (int i = 0; i < s.length(); i++)
	{
		if (FindFirst(operators, s[i]) >= 0)
		{
			v.push_back(Substr(s, first, i - 1));
			first = i + 1;
		}
	}

	v.push_back(Substr(s, first, s.length() - 1));

	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << ",";
	}

	cout << endl;

	return v;
}

inline string Parser::BracketsContent(string s)
{
	int posOpen = FindFirst(s, '(');
	int posClose = FindLast(s, ')');

	if (posOpen < 0 || posClose - posOpen <= 0)
		return stringEmpty;

	return "'" + Substr(s, posOpen + 1, posClose - 1) + "'";
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

inline int Parser::FindClosingBracket(string s)
{
	int count = 0;

	assert(s.length() != 0);

	assert(s[0] == '(');

	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == '(')
			count++;
		else if (s[i] == ')')
		{
			count--;
			if (count == 0)
			{
				return i;
			}
		}
	}

	assert(false);
	cout << "ok";
	return -1;
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

	string element = "";
	int first = 0;

	for (int i = 0; i < s.length(); i++)
	{
		if (FindFirst(operators, s[i]) >= 0)
		{
			if (skip == false)
				curElement.Set(Substr(s, first, i - 1));
			else
				skip = false;

			first = i + 1;
			switch (s[i])
			{
			case '+':
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
			case '-':
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
			case '*':
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
			case '/':
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
			case '^':
			{
				i++;
				assert(s[i] >= '0' && s[i] <= '9');

				int power = s[i] - '0';
				i++;

				while (i < s.length() && s[i] >= '0' && s[i] <= '9')
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
			case '(':
			{
				int closingBracket = FindClosingBracket(Substr(s, i, s.length() - 1));
				curElement = ConvertToPolynomialMap(Substr(s, i, closingBracket));
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
		curElement.Set(Substr(s, first, s.length()));

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

inline bool Parser::IsOperator(char c)
{
	return FindFirst(operators, c) >= 0;
}

inline bool Parser::IsLegalValue(char c)
{
	return IsOperator(c) || CharsConstants::IsDigit(c) || CharsConstants::IsLetter(c);
}

inline bool Parser::IsLegalOpeningOperator(char c)
{
	if (c == '+' || c == '-' || c == '(')
		return true;

	return false;
}

inline string Parser::UniformInputString(string s)
{
	string result = "";
	int countBrackets = 0;

	assert(s.length());

	assert(IsLegalValue(s[0]) && (IsOperator(s[0]) == false || IsLegalOpeningOperator(s[0])));

	if (s[0] != '+')
		result += s[0];

	for (int i = 1; i < s.length(); i++)
	{
		if (CharsConstants::IsWhitespace(s[i]) == false)
		{

			assert(IsLegalValue(s[i]));

			if (CharsConstants::IsDigit(s[i]))
			{
				if (CharsConstants::IsLetter(s[i - 1]))
					result += '^';
			}
			else if (CharsConstants::IsLetter(s[i]))
			{
				if (CharsConstants::IsDigit(s[i - 1]))
					result += '*';
			}

			if (CharsConstants::IsLetter(s[i]))
				result += 'a';
			else
				result += s[i];
		}
	}

	assert(countBrackets == 0);

	cout << result << endl;

	return result;
}