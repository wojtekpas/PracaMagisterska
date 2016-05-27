#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Lib/Parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(PolynomialRootsUnitTests)
	{
		Parser parser;
		Number a;
		Number b;
		vector<Number> polynomialRoots;
	public:

		void Verify(string input)
		{
			Polynomial& p = parser.ConvertToPolynomial(input);
			Polynomial& p2 = p.PolynomialAfterEliminationOfMultipleRoots();
			Polynomial& polynomialAfterElimination = p2;
			polynomialAfterElimination.Normalize();
			vector<Number> roots = polynomialAfterElimination.FindRoots(a, b);
			//vector<mpq_t> roots_mpq;
			//for (int i = 0; i < roots.size(); i++)
				//roots_mpq.push_back(roots[i].value);
			//sort(roots_mpq.begin(), roots_mpq.end());
			polynomialRoots = SortNumbers(polynomialRoots);
			roots = SortNumbers(roots);
			string expectedRoots = to_string(polynomialRoots.size()) + ": ";
			string actualRoots = to_string(roots.size()) + ": ";
			for (int i = 0; i < polynomialRoots.size(); i++)
				expectedRoots += polynomialRoots[i].ToString() + ", ";
			for (int i = 0; i < roots.size(); i++)
				actualRoots += roots[i].ToString() + ", ";
			Assert::AreEqual(expectedRoots, actualRoots);
		}

		TEST_METHOD_INITIALIZE(Init)
		{
			a.SetMaxNegativeValue();
			b.SetMaxValue();
			polynomialRoots.clear();
		}

		TEST_METHOD(PolynomialRoots01)
		{
			Verify("20");
		}

		TEST_METHOD(PolynomialRoots02)
		{
			polynomialRoots.push_back(Number(0));
			Verify("2a");
		}

		TEST_METHOD(PolynomialRoots03)
		{
			polynomialRoots.push_back(Number(0));
			Verify("a2");
		}

		TEST_METHOD(PolynomialRoots04)
		{
			polynomialRoots.push_back(Number(0));
			Verify("-a3");
		}

		TEST_METHOD(PolynomialRoots05)
		{
			polynomialRoots.push_back(Number(0));
			Verify("12a2");
		}

		TEST_METHOD(PolynomialRoots06)
		{
			polynomialRoots.push_back(Number(1));
			Verify("(a-1)^2");
		}

		TEST_METHOD(PolynomialRoots07)
		{
			polynomialRoots.push_back(Number(-3));
			Verify("(a+3)^4");
		}

		TEST_METHOD(PolynomialRoots08)
		{
			polynomialRoots.push_back(Number(-2));
			polynomialRoots.push_back(Number(-1));
			Verify("(a+1)(a+2)");
		}

		TEST_METHOD(PolynomialRoots09)
		{
			polynomialRoots.push_back(Number(-3));
			polynomialRoots.push_back(Number(-1));
			Verify("(a+3)^2*(a+1)");
		}

		TEST_METHOD(PolynomialRoots10)
		{
			polynomialRoots.push_back(Number(-3));
			polynomialRoots.push_back(Number(-1));
			Verify("(a+3)^2*(a+1)^3");
		}

		TEST_METHOD(PolynomialRoots11)
		{
			polynomialRoots.push_back(Number(-2));
			polynomialRoots.push_back(Number(0));
			Verify("a3*(a+2)^1");
		}

		TEST_METHOD(PolynomialRoots12)
		{
			polynomialRoots.push_back(Number(-1));
			polynomialRoots.push_back(Number(2));
			Verify("(x+1)^4*(x-2)^2");
		}

		TEST_METHOD(PolynomialRoots13)
		{
			polynomialRoots.push_back(Number(-1));
			polynomialRoots.push_back(Number(1));
			polynomialRoots.push_back(Number(2));
			Verify("(x-1)^2*(x+1)^2*(x-2)^2");
		}

		TEST_METHOD(PolynomialRoots14)
		{
			polynomialRoots.push_back(Number(-2));
			polynomialRoots.push_back(Number(-1));
			polynomialRoots.push_back(Number(1));
			Verify("(x+1)^2*(x-1)^4*(x+2)^2");
		}

		TEST_METHOD(PolynomialRoots15)
		{
			polynomialRoots.push_back(Number(-1));
			Verify("(x+1)^4*(x2+x+1)");
		}

		TEST_METHOD(PolynomialRoots16)
		{
			a = -1;
			polynomialRoots.push_back(Number(0));
			Verify("12a2");
		}

		TEST_METHOD(PolynomialRoots17)
		{
			b = 4;
			polynomialRoots.push_back(Number(1));
			Verify("(a-1)^2");
		}

		TEST_METHOD(PolynomialRoots18)
		{
			a = -20;
			b = 10;
			polynomialRoots.push_back(Number(-3));
			Verify("(a+3)^4");
		}

		TEST_METHOD(PolynomialRoots19)
		{
			a = -1;
			b = 4;
			polynomialRoots.push_back(Number(0));
			Verify("a3*(a+2)^10");
		}

		TEST_METHOD(PolynomialRoots20)
		{
			a = 0;
			b = 1;
			Verify("(x+1)^4*(x-2)^2");
		}

		TEST_METHOD(PolynomialRoots21)
		{
			b = 2;
			polynomialRoots.push_back(Number(-1));
			polynomialRoots.push_back(Number(1));
			Verify("(x-1)^2*(x+1)^2*(x-3)^2");
		}

		TEST_METHOD(PolynomialRoots22)
		{
			a = Number(-1.3);
			b = Number(2.1);
			polynomialRoots.push_back(Number(-1.25));
			polynomialRoots.push_back(Number(1.25));
			Verify("(4x-5)^5*(4x+5)^2");
		}

		TEST_METHOD(PolynomialRoots23)
		{
			a = Number(-10);
			b = Number(10);
			polynomialRoots.push_back(Number(1));
			Verify("a-1");
		}
	};
}
