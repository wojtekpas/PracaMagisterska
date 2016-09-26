#pragma once
#include "../Lib/Parser.h"
#include "../Lib/Number.h"	

int main()
{
	InitConstants();
	SetDebugMode();

	Parser parser;
	string inputS;
	Number a;
	Number b;
	const int max_retry = 100;
	int retry;
	cout << "-----" << endl;
	while (true)
	{
		retry = 0;
		a = -1000000;
		b = 1000000;
		getline(cin, inputS);
		while (inputS == "")
		{
			getline(cin, inputS);
			retry++;
			if (retry == max_retry)
				return -1;
		}

		if (inputS == "q")
			return 0;

		if (SetOption(inputS))
		{
			Polynomial& p = CreatePolynomial(TYPE);
			p = parser.ConvertToPolynomial(inputS, TYPE);

			if (p.IsZero() == 0)
			{
				p.Execute(a, b);
			}
			else
				printf("Polecenie nierozpoznane lub wielomian oznaczony jako zerowy - nie posiada pierwiastkow.\n");
		}

		cout << "-----" << endl;
		inputS = "";
	}	
}