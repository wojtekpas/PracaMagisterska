#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Lib/PolynomialMap.h"
#include "../Lib/Parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(PolynomialMapNWDUnitTests)
	{
		Parser parser;
	public:

		void Verify(string input, string output)
		{
			PolynomialMap p1 = parser.ConvertToPolynomialMap(input);
			PolynomialMap p2 = parser.ConvertToPolynomialMap(output);
			PolynomialMap nwd = p1.PolynomialAfterEliminationOfMultipleRoots();
			nwd.Normalize();
			Assert::AreEqual(p2.ToString(), nwd.ToString());
		}

		TEST_METHOD(PolynomialMapNWD01)
		{
			Verify("20", "1");
		}

		TEST_METHOD(PolynomialMapNWD02)
		{
			Verify("2a", "1");
		}

		TEST_METHOD(PolynomialMapNWD03)
		{
			Verify("a2", "a");
		}

		TEST_METHOD(PolynomialMapNWD04)
		{
			Verify("-a3", "a2");
		}

		TEST_METHOD(PolynomialMapNWD05)
		{
			Verify("12a2", "a");
		}

		TEST_METHOD(PolynomialMapNWD06)
		{
			Verify("(a-1)^2", "a-1");
		}

		TEST_METHOD(PolynomialMapNWD07)
		{
			Verify("(a+3)^4", "(a+3)^3");
		}

		TEST_METHOD(PolynomialMapNWD08)
		{
			Verify("(a+1)(a+2)", "1");
		}

		TEST_METHOD(PolynomialMapNWD09)
		{
			Verify("(a+3)^2*(a+1)", "a+3");
		}

		TEST_METHOD(PolynomialMapNWD10)
		{
			Verify("(a+3)^2*(a+1)^3", "(a+3)(a+1)^2");
		}

		TEST_METHOD(PolynomialMapNWD11)
		{
			Verify("a^3*(a+5)^10", "a2*(a+1)^9");
		}

	};
}
