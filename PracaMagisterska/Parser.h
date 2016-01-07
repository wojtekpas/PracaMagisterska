#pragma once
#include "PolynomialMap.h"

class Parser
{
public:
	string const stringEmpty = "";
	string s;

	explicit Parser(string s);

	int FindFirst(string s, char c) const;
	int FindLast(string s, char c) const;
	string Substr(string s, int firstInclusive, int lastExclusive) const;
	vector<string> Split(string s, string operators) const;
	string BracketsContent(string s) const;
	vector<string> SeparateElementsSum(string s);
	vector<string> SeperateElementsMul(string s);
	pair<string, string> SeperatePowerAndExp(string s);
};

