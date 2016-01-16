#pragma once
#include "PolynomialMap.h"

class Parser
{
public:
	string const stringEmpty = "";
	string const operators = "+-*/^()";
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
	int FindClosingBracket(string s) const;
	PolynomialMap ConvertToPolynomialMap(string s);
	bool IsLegalValue(char c);
	bool IsOperator(char c);
	bool IsLegalOpeningOperator(char c);
	bool IsDigit(char c);
	bool IsSymbol(char c);
	bool IsWhitespace(char c);
	string UniformInputString(string s);
};

