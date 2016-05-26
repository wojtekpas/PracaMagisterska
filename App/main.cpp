#pragma once
#include "../Lib/Parser.h"
#include "../Lib/Number.h"	

void Verify(string input, Polynomial& expectedOutput)
{
	Parser parser;
	Polynomial& result = parser.ConvertToPolynomial(input);
	string s = result.ToString();
	cout << s << " : " << expectedOutput.ToString() << endl;
}

void Verify(string input, int expectedValue, int power = 0)
{
	Polynomial& expectedOutput = CreatePolynomial();
	expectedOutput.SetValue(power, expectedValue);
	Verify(input, expectedOutput);
}

int main()
{
	Verify("2", 2);
	Verify("2*2", 4);
	Verify("2*2*2", 8);
	Verify("2*2*2", 16);
	Verify("2*2*2*2*2", 32);
	Verify("2*2*2*2*2*2", 64);
	Verify("2^0", 1);
	Verify("2^1", 2);
	Verify("2^2", 4);
	Verify("2^3", 8);
	Verify("2^4", 16);
	Verify("2^5", 32);
	Verify("(2a)^6", 64);
	Verify("(2*1)^6", 64);
	Verify("(2^3)^2", 64);
	Verify("2^3^2", 64);
	Verify("(-2)10", 1024);
	Parser parser;
	string inputS;
	string tmp;
	double a;
	double b;
	const int max_retry = 100;
	int retry;

	while (true)
	{
		retry = 0;
		a = MAX_NEGATIVE_VALUE;
		b = MAX_VALUE;
		cout << "W(x) = " << endl;
		getline(cin, inputS);
		while (inputS == "")
		{
			getline(cin, inputS);
			retry++;
			if (retry == max_retry)
				return -1;
		}
		if (inputS == "quit")
			return 0;

		Polynomial& p = CreatePolynomial();
		
		p = parser.ConvertToPolynomial(inputS);
		cout << "a = ";
		cin >> a;
		cout << "b = ";
		cin >> b;

		p.PrintInput();
		p.Print();
		p.PrintRoots(a, b);
		

		cout << "-----" << endl;
		inputS = "";
	}	
}