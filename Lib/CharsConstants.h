#pragma once

class CharsConstants
{
protected:
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
	static bool IsDigit(char c);
	static bool IsLetter(char c);
	static bool IsUppercase(char c);
	static bool IsLowercase(char c);
	static bool IsWhitespace(char c);
};


inline bool CharsConstants::IsUppercase(char c)
{
	return (c >= LeastUppercase) && (c <= GreatestUppercase);
}

inline bool CharsConstants::IsLowercase(char c)
{
	return (c >= LeastLowercase) && (c <= GreatestLowercase);
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