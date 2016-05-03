#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Lib/Parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(PolynomialDerivativeTests)
	{
		Parser parser;
		Polynomial& result = CreatePolynomial();
	public:

		void Verify(string input)
		{
			Polynomial& empty = CreatePolynomial();
			Verify(input, empty);
		}

		void Verify(string input, Polynomial& expectedOutput)
		{
			Polynomial& p = parser.ConvertToPolynomial(input);
			Polynomial& derivative = p.Derivative();

			Assert::AreEqual(expectedOutput.ToString(), derivative.ToString());
		}

		TEST_METHOD_INITIALIZE(Init)
		{
			result.Clear();
		}

		TEST_METHOD(PolynomialDerivative01)
		{
			Verify("1");
		}

		TEST_METHOD(PolynomialDerivative02)
		{
			Verify("5");
		}

		TEST_METHOD(PolynomialDerivative03)
		{
			Verify("10");
		}

		TEST_METHOD(PolynomialDerivative04)
		{
			Verify("101");
		}

		TEST_METHOD(PolynomialDerivative05)
		{
			Verify("123456789");
		}

		TEST_METHOD(PolynomialDerivative06)
		{
			Verify("0");
		}

		TEST_METHOD(PolynomialDerivative07)
		{
			Verify("-3");
		}

		TEST_METHOD(PolynomialDerivative08)
		{
			Verify("-101");
		}

		TEST_METHOD(PolynomialDerivative09)
		{
			result.SetValue(0, 1);
			Verify("a", result);
		}

		TEST_METHOD(PolynomialDerivative10)
		{
			result.SetValue(0, 2);
			Verify("2a", result);
		}

		TEST_METHOD(PolynomialDerivative11)
		{
			result.SetValue(0, 12);
			Verify("12a", result);
		}

		TEST_METHOD(PolynomialDerivative12)
		{
			result.SetValue(0, -500);
			Verify("-500a", result);
		}

		TEST_METHOD(PolynomialDerivative13)
		{
			result.SetValue(1, 2);
			Verify("a2", result);
		}

		TEST_METHOD(PolynomialDerivative14)
		{
			result.SetValue(2, 21);
			Verify("7a3", result);
		}

		TEST_METHOD(PolynomialDerivative15)
		{
			result.SetValue(129, 15600);
			Verify("120a130", result);
		}

		TEST_METHOD(PolynomialDerivative16)
		{
			result.SetValue(999, -500000);
			Verify("-500a1000", result);
		}

		TEST_METHOD(PolynomialDerivative17)
		{
			result.SetValue(100, -101);
			result.SetValue(16, 34);
			result.SetValue(3, 4);
			result.SetValue(0, 1);
			Verify("-a101+2a17+a4+a", result);
		}
	};
}
