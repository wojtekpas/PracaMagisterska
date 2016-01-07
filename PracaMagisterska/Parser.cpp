#include "Parser.h"

Parser::Parser(string s)
{
	this->s = s;
}

int Parser::FindFirst(string s, char c) const
{
	return s.find_first_of(c);
}

int Parser::FindLast(string s, char c) const
{
	return s.find_last_of(c);
}

string Parser::Substr(string s, int first, int last) const
{
	return s.substr(first, last - first + 1);
}

vector<string> Parser::Split(string s, string operators) const
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

string Parser::BracketsContent(string s) const
{
	int posOpen = FindFirst(s, '(');
	int posClose = FindLast(s, ')');

	if (posOpen < 0 || posClose - posOpen <= 0)
		return stringEmpty;

	return "'" + Substr(s, posOpen + 1, posClose - 1) + "'";
}

vector<string> Parser::SeparateElementsSum(string s)
{
	vector<string>v;
	return v;
}

vector<string> Parser::SeperateElementsMul(string s)
{
	vector<string>v;
	return v;
}

pair<string, string> Parser::SeperatePowerAndExp(string s)
{
	return pair<string, string>("1","2");
}
