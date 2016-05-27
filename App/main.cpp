#pragma once
#include "../Lib/Parser.h"
#include "../Lib/Number.h"	


void Verify(string input)
{
	vector<Number> polynomialRoots;
	polynomialRoots.push_back(Number(-1));
	polynomialRoots.push_back(Number(1));
	polynomialRoots.push_back(Number(2));
	Parser parser;
	Polynomial& p = parser.ConvertToPolynomial(input);
	p.PrintInput();
	p.Print();
	Polynomial& p2 = p.PolynomialAfterEliminationOfMultipleRoots();
	Polynomial& polynomialAfterElimination = p2;
	polynomialAfterElimination.Normalize();
	vector<Number> roots = polynomialAfterElimination.FindRoots(Number(-1000), Number(1000));
	string expectedRoots = to_string(polynomialRoots.size()) + ": ";
	string actualRoots = to_string(roots.size()) + ": ";
	polynomialRoots = SortNumbers(polynomialRoots);
	roots = SortNumbers(roots);
	for (int i = 0; i < polynomialRoots.size(); i++)
		expectedRoots += polynomialRoots[i].ToString() + ", ";
	for (int i = 0; i < roots.size(); i++)
		actualRoots += roots[i].ToString() + ", ";
	cout << "Expected: " << expectedRoots << endl;
	cout << "Actual : " << actualRoots << endl;
}

int main()
{
	Verify("(x-1)^2*(x+1)^2*(x-2)^2");
	return 0;
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