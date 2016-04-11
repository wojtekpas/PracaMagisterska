#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Lib/PolynomialMap.h"
#include "../Lib/Parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(PolynomialMapModOperatorUnitTests)
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
			PolynomialMap result = p1 % p2;

			Assert::AreEqual(expectedOutput.ToString(), result.ToString());
		}

		TEST_METHOD_INITIALIZE(Init)
		{
			result.Clear();
		}

		TEST_METHOD(PolynomialMapModOperator01)
		{
			result.SetValue(0, 20);
			Verify("20", "20a", result);
		}

		TEST_METHOD(PolynomialMapModOperator02)
		{
			Verify("20", "-1");
		}

		TEST_METHOD(PolynomialMapModOperator03)
		{
			Verify("50a", "-25");
		}

		TEST_METHOD(PolynomialMapModOperator04)
		{
			Verify("-21a", "7a");
		}

		TEST_METHOD(PolynomialMapModOperator05)
		{
			Verify("12a2", "3");
		}

		TEST_METHOD(PolynomialMapModOperator06)
		{
			Verify("-12a2", "-6a");
		}

		TEST_METHOD(PolynomialMapModOperator07)
		{
			Verify("12a3", "12a3");
		}

		TEST_METHOD(PolynomialMapModOperator08)
		{
			Verify("a3+a2+a", "a");
		}

		TEST_METHOD(PolynomialMapModOperator09)
		{
			Verify("30a3-15a2", "-15a2");
		}

		TEST_METHOD(PolynomialMapModOperator10)
		{
			result.SetValue(1, -15);
			Verify("-30a3-15a", "-5a2", result);
		}

		TEST_METHOD(PolynomialMapModOperator11)
		{
			result.SetValue(0, 14);
			Verify("22a+14", "11a", result);
		}

		TEST_METHOD(PolynomialMapModOperator12)
		{
			result.SetValue(0, 1);
			Verify("(a+2)^3+1", "a+2", result);
		}

		TEST_METHOD(PolynomialMapModOperator13)
		{
			result.SetValue(0, 10);
			Verify("a3+a2+a1+11", "a2+1", result);
		}

		TEST_METHOD(PolynomialMapModOperator14)
		{
			result.SetValue(0, 10);
			Verify("a3+a2+a1+11", "a2+1", result);
		}

		TEST_METHOD(PolynomialMapModOperator15)
		{
			result.SetValue(1, -3);
			result.SetValue(0, 2);
			Verify("a4-4a3+6a2-7a+3", "(a-1)^2", result);
		}

		TEST_METHOD(PolynomialMapModOperator16)
		{
			PolynomialMap answer = parser.ConvertToPolynomialMap("-2(x4+x3-3x2-5x-2)");
			Verify("x6-6x4-4x3+9x2+12x+4", "x5-4x3-2x2+3x+2", answer);
		}

		TEST_METHOD(PolynomialMapModOperator17)
		{
			string input_p1 = "x6-6x4-4x3+9x2+12x+4";
			string input_derivative = "x5-4x3-2x2+3x+2";
			PolynomialMap six = parser.ConvertToPolynomialMap("6");
			PolynomialMap negativeTwo = parser.ConvertToPolynomialMap("-2");
			PolynomialMap p1 = parser.ConvertToPolynomialMap(input_p1);
			PolynomialMap derivative = p1.Derivative();
			derivative /= six;
			PolynomialMap nwd = p1.Nwd(derivative);
			nwd /= negativeTwo;
			PolynomialMap p1AfterEliminationOfMultipleRoots = p1 / nwd;
			PolynomialMap tmp1 = derivative % nwd;
			PolynomialMap answerDerivative = parser.ConvertToPolynomialMap(input_derivative);
			PolynomialMap answerNwd = parser.ConvertToPolynomialMap("x4+x3-3x2-5x-2");
			PolynomialMap answerP1After = parser.ConvertToPolynomialMap("x2-x-2");
			PolynomialMap answerTmp1 = parser.ConvertToPolynomialMap("Is Zero");

			Assert::AreEqual(answerDerivative.ToString(), derivative.ToString());
			Assert::AreEqual(answerNwd.ToString(), nwd.ToString());
			Assert::AreEqual(answerP1After.ToString(), p1AfterEliminationOfMultipleRoots.ToString());
			Assert::AreEqual(answerTmp1.ToString(), tmp1.ToString());
		}
	};
}
