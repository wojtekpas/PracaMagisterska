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

		TEST_METHOD(ParserUniform_EmptyString_ShouldReturn_EmptyString)
		{
			Verify(StringManager::EmptyString());
		}

		TEST_METHOD(ParserUniform_SingleIllegalChar_ShouldReturn_EmptyString)
		{
			Verify("!");
		}

		TEST_METHOD(ParserUniform_ThreeIllegalChars_ShouldReturn_EmptyString)
		{
			Verify("!@#");
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
			Verify("aa");
		}

		TEST_METHOD(ParserUniform_NumberStartsFromBlankSpace_ShouldReturn_ValueWithoutWhitespaces)
		{
			Verify(" 1234", "1234");
		}

		TEST_METHOD(ParserUniform_ExpressionContainingMulOp_ShouldReturn_ExpressionWithoutChange)
		{
			Verify("100*a", "100*a");
		}

		TEST_METHOD(ParserUniform_ExpressionNotContainingMulOp_ShouldReturn_ExpressionWithAddedMulOp)
		{
			Verify("100a", "100*a");
		}

		TEST_METHOD(ParserUniform_NegativeExpressionNotContainingMulOp_ShouldReturn_ExpressionWithAddedMulOp)
		{
			Verify("-50a", "-50*a");
		}

		TEST_METHOD(ParserUniform_ExpressionContainingExpOp_ShouldReturn_ExpressionWithoutChange)
		{
			Verify("a^2", "a^2");
		}

		TEST_METHOD(ParserUniform_ExpressionNotContainingExpOp_ShouldReturn_ExpressionWithAddedExpOp)
		{
			Verify("a3", "a^3");
		}

		TEST_METHOD(ParserUniform_NegativeExpressionContainingMulOpAndExpOp_ShouldReturn_ExpressionWithoutChange)
		{
			Verify("-5*a3", "-5*a^3");
		}

		TEST_METHOD(ParserUniform_ExpressionContainingMulOpFollowedByExpressionNotContainingMulOp_ShouldReturn_ExpressionWithoutAddedExpOp)
		{
			Verify("a3*3", "a^3*3");
		}

		TEST_METHOD(ParserUniform_ExpressionNotContainingMulOpAndExpOp_ShouldReturn_ExpressionWithAddedMulOpAndExpOp)
		{
			Verify("4a3", "4*a^3");
		}

		TEST_METHOD(ParserUniform_ExpressionNotContainingMulOpAndExpOpWithWhitespace_ShouldReturn_ExpressionWithAddedMulOpAndExpOp)
		{
			Verify("10 a2", "10*a^2");
		}

		TEST_METHOD(ParserUniform_ExpressionNotContainingMulOpPrecedingParenthesis_ShouldReturn_ExpressionWithAddedMulOp)
		{
			Verify("2(4a+2)", "2*(4*a+2)");
		}

		TEST_METHOD(ParserUniform_ExpressionContainingTwoParenthesisNotSeperatedByMulOp_ShouldReturn_ExpressionWithAddedMulOp)
		{
			Verify("(3a+1)(2a+1)", "(3*a+1)*(2*a+1)");
		}

		TEST_METHOD(ParserUniform_ExpressionNotContainingExpOpFollowedByParenthesis_ShouldReturn_ExpressionWithAddedExpOp)
		{
			Verify("(3*a)2", "(3*a)^2");
		}
	};
}