#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Lib/PolynomialMap.h"
#include "../Lib/Parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(PolynomialMapSumOperatorUnitTests)
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
			PolynomialMap result = p1 + p2;

			Assert::AreEqual(expectedOutput.ToString(), result.ToString());
		}

		TEST_METHOD_INITIALIZE(Init)
		{
			result.Clear();
		}

		TEST_METHOD(PolynomialMapSumOperator01)
		{
			result.SetValue(0, 21);
			Verify("1", "20", result );
		}

		TEST_METHOD(PolynomialMapSumOperator02)
		{
			result.SetValue(0,-6);
			Verify("-11", "5", result);
		}

		TEST_METHOD(PolynomialMapSumOperator03)
		{
			result.SetValue(0, -36);
			Verify("-11", "-25", result);
		}

		TEST_METHOD(PolynomialMapSumOperator04)
		{
			result.SetValue(0, -14);
			Verify("11", "-25", result);
		}

		TEST_METHOD(PolynomialMapSumOperator05)
		{
			result.SetValue(1, 12);
			Verify("12a", "0", result);
		}

		TEST_METHOD(PolynomialMapSumOperator06)
		{
			result.SetValue(1, 7);
			Verify("12a", "-5a", result);
		}

		TEST_METHOD(PolynomialMapSumOperator07)
		{
			result.SetValue(3, 27);
			Verify("12a3", "15a3", result);
		}

		TEST_METHOD(PolynomialMapSumOperator08)
		{
			result.SetValue(3, 12);
			result.SetValue(2, -15);
			Verify("12a3", "-15a2", result);
		}

		TEST_METHOD(PolynomialMapSumOperator09)
		{
			result.SetValue(3, 12);
			result.SetValue(2, -11);
			Verify("12a3+4a2", "-15a2", result);
		}

		TEST_METHOD(PolynomialMapSumOperator10)
		{
			result.SetValue(3, 12);
			result.SetValue(2, -15);
			result.SetValue(1, 39);
			Verify("12a3+4a+8", "-15a2+30a+5a-5-3", result);
		}
	};
}
