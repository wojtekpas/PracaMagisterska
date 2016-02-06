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
		void Verify(string input, string expected)
		{
			string result = parser.UniformInputString(input);

			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(ParserUniform_EmptyString_ShouldReturn_EmptyString)
		{
			Verify(StringManager::EmptyString(), StringManager::EmptyString());
		}

		TEST_METHOD(ParserUniform_SingleIllegalChar_ShouldReturn_EmptyString)
		{
			Verify("!", StringManager::EmptyString());
		}

		TEST_METHOD(ParserUniform_ThreeIllegalChars_ShouldReturn_EmptyString)
		{
			Verify("!@#", StringManager::EmptyString());
		}

		TEST_METHOD(ParserUniform_SinglePositiveDigit_ShouldReturn_SinglePositiveDigit)
		{
			Verify("1", "1");
		}

		TEST_METHOD(ParserUniform_PositiveNumber_ShouldReturn_PositiveNumber)
		{
			Verify("123", "123");;
		}

		TEST_METHOD(ParserUniform_SingleNegativeDigit_ShouldReturn_SingleNegativeDigit)
		{
			Verify("-1", "-1");
		}

		TEST_METHOD(ParserUniform_NegativeNumber_ShouldReturn_NegativeNumber)
		{
			Verify("-123", "-123");
		}

		TEST_METHOD(ParserUniform_SingleVar_ShouldReturn_SingleVar)
		{
			Verify("a", "a");
		}

		TEST_METHOD(ParserUniform_TwoVarsInARow_ShouldReturn_EmptyString)
		{
			Verify("aa", StringManager::EmptyString());
		}

		TEST_METHOD(ParserUniform_NumberStartsFromBlankSpace_ShouldReturn_ValueWithoutWhitespaces)
		{
			const string input = " 1234";
			const string expected = input.substr(1);

			string result = parser.UniformInputString(input);

			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(a1)
		{
			const string input = "100*a";
			const string expected = "100*a";
			string result = parser.UniformInputString(input);

			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(a2)
		{
			const string input = "100a";
			const string expected = "100*a";
			string result = parser.UniformInputString(input);

			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(a3)
		{
			const string input = "10 0 a";
			string result = parser.UniformInputString(input);

			Assert::AreEqual(StringManager::EmptyString(), result);
		}
	};
}