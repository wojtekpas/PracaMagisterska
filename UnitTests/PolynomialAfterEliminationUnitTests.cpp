#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Lib/Polynomial.h"
#include "../Lib/Parser.h"
/*
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(PolynomialAfterEliminationUnitTests)
	{
		Parser parser;
	public:

		void Verify(string input, string output)
		{
			Polynomial p1 = parser.ConvertToPolynomial(input);
			Polynomial p2 = parser.ConvertToPolynomial(output);
			Polynomial polynomialAfterElimination = p1.PolynomialAfterEliminationOfMultipleRoots();
			polynomialAfterElimination.Normalize();
			Assert::AreEqual(p2.ToString(), polynomialAfterElimination.ToString());
		}

		TEST_METHOD(PolynomialAfterElimination01)
		{
			Verify("20", "1");
		}

		TEST_METHOD(PolynomialAfterElimination02)
		{
			Verify("2a", "a");
		}

		TEST_METHOD(PolynomialAfterElimination03)
		{
			Verify("a2", "a");
		}

		TEST_METHOD(PolynomialAfterElimination04)
		{
			Verify("-a3", "a");
		}

		TEST_METHOD(PolynomialAfterElimination05)
		{
			Verify("12a2", "a");
		}

		TEST_METHOD(PolynomialAfterElimination06)
		{
			Verify("(a-1)^2", "a-1");
		}

		TEST_METHOD(PolynomialAfterElimination07)
		{
			Verify("(a+3)^4", "(a+3)");
		}

		TEST_METHOD(PolynomialAfterElimination08)
		{
			Verify("(a+1)(a+2)", "(a+1)(a+2)");
		}

		TEST_METHOD(PolynomialAfterElimination09)
		{
			Verify("(a+3)^2*(a+1)", "(a+3)(a+1)");
		}

		TEST_METHOD(PolynomialAfterElimination10)
		{
			Verify("(a+3)^2*(a+1)^3", "(a+3)(a+1)");
		}

		TEST_METHOD(PolynomialAfterElimination11)
		{
			Verify("a3*(a+2)^10", "a(a+2)");
		}

		TEST_METHOD(PolynomialAfterElimination12)
		{
			Verify("(x+1)^4*(x-2)^2", "(x+1)(x-2)");
		}

		TEST_METHOD(PolynomialAfterElimination13)
		{
			Verify("(x-1)^2*(x+1)^2*(x-2)^2", "(x-1)(x+1)(x-2)");
		}

		TEST_METHOD(PolynomialAfterElimination14)
		{
			Verify("(x-1)^2*(x+1)^4*(x-2)^2", "(x-1)(x+1)(x-2)");
		}

		TEST_METHOD(PolynomialAfterElimination15)
		{
			Verify("(x+1)^4*(x2+x+1)", "(x+1)(x2+x+1)");
		}
	};
}
*/