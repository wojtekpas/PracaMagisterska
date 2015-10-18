#pragma once
#include "definitions.h"
#include "Polynomial.h"

int main(int argc, char* argv[])
{
	IPolynomial* p = (IPolynomial*) new Polynomial();

	return 0;
}
