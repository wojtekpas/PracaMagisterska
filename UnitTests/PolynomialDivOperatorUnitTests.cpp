#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Lib/Parser.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(PolynomialDivOperatorUnitTests)
	{
		Parser parser;
		PolynomialMap result;
	public:

		void Verify(string input_p1, string input_p2)
		{
			Polynomial& empty = CreatePolynomial();
			Verify(input_p1, input_p2, empty);
		}

		void Verify(string input_p1, string input_p2, Polynomial& expectedOutput)
		{
			Polynomial& p1 = parser.ConvertToPolynomialRef(input_p1);
			Polynomial& p2 = parser.ConvertToPolynomialRef(input_p2);
			result = p1 / p2;

			Assert::AreEqual(expectedOutput.ToString(), result.ToString());
		}

		TEST_METHOD_INITIALIZE(Init)
		{
			result.Clear();
		}

		TEST_METHOD(PolynomialDivOperator01)
		{
			Verify("20", "20a");
		}

		TEST_METHOD(PolynomialDivOperator02)
		{
			result.SetValue(0, -20);
			Verify("20", "-1", result);
		}

		TEST_METHOD(PolynomialDivOperator03)
		{
			result.SetValue(1, -2);
			Verify("50a", "-25", result);
		}

		TEST_METHOD(PolynomialDivOperator04)
		{
			result.SetValue(0, -3);
			Verify("-21a", "7a", result);
		}

		TEST_METHOD(PolynomialDivOperator05)
		{
			result.SetValue(2, 6);
			Verify("12a2", "2", result);
		}

		TEST_METHOD(PolynomialDivOperator06)
		{
			result.SetValue(1, 2);
			Verify("-12a2", "-6a", result);
		}

		TEST_METHOD(PolynomialDivOperator07)
		{
			result.SetValue(0, 1);
			Verify("12a3", "12a3", result);
		}

		TEST_METHOD(PolynomialDivOperator08)
		{
			result.SetValue(2, 1);
			result.SetValue(1, 1);
			result.SetValue(0, 1);
			Verify("a3+a2+a", "a", result);
		}

		TEST_METHOD(PolynomialDivOperator09)
		{
			result.SetValue(1, -2);
			result.SetValue(0, 1);
			Verify("30a3-15a2", "-15a2", result);
		}

		TEST_METHOD(PolynomialDivOperator10)
		{
			result.SetValue(1, 6);
			Verify("-30a3-15a", "-5a2", result);
		}

		TEST_METHOD(PolynomialDivOperator11)
		{
			Polynomial& answer = parser.ConvertToPolynomialRef("x");
			Verify("x6-6x4-4x3+9x2+12x+4", "x5-4x3-2x2+3x+2", answer);
		}
	};
}