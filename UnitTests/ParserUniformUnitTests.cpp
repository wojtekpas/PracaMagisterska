#pragma once
#include "stdafx.h"

#include "CppUnitTest.h"
#include "../Lib/Parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
	TEST_CLASS(ParserUniformUnitTests)
	{
		Parser parser;
	public:
		void Verify(string input, string expectedOutput = StringManager::EmptyString())
		{
			string result = parser.UniformInputString(input);

			Assert::AreEqual(expectedOutput, result);
		}

		TEST_METHOD(ParserUniform01)
		{
			Verify(StringManager::EmptyString());
		}

		TEST_METHOD(ParserUniform02)
		{
			Verify("!");
		}

		TEST_METHOD(ParserUniform03)
		{
			Verify("!@#");
		}

		TEST_METHOD(ParserUniform04)
		{
			Verify("1", "1");
		}

		TEST_METHOD(ParserUniform05)
		{
			Verify("123", "123");;
		}

		TEST_METHOD(ParserUniform06)
		{
			Verify("-1", "-1");
		}

		TEST_METHOD(ParserUniform07)
		{
			Verify("-123", "-123");
		}

		TEST_METHOD(ParserUniform08)
		{
			Verify("x", "x");
		}

		TEST_METHOD(ParserUniform09)
		{
			Verify("xx");
		}

		TEST_METHOD(ParserUniform10)
		{
			Verify(" 1234", "1234");
		}

		TEST_METHOD(ParserUniform11)
		{
			Verify("100*x", "100*x");
		}

		TEST_METHOD(ParserUniform12)
		{
			Verify("100x", "100*x");
		}

		TEST_METHOD(ParserUniform13)
		{
			Verify("-50x", "-50*x");
		}

		TEST_METHOD(ParserUniform14)
		{
			Verify("x^2", "x^2");
		}

		TEST_METHOD(ParserUniform15)
		{
			Verify("x3", "x^3");
		}

		TEST_METHOD(ParserUniform16)
		{
			Verify("-5*x3", "-5*x^3");
		}

		TEST_METHOD(ParserUniform17)
		{
			Verify("x3*3", "x^3*3");
		}

		TEST_METHOD(ParserUniform18)
		{
			Verify("4x3", "4*x^3");
		}

		TEST_METHOD(ParserUniform19)
		{
			Verify("10 x2", "10*x^2");
		}

		TEST_METHOD(ParserUniform20)
		{
			Verify("2(4x+2)", "2*(4*x+2)");
		}

		TEST_METHOD(ParserUniform21)
		{
			Verify("(3x+1)(2x+1)", "(3*x+1)*(2*x+1)");
		}

		TEST_METHOD(ParserUniform22)
		{
			Verify("(3*x)2", "(3*x)^2");
		}

		TEST_METHOD(ParserUniform23)
		{
			Verify("3*-2");
		}

		TEST_METHOD(ParserUniform24)
		{
			Verify("(-1)2", "(-1)^2");
		}
	};
}