#pragma once
#include "definitions.h"
#include "CharsConstants.h"

class StringManager
{
public:
	static string EmptyString();
	static bool IsEmptyString(string s);
	static char ReturnLastChar(string s);
	static bool LastCharIsADigit(string s);
	static bool LastCharIsALetter(string s);
	static bool LastCharIsADigitOrALetter(string s);
	static bool LastCharIsAdigitOrALetterOrAParenthesis(string s);
	static int FindFirst(string s, char c);
	static int FindLast(string s, char c);
	static string Substr(string s, int first, int last);
	static vector<string> Split(string s, string operators);
	static int FindClosingParenthesis(string s);
	static string ParenthesisContent(string s);
	static bool BeginStarts(string s1, string s2);
	static bool ContainsOnlyDigits(string s);
};

inline string StringManager::EmptyString()
{
	return "";
}

inline bool StringManager::IsEmptyString(string s)
{
	return s.length() == 0;
}

inline char StringManager::ReturnLastChar(string s)
{
	if (IsEmptyString(s))
		return -1;

	return s[s.length() - 1];
}

inline bool StringManager::LastCharIsADigit(string s)
{
	return CharsConstants::IsDigit(ReturnLastChar(s));
}

inline bool StringManager::LastCharIsALetter(string s)
{
	return CharsConstants::IsLetter(ReturnLastChar(s));
}

inline bool StringManager::LastCharIsADigitOrALetter(string s)
{
	return LastCharIsADigit(s) || LastCharIsALetter(s);
}

inline bool StringManager::LastCharIsAdigitOrALetterOrAParenthesis(string s)
{
	return LastCharIsADigitOrALetter(s)
		|| CharsConstants::IsOpeningParenthesis(ReturnLastChar(s))
		|| CharsConstants::IsClosingParenthesis(ReturnLastChar(s));
}

inline int StringManager::FindFirst(string s, char c)
{
	return s.find_first_of(c);
}

inline int StringManager::FindLast(string s, char c)
{
	return s.find_last_of(c);
}

inline string StringManager::Substr(string s, int first, int last)
{
	return s.substr(first, last - first + 1);
}

inline vector<string> StringManager::Split(string s, string operators)
{
	vector<string> v;

	if (IsEmptyString(s))
		return v;

	string element = EmptyString();
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

	return v;
}

inline int StringManager::FindClosingParenthesis(string s)
{
	const int errCode = -1;
	int count = 0;

	if (s.length() == 0)
		return errCode;

	if (CharsConstants::IsOpeningParenthesis(s[0]) == false)
		return errCode;

	for (int i = 0; i < s.length(); i++)
	{
		if (CharsConstants::IsOpeningParenthesis(s[i]))
			count++;
		else if (CharsConstants::IsClosingParenthesis(s[i]))
		{
			count--;
			if (count == 0)
			{
				return i;
			}
		}
	}

	return errCode;
}

inline string StringManager::ParenthesisContent(string s)
{
	int posOpen = FindFirst(s, CharsConstants::OpeningParenthesis);
	int posClose = FindFirst(s, CharsConstants::ClosingParenthesis);

	if (posOpen < 0 || posClose - posOpen <= 0)
		return EmptyString();

	return Substr(s, posOpen + 1, posClose - 1);
}

inline bool StringManager::BeginStarts(string s1, string s2)
{
	if (s2.length() > s1.length())
	{
		return false;
	}

	for (int i = 0; i < s2.length(); i++)
	{
		if (s1[i] != s2[i])
			return false;
	}

	return true;
}

inline bool StringManager::ContainsOnlyDigits(string s)
{
	for (int i = 0; i < s.length(); i++)
	{
		if (CharsConstants::IsDigit(s[i]) == false)
		{
			printf("WARNING: '%c' nie jest cyfra.\n", s[i]);
			return false;
		}
	}

	return true;
}