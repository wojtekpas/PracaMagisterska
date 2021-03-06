#pragma once
#include "../Lib/Parser.h"
#include "../Lib/Number.h"	

int main()
{
	InitConstants();
	SetDebugMode();

	Parser parser;
	string inputS;
	const int max_retry = 100;
	int retry;
	numberA = -1000000;
	numberB = 1000000;
	printf("Witaj w apliacji !\nWprowadz wielomian lub ustaw odpowiednia opcje.\n");
	while (true)
	{
		retry = 0;
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
			if (SetValueFromString(inputS))
			{
				Polynomial& p = CreatePolynomial(TYPE);
				p = parser.ConvertToPolynomial(inputS, TYPE);

				if (p.IsZero() == 0)
				{
					p.Execute(numberA, numberB);
				}
				else
					printf("Polecenie nierozpoznane lub wielomian oznaczony jako zerowy - nie posiada pierwiastkow.\n");
			}
		}
		cout << "-----" << endl;
		inputS = "";
	}	
}