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

int Parser::FindClosingBracket(string s) const
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
			if(count == 0)
			{
				return i;
			}
		}
	}
	
	assert(false);
	cout << "ok";
	return -1;
}

PolynomialMap Parser::ConvertToPolynomialMap(string inputS)
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
			switch(s[i])
			{
			case '+':
			{
				if(mulElement.IsZero() == false)
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
	if(skip == false)
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

bool Parser::IsLegalValue(char c)
{
	return IsOperator(c) || IsDigit(c) || IsSymbol(c);
}

bool Parser::IsOperator(char c)
{
	return FindFirst(operators, c) >= 0;
}

bool Parser::IsLegalOpeningOperator(char c)
{
	if (c == '+' || c == '-' || c == '(')
		return true;

	return false;
}

bool Parser::IsDigit(char c)
{
	return (c >= '0' && c <= '9');
}

bool Parser::IsSymbol(char c)
{
	return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

bool Parser::IsWhitespace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

string Parser::UniformInputString(string s)
{
	string result = "";
	int countBrackets = 0;

	assert(s.length());

	assert(IsLegalValue(s[0]) && (IsOperator(s[0]) == false || IsLegalOpeningOperator(s[0])));

	if (s[0] != '+')
		result += s[0];

	for (int i = 1; i < s.length(); i++)
	{
		if (IsWhitespace(s[i]) == false)
		{

			assert(IsLegalValue(s[i]));

			if (IsDigit(s[i]))
			{
				if (IsSymbol(s[i - 1]))
					result += '^';
			}
			else if (IsSymbol(s[i]))
			{
				if (IsDigit(s[i - 1]))
					result += '*';
			}

			if (IsSymbol(s[i]))
				result += 'a';
			else
				result += s[i];
		}
	}
	
	assert(countBrackets == 0);

	cout << result << endl;

	return result;
}