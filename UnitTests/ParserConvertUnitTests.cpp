#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Lib/PolynomialMap.h"
#include "../Lib/Parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(ParserConvertUnitTests)
	{
		Parser parser;
		PolynomialMap polynomialMap;
		PolynomialMap result;
	public:

		void Verify(string input)
		{
			PolynomialMap expectedOutput;

			Verify(input, expectedOutput);
		}

		void Verify(string input, PolynomialMap expectedOutput)
		{
			PolynomialMap result = parser.ConvertToPolynomialMap(input);

			Assert::IsTrue(expectedOutput == result);
		}

		void VerifyForAFirstPower(string input, int expectedValueForAFirstPower)
		{
			Verify(input, expectedValueForAFirstPower, 1);
		}

		void Verify(string input, int expectedValue, int power = 0)
		{
			PolynomialMap expectedOutput;

			expectedOutput.SetValue(power, expectedValue);

			Verify(input, expectedOutput);
		}

		TEST_METHOD_INITIALIZE(Init)
		{
			result.Clear();
		}

		TEST_METHOD(ParserUniform_EmptyString_ShouldReturn_EmptyPolynomialMap)
		{
			Verify(StringManager::EmptyString());
		}

		TEST_METHOD(ParserUniform_SinglePositiveDigit_ShouldReturn_SinglePositiveDigit)
		{
			Verify("1", 1);
		}

		TEST_METHOD(ParserUniform_PositiveNumber_ShouldReturn_PositiveNumber)
		{
			Verify("123", 123);
		}

		TEST_METHOD(ParserUniform_SingleNegativeDigit_ShouldReturn_SingleNegativeDigit)
		{
			Verify("-1", -1);
		}

		TEST_METHOD(ParserUniform_NegativeNumber_ShouldReturn_NegativeNumber)
		{
			Verify("-123", -123);
		}

		TEST_METHOD(ParserUniform_SingleVar_ShouldReturn_SingleVar)
		{
			VerifyForAFirstPower("a", 1);
		}

		TEST_METHOD(ParserUniform_TwoVarsInARow_ShouldReturn_EmptyString)
		{
			Verify("aa");
		}

		TEST_METHOD(ParserUniform_NumberStartsFromBlankSpace_ShouldReturn_ValueWithoutWhitespaces)
		{
			Verify(" 1234", 1234);
		}

		TEST_METHOD(ParserUniform_ExpressionContainingMulOp_ShouldReturn_ExpressionWithoutChange)
		{
			VerifyForAFirstPower("100*a", 100);
		}

		TEST_METHOD(ParserUniform_ExpressionNotContainingMulOp_ShouldReturn_ExpressionWithAddedMulOp)
		{
			VerifyForAFirstPower("100a", 100);
		}

		TEST_METHOD(ParserUniform_NegativeExpressionNotContainingMulOp_ShouldReturn_ExpressionWithAddedMulOp)
		{
			VerifyForAFirstPower("-50a", -50);
		}

		TEST_METHOD(ParserUniform_ExpressionContainingExpOp_ShouldReturn_ExpressionWithoutChange)
		{
			Verify("a^2", 1, 2);
		}

		TEST_METHOD(ParserUniform_ExpressionNotContainingExpOp_ShouldReturn_ExpressionWithAddedExpOp)
		{
			Verify("a3", 1, 3);
		}

		TEST_METHOD(ParserUniform_NegativeExpressionContainingMulOpAndExpOp_ShouldReturn_ExpressionWithoutChange)
		{
			Verify("-5*a3", -5, 3);
		}

		TEST_METHOD(ParserUniform_ExpressionContainingMulOpFollowedByExpressionNotContainingMulOp_ShouldReturn_ExpressionWithoutAddedExpOp)
		{
			Verify("a3*3", 3, 3);
		}

		TEST_METHOD(ParserUniform_ExpressionNotContainingMulOpAndExpOp_ShouldReturn_ExpressionWithAddedMulOpAndExpOp)
		{
			Verify("4a3", 4, 3);
		}

		TEST_METHOD(ParserUniform_ExpressionNotContainingMulOpAndExpOpWithWhitespace_ShouldReturn_ExpressionWithAddedMulOpAndExpOp)
		{
			Verify("10 a2", 10, 2);
		}

		TEST_METHOD(ParserUniform_ExpressionNotContainingMulOpPrecedingParenthesis_ShouldReturn_ExpressionWithAddedMulOp)
		{
		}

		TEST_METHOD(ParserUniform_ExpressionContainingTwoParenthesisNotSeperatedByMulOp_ShouldReturn_ExpressionWithAddedMulOp)
		{
		}

		TEST_METHOD(ParserUniform_ExpressionNotContainingExpOpFollowedByParenthesis_ShouldReturn_ExpressionWithAddedExpOp)
		{
		}

		TEST_METHOD(ParserUniform_ExpressionContainingSubOpImmediatelyFollowedByMulOp_ShouldReturn_EmptyString)
		{
			Verify("3*-2");
		}

	};
}
