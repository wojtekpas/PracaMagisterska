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
		cout << "W(x) = " << endl;
		getline(cin, inputS);
		//inputS = "a2+3a+2";
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
		PrintStats();
		p = parser.ConvertToPolynomial(inputS);
		PrintStats();
		cout << p.ToString() << endl;
		//cout << "created = " << countPolynomialVectors << ", deleted = " << countPolynomialVectorsDeleted << ", created numbers = " << countNumbers << endl;
		cout << "a = ";
		//cin >> a;
		cout << "b = ";
		a = -4;
		b = 4;
		//cin >> b;

		p.PrintInput();
		p.Print();
		p.PrintRoots(a, b);

		cout << "-----" << endl;
		inputS = "";
		//cout << "created = " << countPolynomialVectors << ", deleted = " << countPolynomialVectorsDeleted << ", created numbers = " << countNumbers << endl;
	}
}