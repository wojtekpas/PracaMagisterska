#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Lib/PolynomialMap.h"
#include "../Lib/Parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
	TEST_CLASS(UnitTest1)
	{
	public:	
		TEST_METHOD(TestMethod1)
		{
			PolynomialMap p;
			p.Clear();
			Parser pa("3");
			Assert::AreNotEqual(false, true);
		}

	};
}