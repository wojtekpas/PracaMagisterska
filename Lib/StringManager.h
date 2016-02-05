#pragma once
#include "definitions.h"
#include "CharsConstants.h"

class StringManager
{
public:
	static string EmptyString();
	static bool IsEmptyString(string s);
	static int FindFirst(string s, char c);
	static int FindLast(string s, char c);
	static string Substr(string s, int first, int last);
	static vector<string> Split(string s, string operators);
	static int FindClosingParenthesis(string s);
	string ParenthesisContent(string s);
};

inline string StringManager::EmptyString()
{
	return "";
}

inline bool StringManager::IsEmptyString(string s)
{
	return s.length() == 0;
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

	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << ",";
	}

	cout << endl;

	return v;
}

inline int StringManager::FindClosingParenthesis(string s)
{
	int count = 0;

	assert(s.length() != 0);

	assert(CharsConstants::IsOpeningParenthesis(s[0]));

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

	assert(false);
	cout << "ok";
	return -1;
}

inline string StringManager::ParenthesisContent(string s)
{
	int posOpen = FindFirst(s, CharsConstants::OpeningParenthesis);
	int posClose = FindFirst(s, CharsConstants::ClosingParenthesis);

	if (posOpen < 0 || posClose - posOpen <= 0)
		return EmptyString();

	return Substr(s, posOpen + 1, posClose - 1);
}