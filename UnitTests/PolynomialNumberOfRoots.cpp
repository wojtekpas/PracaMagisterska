#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Lib/Parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(PolynomialNumberOfRootsUnitTests)
	{
		Parser parser;
		Number a;
		Number b;
	public:

		void Verify(string input, int expectedNumberOfRoots)
		{
			Polynomial& p = parser.ConvertToPolynomial(input);
			Polynomial& polynomialAfterElimination = p.PolynomialAfterEliminationOfMultipleRoots();
			polynomialAfterElimination.Normalize();
			int numberOfRoots = polynomialAfterElimination.NumberOfRoots(a, b);
			Assert::AreEqual(expectedNumberOfRoots, numberOfRoots);
		}

		TEST_METHOD_INITIALIZE(Init)
		{
			a.SetMaxNegativeValue();
			b.SetMaxValue();
		}

		TEST_METHOD(PolynomialNumberOfRoots01)
		{
			Verify("20", 0);
		}

		TEST_METHOD(PolynomialNumberOfRoots02)
		{
			Verify("2a", 1);
		}

		TEST_METHOD(PolynomialNumberOfRoots03)
		{
			Verify("a2", 1);
		}

		TEST_METHOD(PolynomialNumberOfRoots04)
		{
			Verify("-a3", 1);
		}

		TEST_METHOD(PolynomialNumberOfRoots05)
		{
			Verify("12a2", 1);
		}

		TEST_METHOD(PolynomialNumberOfRoots06)
		{
			Verify("(a-1)^2", 1);
		}

		TEST_METHOD(PolynomialNumberOfRoots07)
		{
			Verify("(a+3)^4", 1);
		}

		TEST_METHOD(PolynomialNumberOfRoots08)
		{
			Verify("(a+1)(a+2)", 2);
		}

		TEST_METHOD(PolynomialNumberOfRoots09)
		{
			Verify("(a+3)^2*(a+1)", 2);
		}

		TEST_METHOD(PolynomialNumberOfRoots10)
		{
			Verify("(a+3)^2*(a+1)^3", 2);
		}

		TEST_METHOD(PolynomialNumberOfRoots11)
		{
			Verify("a3*(a+2)^10", 2);
		}

		TEST_METHOD(PolynomialNumberOfRoots12)
		{
			Verify("(x+1)^4*(x-2)^2", 2);
		}

		TEST_METHOD(PolynomialNumberOfRoots13)
		{
			Verify("(x-1)^2*(x+1)^2*(x-2)^2", 3);
		}

		TEST_METHOD(PolynomialNumberOfRoots14)
		{
			Verify("(x-1)^2*(x+1)^4*(x-2)^2", 3);
		}

		TEST_METHOD(PolynomialNumberOfRoots15)
		{
			Verify("(x+1)^4*(x2+x+1)", 1);
		}

		TEST_METHOD(PolynomialNumberOfRoots16)
		{
			a = -1;
			Verify("12a2", 1);
		}

		TEST_METHOD(PolynomialNumberOfRoots17)
		{
			b = 4;
			Verify("(a-1)^2", 1);
		}

		TEST_METHOD(PolynomialNumberOfRoots18)
		{
			a = -20;
			b = 10;
			Verify("(a+3)^4", 1);
		}

		TEST_METHOD(PolynomialNumberOfRoots19)
		{
			a = -1;
			b = 4;
			Verify("a3*(a+2)^10", 1);
		}

		TEST_METHOD(PolynomialNumberOfRoots20)
		{
			a = 0;
			b = 1;
			Verify("(x+1)^4*(x-2)^2", 0);
		}

		TEST_METHOD(PolynomialNumberOfRoots21)
		{
			b = 2;
			Verify("(x-1)^2*(x+1)^2*(x-3)^2", 2);
		}
	};
}
