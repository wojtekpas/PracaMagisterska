#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Lib/PolynomialMap.h"
#include "../Lib/Parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(PolynomialMapValueUnitTests)
	{
		Parser parser;
	public:

		void Verify(string input, int a, double expectedValue)
		{
			PolynomialMap p1 = parser.ConvertToPolynomialMap(input);
			Number result = p1.PolynomialValue(Number(a));
			Assert::AreEqual(expectedValue, result.GetValue());
		}

		TEST_METHOD(PolynomialMapValue01)
		{
			Verify("20", 0, 20);
		}

		TEST_METHOD(PolynomialMapValue02)
		{
			Verify("-30", 5, -30);
		}

		TEST_METHOD(PolynomialMapValue03)
		{
			Verify("a", 13, 13);
		}

		TEST_METHOD(PolynomialMapValue04)
		{
			Verify("-a3", 7, -343);
		}

		TEST_METHOD(PolynomialMapValue05)
		{
			Verify("12a2", 3, 108);
		}

		TEST_METHOD(PolynomialMapValue06)
		{
			Verify("(a-1)^2", 1, 0);
		}

		TEST_METHOD(PolynomialMapValue07)
		{
			Verify("(a+3)^4", 2, 625);
		}

		TEST_METHOD(PolynomialMapValue08)
		{
			Verify("(a+1)(a+2)", 3, 20);
		}

		TEST_METHOD(PolynomialMapValue09)
		{
			Verify("(a+3)^2*(a+1)", 2, 75);
		}

		TEST_METHOD(PolynomialMapValue10)
		{
			Verify("(a+3)^2*(a+1)^3", -2, -1);
		}

		TEST_METHOD(PolynomialMapValue11)
		{
			Verify("(a+8)*(a+2)^10", 0, 8192);
		}

		TEST_METHOD(PolynomialMapValue12)
		{
			Verify("(x+1)^4*(x-2)^2", 2, 0);
		}

		TEST_METHOD(PolynomialMapValue13)
		{
			Verify("(x-1)^2*(x+1)^2*(x-2)^2", 0, 4);
		}

		TEST_METHOD(PolynomialMapValue14)
		{
			Verify("(x-1)^2*(x+1)^4*(x-2)^2", 3, 1024);
		}

		TEST_METHOD(PolynomialMapValue15)
		{
			Verify("(x+1)^4*(x2+x+1)", 2, 567);
		}
	};
}
