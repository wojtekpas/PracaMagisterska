#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Lib/Polynomial.h"
#include "../Lib/Parser.h"
/*
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(PolynomialSumOperatorUnitTests)
	{
		Parser parser;
		Polynomial& polynomial;
		Polynomial& result;
	public:

		void Verify(string input_p1, string input_p2)
		{
			PolynomialMap polynomialMap;
			Polynomial& empty = polynomialMap.CreatePolynomial();
			Verify(input_p1, input_p2, empty);
		}

		void Verify(string input_p1, string input_p2, Polynomial& expectedOutput)
		{
			Polynomial& p1 = parser.ConvertToPolynomial(input_p1);
			Polynomial& p2 = parser.ConvertToPolynomial(input_p2);
			Polynomial& result = p1 + p2;

			Assert::AreEqual(expectedOutput.ToString(), result.ToString());
		}

		TEST_METHOD_INITIALIZE(Init)
		{
			result.Clear();
		}

		TEST_METHOD(PolynomialSumOperator01)
		{
			result.SetValue(0, 21);
			Verify("1", "20", result );
		}

		TEST_METHOD(PolynomialSumOperator02)
		{
			result.SetValue(0,-6);
			Verify("-11", "5", result);
		}

		TEST_METHOD(PolynomialSumOperator03)
		{
			result.SetValue(0, -36);
			Verify("-11", "-25", result);
		}

		TEST_METHOD(PolynomialSumOperator04)
		{
			result.SetValue(0, -14);
			Verify("11", "-25", result);
		}

		TEST_METHOD(PolynomialSumOperator05)
		{
			result.SetValue(1, 12);
			Verify("12a", "0", result);
		}

		TEST_METHOD(PolynomialSumOperator06)
		{
			result.SetValue(1, 7);
			Verify("12a", "-5a", result);
		}

		TEST_METHOD(PolynomialSumOperator07)
		{
			result.SetValue(3, 27);
			Verify("12a3", "15a3", result);
		}

		TEST_METHOD(PolynomialSumOperator08)
		{
			result.SetValue(3, 12);
			result.SetValue(2, -15);
			Verify("12a3", "-15a2", result);
		}

		TEST_METHOD(PolynomialSumOperator09)
		{
			result.SetValue(3, 12);
			result.SetValue(2, -11);
			Verify("12a3+4a2", "-15a2", result);
		}

		TEST_METHOD(PolynomialSumOperator10)
		{
			result.SetValue(3, 12);
			result.SetValue(2, -15);
			result.SetValue(1, 39);
			Verify("12a3+4a+8", "-15a2+30a+5a-5-3", result);
		}
	};
}
*/
