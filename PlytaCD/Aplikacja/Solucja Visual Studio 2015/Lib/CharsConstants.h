#pragma once

class CharsConstants
{
	static const char Space = ' ';
	static const char Tab = '\t';
	static const char NewLine = '\n';
	static const char LeastDigit = '0';
	static const char GreatestDigit = '9';
	static const char LeastUppercase = 'A';
	static const char GreatestUppercase = 'Z';
	static const char LeastLowercase = 'a';
	static const char GreatestLowercase = 'z';

public:
	static const char Plus = '+';
	static const char Minus = '-';
	static const char Mul = '*';
	static const char Div = '/';
	static const char Exp = '^';
	static const char OpeningParenthesis = '(';
	static const char ClosingParenthesis = ')';
	static const char Var = 'x';

	static int CharToInt(char c);
	static bool IsDigit(char c);
	static bool IsLetter(char c);
	static bool IsUppercase(char c);
	static bool IsLowercase(char c);
	static bool IsWhitespace(char c);
	static bool IsPlus(char c);
	static bool IsMinus(char c);
	static bool IsMul(char c);
	static bool IsDiv(char c);
	static bool IsExp(char c);
	static bool IsOpeningParenthesis(char c);
	static bool IsClosingParenthesis(char c);
	static bool IsVar(char c);
	static bool IsOperator(char c);
	static bool IsLegalValue(char c);
	static bool IsLegalOpeningOperator(char c);
};


inline bool CharsConstants::IsUppercase(char c)
{
	return (c >= LeastUppercase) && (c <= GreatestUppercase);
}

inline bool CharsConstants::IsLowercase(char c)
{
	return (c >= LeastLowercase) && (c <= GreatestLowercase);
}

inline int CharsConstants::CharToInt(char c)
{
	return c - LeastDigit;
}

inline bool CharsConstants::IsDigit(char c)
{
	return (c >= LeastDigit) && (c <= GreatestDigit);
}

inline bool CharsConstants::IsLetter(char c)
{
	return IsUppercase(c) || IsLowercase(c);
}

inline bool CharsConstants::IsWhitespace(char c)
{
	return (c == Space || c == NewLine || c == Tab);
}

inline bool CharsConstants::IsPlus(char c)
{
	return c == Plus;
}

inline bool CharsConstants::IsMinus(char c)
{
	return c == Minus;
}

inline bool CharsConstants::IsMul(char c)
{
	return c == Mul;
}

inline bool CharsConstants::IsDiv(char c)
{
	return c == Div;
}

inline bool CharsConstants::IsExp(char c)
{
	return c == Exp;
}

inline bool CharsConstants::IsOpeningParenthesis(char c)
{
	return c == OpeningParenthesis;
}

inline bool CharsConstants::IsClosingParenthesis(char c)
{
	return c == ClosingParenthesis;
}

inline bool CharsConstants::IsVar(char c)
{
	return c == Var;
}

inline bool CharsConstants::IsOperator(char c)
{
	return IsPlus(c) || IsMinus(c) || IsMul(c) || IsDiv(c) || IsExp(c)
		|| IsOpeningParenthesis(c) || IsClosingParenthesis(c);
}

inline bool CharsConstants::IsLegalOpeningOperator(char c)
{
	return IsMinus(c) || IsOpeningParenthesis(c);
}

inline bool CharsConstants::IsLegalValue(char c)
{
	return IsOperator(c) || IsDigit(c) || IsLetter(c) || IsWhitespace(c);
}