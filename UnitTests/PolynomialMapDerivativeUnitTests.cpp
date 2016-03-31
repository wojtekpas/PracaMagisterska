#pragma once
#include "stdafx.h"
/*
#include "CppUnitTest.h"
#include "../Lib/PolynomialMap.h"
#include "../Lib/Parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(PolynomialMapDerivativeTests)
	{
		Parser parser;
		PolynomialMap polynomialMap;
		PolynomialMap result;
	public:

		void Verify(string input)
		{
			PolynomialMap empty;
			Verify(input, empty);
		}

		void Verify(string input, PolynomialMap expectedOutput)
		{
			PolynomialMap p = parser.ConvertToPolynomialMap(input);
			PolynomialMap derivative = p.Derivative();

			Assert::AreEqual(expectedOutput.ToString(), derivative.ToString());
		}

		TEST_METHOD_INITIALIZE(Init)
		{
			result.Clear();
		}

		TEST_METHOD(PolynomialMapDerivative01)
		{
			Verify("1");
		}

		TEST_METHOD(PolynomialMapDerivative02)
		{
			Verify("5");
		}

		TEST_METHOD(PolynomialMapDerivative03)
		{
			Verify("10");
		}

		TEST_METHOD(PolynomialMapDerivative04)
		{
			Verify("101");
		}

		TEST_METHOD(PolynomialMapDerivative05)
		{
			Verify("123456789");
		}

		TEST_METHOD(PolynomialMapDerivative06)
		{
			Verify("0");
		}

		TEST_METHOD(PolynomialMapDerivative07)
		{
			Verify("-3");
		}

		TEST_METHOD(PolynomialMapDerivative08)
		{
			Verify("-101");
		}

		TEST_METHOD(PolynomialMapDerivative09)
		{
			result.SetValue(0, 1);
			Verify("a", result);
		}

		TEST_METHOD(PolynomialMapDerivative10)
		{
			result.SetValue(0, 2);
			Verify("2a", result);
		}

		TEST_METHOD(PolynomialMapDerivative11)
		{
			result.SetValue(0, 12);
			Verify("12a", result);
		}

		TEST_METHOD(PolynomialMapDerivative12)
		{
			result.SetValue(0, -500);
			Verify("-500a", result);
		}

		TEST_METHOD(PolynomialMapDerivative13)
		{
			result.SetValue(1, 2);
			Verify("a2", result);
		}

		TEST_METHOD(PolynomialMapDerivative14)
		{
			result.SetValue(2, 21);
			Verify("7a3", result);
		}

		TEST_METHOD(PolynomialMapDerivative15)
		{
			result.SetValue(129, 15600);
			Verify("120a130", result);
		}

		TEST_METHOD(PolynomialMapDerivative16)
		{
			result.SetValue(999, -500000);
			Verify("-500a1000", result);
		}

	};
}
*/
