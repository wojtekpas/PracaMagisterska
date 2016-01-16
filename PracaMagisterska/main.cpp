#pragma once
#include "Parser.h"

int main(int argc, char* argv[])
{
	/*
	PolynomialMap p1(3);
	PolynomialMap p2(2);
	PolynomialMap p3(1);
	PolynomialMap c1 = p1;
	PolynomialMap c2 = p1;

	c1 = c1 + p2 + p3;
	c2 += p2;
	c2 += p3;

	p1.Print("p1");
	p2.Print("p2");
	p3.Print("p3");
	c1.Print("p1 + p2 + p3");
	c2.Print("p1 + p2 + p3");
	*/

	string operators = "+-*/()";

	Parser p1("a5+2"); //12+21+23*5+32

	PolynomialMap map = p1.ConvertToPolynomialMap(p1.s);

	map.Print("map");

	int tmp;
	cin >> tmp;
	cin >> tmp;
	return 0;
}
