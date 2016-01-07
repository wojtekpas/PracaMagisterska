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

	Parser p1("12+21+23*5+32");
	Parser p2("11");
	Parser p3("");
	Parser p4("22*33");
	Parser p5("(15");
	Parser p6("35/55");
	Parser p7("10*10+10");
	Parser p8("30*(10+10)");
	Parser p9("(4)");

	p1.Split(p1.s, operators);
	p1.Split(p2.s, operators);
	p1.Split(p3.s, operators);
	p1.Split(p4.s, operators);
	p1.Split(p5.s, operators);
	p1.Split(p6.s, operators);
	p1.Split(p7.s, operators);
	p1.Split(p8.s, operators);
	p1.Split(p9.s, operators);

	int tmp;
	cin >> tmp;
	cin >> tmp;
	return 0;
}
