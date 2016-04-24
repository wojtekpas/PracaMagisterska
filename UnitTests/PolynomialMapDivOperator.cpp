#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Lib/PolynomialMap.h"
#include "../Lib/Parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(PolynomialMapDivOperatorUnitTests)
	{
		Parser parser;
		PolynomialMap polynomialMap;
		PolynomialMap result;
	public:

		void Verify(string input_p1, string input_p2)
		{
			PolynomialMap empty;
			Verify(input_p1, input_p2, empty);
		}

		void Verify(string input_p1, string input_p2, PolynomialMap expectedOutput)
		{
			PolynomialMap p1 = parser.ConvertToPolynomialMap(input_p1);
			PolynomialMap p2 = parser.ConvertToPolynomialMap(input_p2);
			PolynomialMap result = p1 / p2;

			Assert::AreEqual(expectedOutput.ToString(), result.ToString());
		}

		TEST_METHOD_INITIALIZE(Init)
		{
			result.Clear();
		}

		TEST_METHOD(PolynomialMapDivOperator01)
		{
			Verify("20", "20a");
		}

		TEST_METHOD(PolynomialMapDivOperator02)
		{
			result.SetValue(0, -20);
			Verify("20", "-1", result);
		}

		TEST_METHOD(PolynomialMapDivOperator03)
		{
			result.SetValue(1, -2);
			Verify("50a", "-25", result);
		}

		TEST_METHOD(PolynomialMapDivOperator04)
		{
			result.SetValue(0, -3);
			Verify("-21a", "7a", result);
		}

		TEST_METHOD(PolynomialMapDivOperator05)
		{
			result.SetValue(2, 6);
			Verify("12a2", "2", result);
		}

		TEST_METHOD(PolynomialMapDivOperator06)
		{
			result.SetValue(1, 2);
			Verify("-12a2", "-6a", result);
		}

		TEST_METHOD(PolynomialMapDivOperator07)
		{
			result.SetValue(0, 1);
			Verify("12a3", "12a3", result);
		}

		TEST_METHOD(PolynomialMapDivOperator08)
		{
			result.SetValue(2, 1);
			result.SetValue(1, 1);
			result.SetValue(0, 1);
			Verify("a3+a2+a", "a", result);
		}

		TEST_METHOD(PolynomialMapDivOperator09)
		{
			result.SetValue(1, -2);
			result.SetValue(0, 1);
			Verify("30a3-15a2", "-15a2", result);
		}

		TEST_METHOD(PolynomialMapDivOperator10)
		{
			result.SetValue(1, 6);
			Verify("-30a3-15a", "-5a2", result);
		}

		TEST_METHOD(PolynomialMapDivOperator11)
		{
			PolynomialMap answer = parser.ConvertToPolynomialMap("x");
			Verify("x6-6x4-4x3+9x2+12x+4", "x5-4x3-2x2+3x+2", answer);
		}
	};
}
