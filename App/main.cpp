#pragma once
#include "../Lib/Parser.h"
#include "../Lib/Number.h"	

int main()
{
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
//		cout << "a = ";
//		cin >> a;
//		cout << "b = ";
//		cin >> b;

		p.PrintInput();
		p.Print();
		p.PrintRoots(a, b);

		cout << "-----" << endl;
		inputS = "";
	}	
}