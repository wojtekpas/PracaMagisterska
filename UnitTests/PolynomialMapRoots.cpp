#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Lib/PolynomialMap.h"
#include "../Lib/Parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(PolynomialMapRootsUnitTests)
	{
		Parser parser;
		Number a;
		Number b;
		vector<Number> polynomialRoots;
	public:

		void Verify(string input)
		{
			PolynomialMap p = parser.ConvertToPolynomialMap(input);
			PolynomialMap polynomialAfterElimination = p.PolynomialAfterEliminationOfMultipleRoots();
			polynomialAfterElimination.Normalize();
			vector<Number> roots = polynomialAfterElimination.FindRoots(a, b);
			vector<double> roots_double;
			for (int i = 0; i < roots.size(); i++)
				roots_double.push_back(roots[i].GetValue());
			sort(roots_double.begin(), roots_double.end());
			string expectedRoots = to_string(polynomialRoots.size()) + ": ";
			string actualRoots = to_string(roots_double.size()) + ": ";
			for (int i = 0; i < polynomialRoots.size(); i++)
				expectedRoots += polynomialRoots[i].ToString() + ", ";
			for (int i = 0; i < roots_double.size(); i++)
				actualRoots += to_string(roots_double[i]) + ", ";
			Assert::AreEqual(expectedRoots, actualRoots);
		}

		TEST_METHOD_INITIALIZE(Init)
		{
			a.SetMaxNegativeValue();
			b.SetMaxValue();
			polynomialRoots.clear();
		}

		TEST_METHOD(PolynomialMapRoots01)
		{
			Verify("20");
		}

		TEST_METHOD(PolynomialMapRoots02)
		{
			polynomialRoots.push_back(Number(0));
			Verify("2a");
		}

		TEST_METHOD(PolynomialMapRoots03)
		{
			polynomialRoots.push_back(Number(0));
			Verify("a2");
		}

		TEST_METHOD(PolynomialMapRoots04)
		{
			polynomialRoots.push_back(Number(0));
			Verify("-a3");
		}

		TEST_METHOD(PolynomialMapRoots05)
		{
			polynomialRoots.push_back(Number(0));
			Verify("12a2");
		}

		TEST_METHOD(PolynomialMapRoots06)
		{
			polynomialRoots.push_back(Number(1));
			Verify("(a-1)^2");
		}

		TEST_METHOD(PolynomialMapRoots07)
		{
			polynomialRoots.push_back(Number(-3));
			Verify("(a+3)^4");
		}

		TEST_METHOD(PolynomialMapRoots08)
		{
			polynomialRoots.push_back(Number(-2));
			polynomialRoots.push_back(Number(-1));
			Verify("(a+1)(a+2)");
		}

		TEST_METHOD(PolynomialMapRoots09)
		{
			polynomialRoots.push_back(Number(-3));
			polynomialRoots.push_back(Number(-1));
			Verify("(a+3)^2*(a+1)");
		}

		TEST_METHOD(PolynomialMapRoots10)
		{
			polynomialRoots.push_back(Number(-3));
			polynomialRoots.push_back(Number(-1));
			Verify("(a+3)^2*(a+1)^3");
		}

		TEST_METHOD(PolynomialMapRoots11)
		{
			polynomialRoots.push_back(Number(-2));
			polynomialRoots.push_back(Number(0));
			Verify("a3*(a+2)^10");
		}

		TEST_METHOD(PolynomialMapRoots12)
		{
			polynomialRoots.push_back(Number(-1));
			polynomialRoots.push_back(Number(2));
			Verify("(x+1)^4*(x-2)^2");
		}

		TEST_METHOD(PolynomialMapRoots13)
		{
			polynomialRoots.push_back(Number(-1));
			polynomialRoots.push_back(Number(1));
			polynomialRoots.push_back(Number(2));
			Verify("(x-1)^2*(x+1)^2*(x-2)^2");
		}

		TEST_METHOD(PolynomialMapRoots14)
		{
			polynomialRoots.push_back(Number(-1));
			polynomialRoots.push_back(Number(1));
			polynomialRoots.push_back(Number(2));
			Verify("(x-1)^2*(x+1)^4*(x-2)^2");
		}

		TEST_METHOD(PolynomialMapRoots15)
		{
			polynomialRoots.push_back(Number(-1));
			Verify("(x+1)^4*(x2+x+1)");
		}

		TEST_METHOD(PolynomialMapRoots16)
		{
			a = -1;
			polynomialRoots.push_back(Number(0));
			Verify("12a2");
		}

		TEST_METHOD(PolynomialMapRoots17)
		{
			b = 4;
			polynomialRoots.push_back(Number(1));
			Verify("(a-1)^2");
		}

		TEST_METHOD(PolynomialMapRoots18)
		{
			a = -20;
			b = 10;
			polynomialRoots.push_back(Number(-3));
			Verify("(a+3)^4");
		}

		TEST_METHOD(PolynomialMapRoots19)
		{
			a = -1;
			b = 4;
			polynomialRoots.push_back(Number(0));
			Verify("a3*(a+2)^10");
		}

		TEST_METHOD(PolynomialMapRoots20)
		{
			a = 0;
			b = 1;
			Verify("(x+1)^4*(x-2)^2");
		}

		TEST_METHOD(PolynomialMapRoots21)
		{
			b = 2;
			polynomialRoots.push_back(Number(-1));
			polynomialRoots.push_back(Number(1));
			Verify("(x-1)^2*(x+1)^2*(x-3)^2");
		}
	};
}
