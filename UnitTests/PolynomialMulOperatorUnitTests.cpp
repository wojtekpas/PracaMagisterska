#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Lib/Parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(PolynomialMulOperatorUnitTests)
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
			Polynomial& p1 = parser.ConvertToPolynomial(input_p1);
			Polynomial& p2 = parser.ConvertToPolynomial(input_p2);
			result = p1 * p2;

			Assert::AreEqual(expectedOutput.ToString(), result.ToString());
		}

		TEST_METHOD_INITIALIZE(Init)
		{
			result.Clear();
		}

		TEST_METHOD(PolynomialMulOperator01)
		{
			result.SetValue(0, 20);
			Verify("1", "20", result);
		}

		TEST_METHOD(PolynomialMulOperator02)
		{
			result.SetValue(0, -55);
			Verify("-11", "5", result);
		}

		TEST_METHOD(PolynomialMulOperator03)
		{
			result.SetValue(0, 275);
			Verify("-11", "-25", result);
		}

		TEST_METHOD(PolynomialMulOperator04)
		{
			result.SetValue(1, -14);
			Verify("-2a", "7", result);
		}

		TEST_METHOD(PolynomialMulOperator05)
		{
			result.SetValue(1, 12);
			Verify("12a", "0");
		}

		TEST_METHOD(PolynomialMulOperator06)
		{
			result.SetValue(2, -60);
			Verify("12a", "-5a", result);
		}

		TEST_METHOD(PolynomialMulOperator07)
		{
			result.SetValue(6, 180);
			Verify("12a3", "15a3", result);
		}

		TEST_METHOD(PolynomialMulOperator08)
		{
			result.SetValue(5, -180);
			Verify("12a3", "-15a2", result);
		}

		TEST_METHOD(PolynomialMulOperator09)
		{
			result.SetValue(5, -180);
			result.SetValue(4, -60);
			Verify("12a3+4a2", "-15a2", result);
		}

		TEST_METHOD(PolynomialMulOperator10)
		{
			result.SetValue(5, -180);
			result.SetValue(4, 420);
			result.SetValue(3, -156);
			result.SetValue(2, 20);
			result.SetValue(1, 248);
			result.SetValue(0, -64);
			Verify("12a3+4a+8", "-15a2+35a-8", result);
		}
	};
}
