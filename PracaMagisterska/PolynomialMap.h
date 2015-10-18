#pragma once
#include "IPolynomial.h"

class PolynomialMap :
	public IPolynomial
{
public:
	int Size() override;
	int ValueForPower(int power) override;
};

