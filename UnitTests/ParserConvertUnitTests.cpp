#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Lib/Parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(ParserConvertUnitTests)
	{
		Parser parser;
		Polynomial& result = CreatePolynomial();
	public:

		void Verify(string input)
		{
			Polynomial& expectedOutput = CreatePolynomial();

			Verify(input, expectedOutput);
		}

		void Verify(string input, Polynomial& expectedOutput)
		{
			Polynomial& result = parser.ConvertToPolynomial(input);
			string s = result.ToString();

			Assert::AreEqual(expectedOutput.ToString(), s);
		}

		void VerifyForAFirstPower(string input, int expectedValueForAFirstPower)
		{
			Verify(input, expectedValueForAFirstPower, 1);
		}

		void Verify(string input, int expectedValue, int power = 0)
		{
			Polynomial& expectedOutput = CreatePolynomial();
			expectedOutput.SetValue(power, expectedValue);
			Verify(input, expectedOutput);
		}

		TEST_METHOD_INITIALIZE(Init)
		{
			result.Clear();
			InitConstants();
		}
		
		TEST_METHOD(ParserConvert01)
		{
			Verify(StringManager::EmptyString());
		}

		TEST_METHOD(ParserConvert02)
		{
			Verify("1", 1);
		}

		TEST_METHOD(ParserConvert03)
		{
			Verify("123", 123);
		}

		TEST_METHOD(ParserConvert04)
		{
			Verify("-1", -1);
		}

		TEST_METHOD(ParserConvert05)
		{
			Verify("-123", -123);
		}

		TEST_METHOD(ParserConvert06)
		{
			VerifyForAFirstPower("a", 1);
		}

		TEST_METHOD(ParserConvert07)
		{
			Verify("aa");
		}

		TEST_METHOD(ParserConvert08)
		{
			Verify(" 1234", 1234);
		}

		TEST_METHOD(ParserConvert09)
		{
			VerifyForAFirstPower("100*a", 100);
		}

		TEST_METHOD(ParserConvert10)
		{
			VerifyForAFirstPower("100a", 100);
		}

		TEST_METHOD(ParserConvert11)
		{
			VerifyForAFirstPower("-50a", -50);
		}

		TEST_METHOD(ParserConvert12)
		{
			Verify("a^2", 1, 2);
		}

		TEST_METHOD(ParserConvert13)
		{
			Verify("a3", 1, 3);
		}

		TEST_METHOD(ParserConvert14)
		{
			Verify("-5*a3", -5, 3);
		}

		TEST_METHOD(ParserConvert15)
		{
			Verify("a3*3", 3, 3);
		}

		TEST_METHOD(ParserConvert16)
		{
			Verify("4a3", 4, 3);
		}

		TEST_METHOD(ParserConvert17)
		{
			Verify("10 a2", 10, 2);
		}

		TEST_METHOD(ParserConvert18)
		{
			result.SetValue(1, 4);
			result.SetValue(0, 2);

			Verify("4*a+2", result);
		}

		TEST_METHOD(ParserConvert19)
		{
			VerifyForAFirstPower("2(4a-0)", 8);
		}
		
		TEST_METHOD(ParserConvert20)
		{
			result.SetValue(1, 8);
			result.SetValue(0, 4);

			Verify("2(4a+2)", result);
		}

		TEST_METHOD(ParserConvert21)
		{
			Verify("(3*a)^2", 9, 2);
		}

		TEST_METHOD(ParserConvert22)
		{
			Verify("3*-2");
		}

		TEST_METHOD(ParserConvert23)
		{
			Verify("(3*a)0", 1);
		}

		TEST_METHOD(ParserConvert24)
		{
			Verify("(1)2", 1);
		}

		TEST_METHOD(ParserConvert25)
		{
			Verify("(-1)2", 1);
		}

		TEST_METHOD(ParserConvert26)
		{
			Verify("(-2)10", 1024);
		}

		TEST_METHOD(ParserConvert27)
		{
			result.SetValue(123, 1);

			Verify("a^123", result);
		}

		TEST_METHOD(ParserConvert28)
		{
			result.SetValue(2, 2);

			Verify("a*2a", result);
		}

		TEST_METHOD(ParserConvert29)
		{
			result.SetValue(2, 3);
			result.SetValue(1, 2);
			result.SetValue(0, 2);

			Verify("3a2+2a+2", result);
		}

		TEST_METHOD(ParserConvert30)
		{
			result.SetValue(2, 1);
			result.SetValue(0, -1);

			Verify("(a+1)(a-1)", result);
		}

		TEST_METHOD(ParserConvert31)
		{
			result.SetValue(2, -2);
			result.SetValue(0, 2);

			Verify("-2(a+1)(a-1)", result);
		}

		TEST_METHOD(ParserConvert32)
		{
			result.SetValue(2, 1);
			result.SetValue(1, 2);
			result.SetValue(0, 1);

			Verify("(a+1)(a+1)", result);
		}

		TEST_METHOD(ParserConvert33)
		{
			result.SetValue(3, 1);
			result.SetValue(2, -3);
			result.SetValue(1, 3);
			result.SetValue(0, -1);

			Verify("(a-1)^3", result);
		}

		TEST_METHOD(ParserConvert34)
		{
			result.SetValue(3, 1);
			result.SetValue(2, 6);

			Verify("a3+2a2+4a2", result);
		}

		TEST_METHOD(ParserConvert35)
		{
			Verify("0*2a");
		}

		TEST_METHOD(ParserConvert36)
		{
			Verify("0*(a3-1)");
		}

		TEST_METHOD(ParserConvert37)
		{
			Verify("(a3-1)*0");
		}

		TEST_METHOD(ParserConvert38)
		{
			result.SetValue(3, 1);
			result.SetValue(1, 3);
			result.SetValue(0, -1);

			Verify("(a-1)^3+4a2-a2+0*(a3-1)", result);
		}

		TEST_METHOD(ParserConvert39)
		{
			result.SetValue(2, 6);
			result.SetValue(1, 5);
			result.SetValue(0, 1);
			Verify("(3a+1)(2a+1)", result);
		}

		TEST_METHOD(ParserConvert40)
		{
			Verify("-2a3*0+11", 11);
		}

		TEST_METHOD(ParserConvert41)
		{
			Verify("2^3^2", 64);
		}

		TEST_METHOD(ParserConvert42)
		{
			Verify("5^0", 1);
		}

		TEST_METHOD(ParserConvert43)
		{
			Verify("-(2a5)^0", -1);
		}

		TEST_METHOD(ParserConvert44)
		{
			Verify("(2a-3a+a)^1", 0);
		}

		TEST_METHOD(ParserConvert45)
		{
			Verify("-(2a-3a+a)^0", 0);
		}
	};
}
