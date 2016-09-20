#pragma once
#include "../Lib/Parser.h"
#include "../Lib/Number.h"	

class tmpclass
{
	Parser parser;
	Number a;
	Number b;
	vector<Number> polynomialRoots;
public:
	void Verify(string input)
	{
		for (int type = 0; type < NUMBER_OF_TYPES; type++)
		{
			Polynomial& p = parser.ConvertToPolynomial(input, type);
			Polynomial& p2 = p.PolynomialAfterEliminationOfMultipleRoots();
			Polynomial& polynomialAfterElimination = p2;
			polynomialAfterElimination.Normalize();
			vector<Number> roots = polynomialAfterElimination.FindRoots(a, b);
			polynomialRoots = SortNumbers(polynomialRoots);
			roots = SortNumbers(roots);
			if (VectorsAreEqual(polynomialRoots, roots))
			{
				cout << "ok" << endl;
				return;
			}

			string expectedRoots = to_string(polynomialRoots.size()) + ": ";
			string actualRoots = to_string(roots.size()) + ": ";
			for (int i = 0; i < polynomialRoots.size(); i++)
				expectedRoots += polynomialRoots[i].ToString() + ", ";
			for (int i = 0; i < roots.size(); i++)
				actualRoots += roots[i].ToString() + ", ";
			cout << "results:" << endl;
			cout << expectedRoots << " " << actualRoots << endl;
		}
	}

	void Init()
	{
		polynomialRoots.clear();
		InitConstants();
		a = -1000000;
		b = 100000;
	}

	void PolynomialRoots06()
	{
		polynomialRoots.push_back(Number(1));
		Verify("(a-1)^2");
	}
};

int main()
{
	InitConstants();

	tmpclass tmpc;
	tmpc.Init();
	tmpc.PolynomialRoots06();

	Parser parser;
	string inputS;
	string tmp;
	Number a;
	Number b;
	const int max_retry = 100;
	int retry;

	while (true)
	{
		retry = 0;
		a = -1000000;
		b = 1000000;
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

		p = parser.ConvertToPolynomial(inputS);

		Polynomial& after = p.PolynomialAfterEliminationOfMultipleRoots();

		after.Normalize();
		after.PrintRoots(a, b);

		cout << "-----" << endl;
		inputS = "";
	}	
}