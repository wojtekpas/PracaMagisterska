#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Lib/PolynomialMap.h"
#include "../Lib/Parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(PolynomialMapNumberOfRootsUnitTests)
	{
		Parser parser;
		Number a;
		Number b;
	public:

		void Verify(string input, int expectedNumberOfRoots)
		{
			PolynomialMap p = parser.ConvertToPolynomialMap(input);
			PolynomialMap polynomialAfterElimination = p.PolynomialAfterEliminationOfMultipleRoots();
			polynomialAfterElimination.Normalize();
			int numberOfRoots = polynomialAfterElimination.NumberOfRoots(a, b);
			Assert::AreEqual(expectedNumberOfRoots, numberOfRoots);
		}

		TEST_METHOD_INITIALIZE(Init)
		{
			a.SetMaxNegativeValue();
			b.SetMaxValue();
		}

		TEST_METHOD(PolynomialMapNumberOfRoots01)
		{
			Verify("20", 0);
		}

		TEST_METHOD(PolynomialMapNumberOfRoots02)
		{
			Verify("2a", 1);
		}

		TEST_METHOD(PolynomialMapNumberOfRoots03)
		{
			Verify("a2", 1);
		}

		TEST_METHOD(PolynomialMapNumberOfRoots04)
		{
			Verify("-a3", 1);
		}

		TEST_METHOD(PolynomialMapNumberOfRoots05)
		{
			Verify("12a2", 1);
		}

		TEST_METHOD(PolynomialMapNumberOfRoots06)
		{
			Verify("(a-1)^2", 1);
		}

		TEST_METHOD(PolynomialMapNumberOfRoots07)
		{
			Verify("(a+3)^4", 1);
		}

		TEST_METHOD(PolynomialMapNumberOfRoots08)
		{
			Verify("(a+1)(a+2)", 2);
		}

		TEST_METHOD(PolynomialMapNumberOfRoots09)
		{
			Verify("(a+3)^2*(a+1)", 2);
		}

		TEST_METHOD(PolynomialMapNumberOfRoots10)
		{
			Verify("(a+3)^2*(a+1)^3", 2);
		}

		TEST_METHOD(PolynomialMapNumberOfRoots11)
		{
			Verify("a3*(a+2)^10", 2);
		}

		TEST_METHOD(PolynomialMapNumberOfRoots12)
		{
			Verify("(x+1)^4*(x-2)^2", 2);
		}

		TEST_METHOD(PolynomialMapNumberOfRoots13)
		{
			Verify("(x-1)^2*(x+1)^2*(x-2)^2", 3);
		}

		TEST_METHOD(PolynomialMapNumberOfRoots14)
		{
			Verify("(x-1)^2*(x+1)^4*(x-2)^2", 3);
		}

		TEST_METHOD(PolynomialMapNumberOfRoots15)
		{
			Verify("(x+1)^4*(x2+x+1)", 1);
		}
	};
}
