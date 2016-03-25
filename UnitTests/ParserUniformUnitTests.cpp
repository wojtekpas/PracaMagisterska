#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Lib/PolynomialMap.h"
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
			Verify("a", "a");
		}

		TEST_METHOD(ParserUniform09)
		{
			Verify("aa");
		}

		TEST_METHOD(ParserUniform10)
		{
			Verify(" 1234", "1234");
		}

		TEST_METHOD(ParserUniform11)
		{
			Verify("100*a", "100*a");
		}

		TEST_METHOD(ParserUniform12)
		{
			Verify("100a", "100*a");
		}

		TEST_METHOD(ParserUniform13)
		{
			Verify("-50a", "-50*a");
		}

		TEST_METHOD(ParserUniform14)
		{
			Verify("a^2", "a^2");
		}

		TEST_METHOD(ParserUniform15)
		{
			Verify("a3", "a^3");
		}

		TEST_METHOD(ParserUniform16)
		{
			Verify("-5*a3", "-5*a^3");
		}

		TEST_METHOD(ParserUniform17)
		{
			Verify("a3*3", "a^3*3");
		}

		TEST_METHOD(ParserUniform18)
		{
			Verify("4a3", "4*a^3");
		}

		TEST_METHOD(ParserUniform19)
		{
			Verify("10 a2", "10*a^2");
		}

		TEST_METHOD(ParserUniform20)
		{
			Verify("2(4a+2)", "2*(4*a+2)");
		}

		TEST_METHOD(ParserUniform21)
		{
			Verify("(3a+1)(2a+1)", "(3*a+1)*(2*a+1)");
		}

		TEST_METHOD(ParserUniform22)
		{
			Verify("(3*a)2", "(3*a)^2");
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