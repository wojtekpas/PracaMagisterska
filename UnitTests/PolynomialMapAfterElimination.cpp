#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Lib/PolynomialMap.h"
#include "../Lib/Parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(PolynomialMapAfterEliminationUnitTests)
	{
		Parser parser;
	public:

		void Verify(string input, string output)
		{
			PolynomialMap p1 = parser.ConvertToPolynomialMap(input);
			PolynomialMap p2 = parser.ConvertToPolynomialMap(output);
			PolynomialMap AfterElimination = p1.PolynomialAfterEliminationOfMultipleRoots();
			AfterElimination.Normalize();
			Assert::AreEqual(p2.ToString(), AfterElimination.ToString());
		}

		TEST_METHOD(PolynomialMapAfterElimination01)
		{
			Verify("20", "1");
		}

		TEST_METHOD(PolynomialMapAfterElimination02)
		{
			Verify("2a", "1");
		}

		TEST_METHOD(PolynomialMapAfterElimination03)
		{
			Verify("a2", "a");
		}

		TEST_METHOD(PolynomialMapAfterElimination04)
		{
			Verify("-a3", "a2");
		}

		TEST_METHOD(PolynomialMapAfterElimination05)
		{
			Verify("12a2", "a");
		}

		TEST_METHOD(PolynomialMapAfterElimination06)
		{
			Verify("(a-1)^2", "a-1");
		}

		TEST_METHOD(PolynomialMapAfterElimination07)
		{
			Verify("(a+3)^4", "(a+3)^3");
		}

		TEST_METHOD(PolynomialMapAfterElimination08)
		{
			Verify("(a+1)(a+2)", "(a+1)(a+2)");
		}

		TEST_METHOD(PolynomialMapAfterElimination09)
		{
			Verify("(a+3)^2*(a+1)", "(a+3)(a+1)");
		}

		TEST_METHOD(PolynomialMapAfterElimination10)
		{
			Verify("(a+3)^2*(a+1)^3", "(a+3)(a+1)");
		}

		TEST_METHOD(PolynomialMapAfterElimination11)
		{
			Verify("a3*(a+5)^10", "a(a+5)");
		}

		TEST_METHOD(PolynomialMapAfterElimination12)
		{
			Verify("(x+1)^4*(x-2)^2", "(x+1)(x-2)");
		}

		TEST_METHOD(PolynomialMapAfterElimination13)
		{
			Verify("(x-1)^2*(x+1)^2*(x-2)^2", "(x-1)(x+1)(x-2)");
		}

		TEST_METHOD(PolynomialMapAfterElimination14)
		{
			Verify("(x-1)^2*(x+1)^4*(x-2)^2", "(x-1)(x+1)(x-2)");
		}

		TEST_METHOD(PolynomialMapAfterElimination15)
		{
			Verify("(x+1)^4*(x2+x+1)", "(x+1)(x2+x+1)");
		}
	};
}
