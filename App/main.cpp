#include "../Lib/Parser.h"

int main()
{
	Parser parser;
	Polynomial& p = CreatePolynomial();
	p = parser.ConvertToPolynomial("x13+14x12+8x7-22x3+1");
	p.PrintRoots(-10, 10);
	
	getchar();
	getchar();
	return 0;
}