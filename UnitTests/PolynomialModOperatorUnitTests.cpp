#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Lib/Parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(PolynomialModOperatorUnitTests)
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
			result = p1 % p2;

			Assert::AreEqual(expectedOutput.ToString(), result.ToString());
		}

		TEST_METHOD_INITIALIZE(Init)
		{
			result.Clear();
		}

		TEST_METHOD(PolynomialModOperator01)
		{
			result.SetValue(0, 20);
			Verify("20", "20a", result);
		}

		TEST_METHOD(PolynomialModOperator02)
		{
			Verify("20", "-1");
		}

		TEST_METHOD(PolynomialModOperator03)
		{
			Verify("50a", "-25");
		}

		TEST_METHOD(PolynomialModOperator04)
		{
			Verify("-21a", "7a");
		}

		TEST_METHOD(PolynomialModOperator05)
		{
			Verify("12a2", "3");
		}

		TEST_METHOD(PolynomialModOperator06)
		{
			Verify("-12a2", "-6a");
		}

		TEST_METHOD(PolynomialModOperator07)
		{
			Verify("12a3", "12a3");
		}

		TEST_METHOD(PolynomialModOperator08)
		{
			Verify("a3+a2+a", "a");
		}

		TEST_METHOD(PolynomialModOperator09)
		{
			Verify("30a3-15a2", "-15a2");
		}

		TEST_METHOD(PolynomialModOperator10)
		{
			result.SetValue(1, -15);
			Verify("-30a3-15a", "-5a2", result);
		}

		TEST_METHOD(PolynomialModOperator11)
		{
			result.SetValue(0, 14);
			Verify("22a+14", "11a", result);
		}

		TEST_METHOD(PolynomialModOperator12)
		{
			result.SetValue(0, 1);
			Verify("(a+2)^3+1", "a+2", result);
		}

		TEST_METHOD(PolynomialModOperator13)
		{
			result.SetValue(0, 10);
			Verify("a3+a2+a1+11", "a2+1", result);
		}

		TEST_METHOD(PolynomialModOperator14)
		{
			result.SetValue(0, 10);
			Verify("a3+a2+a1+11", "a2+1", result);
		}

		TEST_METHOD(PolynomialModOperator15)
		{
			result.SetValue(1, -3);
			result.SetValue(0, 2);
			Verify("a4-4a3+6a2-7a+3", "(a-1)^2", result);
		}

		TEST_METHOD(PolynomialModOperator16)
		{
			Polynomial& answer = parser.ConvertToPolynomialRef("-2(x4+x3-3x2-5x-2)");
			Verify("x6-6x4-4x3+9x2+12x+4", "x5-4x3-2x2+3x+2", answer);
		}

		TEST_METHOD(PolynomialModOperator17)
		{
			string input_p1 = "x6-6x4-4x3+9x2+12x+4";
			string input_derivative = "x5-4x3-2x2+3x+2";
			Polynomial& p1 = parser.ConvertToPolynomialRef(input_p1);
			Polynomial& derivative = p1.Derivative();
			derivative.Normalize();
			Polynomial& nwd = p1.Nwd(p1, derivative);
			nwd.Normalize();
			Polynomial& p1AfterEliminationOfMultipleRoots = p1 / nwd;
			Polynomial& tmp1 = derivative % nwd;
			Polynomial& answerDerivative = parser.ConvertToPolynomialRef(input_derivative);
			Polynomial& answerNwd = parser.ConvertToPolynomialRef("x4+x3-3x2-5x-2");
			Polynomial& answerP1After = parser.ConvertToPolynomialRef("x2-x-2");
			Polynomial& answerTmp1 = parser.ConvertToPolynomialRef("Is Zero");

			Assert::AreEqual(answerDerivative.ToString(), derivative.ToString());
			Assert::AreEqual(answerNwd.ToString(), nwd.ToString());
			Assert::AreEqual(answerP1After.ToString(), p1AfterEliminationOfMultipleRoots.ToString());
			Assert::AreEqual(answerTmp1.ToString(), tmp1.ToString());
		}
	};
}
