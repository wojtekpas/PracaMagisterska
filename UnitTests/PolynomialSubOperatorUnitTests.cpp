#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Lib/Parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(PolynomialSubOperatorUnitTests)
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
			result = p1 - p2;

			Assert::AreEqual(expectedOutput.ToString(), result.ToString());
		}

		TEST_METHOD_INITIALIZE(Init)
		{
			result.Clear();
		}

		TEST_METHOD(PolynomialSubOperator01)
		{
			result.SetValue(0, -19);
			Verify("1", "20", result);
		}

		TEST_METHOD(PolynomialSubOperator02)
		{
			result.SetValue(0, -16);
			Verify("-11", "5", result);
		}

		TEST_METHOD(PolynomialSubOperator03)
		{
			result.SetValue(0, 14);
			Verify("-11", "-25", result);
		}

		TEST_METHOD(PolynomialSubOperator04)
		{
			result.SetValue(0, 36);
			Verify("11", "-25", result);
		}

		TEST_METHOD(PolynomialSubOperator05)
		{
			result.SetValue(1, 12);
			Verify("12a", "0", result);
		}

		TEST_METHOD(PolynomialSubOperator06)
		{
			result.SetValue(1, 17);
			Verify("12a", "-5a", result);
		}

		TEST_METHOD(PolynomialSubOperator07)
		{
			result.SetValue(3, -3);
			Verify("12a3", "15a3", result);
		}

		TEST_METHOD(PolynomialSubOperator08)
		{
			result.SetValue(3, 12);
			result.SetValue(2, 15);
			Verify("12a3", "-15a2", result);
		}

		TEST_METHOD(PolynomialSubOperator09)
		{
			result.SetValue(3, 12);
			result.SetValue(2, 19);
			Verify("12a3+4a2", "-15a2", result);
		}

		TEST_METHOD(PolynomialSubOperator10)
		{
			result.SetValue(3, 12);
			result.SetValue(2, 15);
			result.SetValue(1, -31);
			result.SetValue(0, 16);
			Verify("12a3+4a+8", "-15a2+30a+5a-5-3", result);
		}
	};
}
