#pragma once
#include "../Lib/Parser.h"
#include <condition_variable>

Polynomial& CreateTestPolynomial1(int type, int degree, int interval, int value = 1)
{
	Polynomial& p = CreatePolynomial(type);
	p.SetValue(8, 1);
	p.SetValue(4, -1);
//	for (int i = degree; i >= 0; i -= interval)
//		p.SetValue(i, value);
	return p;
}

Polynomial& CreateTestPolynomial2(int type, int degree, int interval, int value = 1)
{
	Polynomial& p = CreatePolynomial(type);
	int count = 0;
	for (int i = degree; i >= 0; i -= interval)
	{
		if (count % 2 == 0)
			p.SetValue(i, value);
		else
			p.SetValue(i, -value);
		count++;
	}
	return p;
}

void MeasureTime(Polynomial& p)
{
	p.Print();
	cout << p.NumberOfRoots(Number(-100), Number(100)) << endl;
	auto begin = chrono::high_resolution_clock::now();
	p.PrintRoots(-100, 100);
	auto end = chrono::high_resolution_clock::now();
	auto durationInNs = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
	std::cout << durationInNs/1000000 << "ms ~" << durationInNs / 1000000000 << "s" << endl;
}

int main()
{
	Parser parser;
	string inputS;
	string tmp;

	MeasureTime(CreateTestPolynomial2(0, 101, 13, 1));

	getchar();
	getchar();
	return 0;
}