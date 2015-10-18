#pragma once
#include "definitions.h"

class IPolynomial
{
public:
	virtual int Size();
	virtual int ValueForPower(int power);

};

