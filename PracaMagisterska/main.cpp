#pragma once
#include "definitions.h"
#include "PolynomialMap.h"

int main(int argc, char* argv[])
{
	PolynomialMap* p1 = new PolynomialMap(3);
	PolynomialMap* p2 = new PolynomialMap(2);
	PolynomialMap* p3 = new PolynomialMap(1);
	PolynomialMap* c1 = p1;
	PolynomialMap* c2 = p2;

/*	c1->Print("c1");
	c2->Print("c2");*/

	*p3 += p2;

	p1->Print("p1");
	p2->Print("p2");
	p3->Print("p3");

	int tmp;
	cin >> tmp;
	cin >> tmp;
	return 0;
}
