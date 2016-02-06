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
		const string SingleIllegalChar = "%";
		const string ThreeIllegalChars = "!@#";
		const string SinglePositiveDigit = "1";
		const string PositiveNumber = "12345";
		const string SingleNegativeDigit = "-1";
		const string NegativeNumber = "-12345";
		const string SingleVar = string(1,CharsConstants::Var);
		const string TwoVarsInARow = string(2, CharsConstants::Var);
	public:	
		TEST_METHOD(ParserUniform_EmptyString_ShouldReturn_EmptyString)
		{
			string result = parser.UniformInputString(StringManager::EmptyString());

			Assert::AreEqual(StringManager::EmptyString(), result);
		}

		TEST_METHOD(ParserUniform_SingleIllegalChar_ShouldReturn_EmptyString)
		{
			string result = parser.UniformInputString(SingleIllegalChar);

			Assert::AreEqual(StringManager::EmptyString(), result);
		}

		TEST_METHOD(ParserUniform_ThreeIllegalChars_ShouldReturn_EmptyString)
		{
			string result = parser.UniformInputString(ThreeIllegalChars);

			Assert::AreEqual(StringManager::EmptyString(), result);
		}

		TEST_METHOD(ParserUniform_SinglePositiveDigit_ShouldReturn_SinglePositiveDigit)
		{
			string result = parser.UniformInputString(SinglePositiveDigit);

			Assert::AreEqual(SinglePositiveDigit, result);
		}

		TEST_METHOD(ParserUniform_PositiveNumber_ShouldReturn_PositiveNumber)
		{
			string result = parser.UniformInputString(PositiveNumber);

			Assert::AreEqual(PositiveNumber, result);
		}

		TEST_METHOD(ParserUniform_SingleNegativeDigit_ShouldReturn_SingleNegativeDigit)
		{
			string result = parser.UniformInputString(SingleNegativeDigit);

			Assert::AreEqual(SingleNegativeDigit, result);
		}

		TEST_METHOD(ParserUniform_NegativeNumber_ShouldReturn_NegativeNumber)
		{
			string result = parser.UniformInputString(NegativeNumber);

			Assert::AreEqual(NegativeNumber, result);
		}

		TEST_METHOD(ParserUniform_SingleVar_ShouldReturn_SingleVar)
		{
			string result = parser.UniformInputString(SingleVar);

			Assert::AreEqual(SingleVar, result);
		}

		TEST_METHOD(ParserUniform_TwoVarsInARow_ShouldReturn_EmptyString)
		{
			string result = parser.UniformInputString(TwoVarsInARow);
			
			Assert::AreEqual(StringManager::EmptyString(), result);
		}
	};
}