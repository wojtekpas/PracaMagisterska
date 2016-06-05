#pragma once
#include "../Lib/Parser.h"
#include <condition_variable>

Polynomial& CreateTestPolynomial1(int type, int degree, int interval, int value = 1)
{
	Polynomial& p = CreatePolynomial(type);
	for (int i = degree; i >= 0; i -= interval)
	{
		if (value)
			p.SetValue(i, value);
		else
			p.SetValue(i, rand() % 100);
	}

	return p;
}

Polynomial& CreateTestPolynomial2(int type, int degree, int interval, int value = 1)
{
	Polynomial& p = CreatePolynomial(type);
	for (int i = degree; i >= 0; i -= interval)
	{
		if (value)
			p.SetValue(i, value);
		else
		{
			p.SetValue(i, (rand() % 199) - 99);
		}
	}
	return p;
}

void MeasureTime(Polynomial& p)
{
	//p.Print();
	//cout << p.NumberOfRoots(Number(-100), Number(100)) << endl;
	auto begin = chrono::high_resolution_clock::now();
	p.FindRoots(Number(-100), Number(100));
	auto end = chrono::high_resolution_clock::now();
	auto durationInNs = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
	cout << durationInNs / 1000000000 << "s ~= " << durationInNs/1000000 << "ms " << endl;
}

int degrees[] = { 100, 200, 500, 1000, 2000 }; //, 5000, 10000 };

void Test1(int intervalArg = 0, int value = 0)
{
	int interval = intervalArg;
	int size = sizeof(degrees) / sizeof(degrees[0]);
	for (int i = 0; i < size; i++)
	{
		if (intervalArg == 0)
			interval = degrees[i];
		cout << "map degree = " << degrees[i] << ": ";
		MeasureTime(CreateTestPolynomial1(0, degrees[i], interval, value));
	}
	for (int i = 0; i < size; i++)
	{
		if (intervalArg == 0)
			interval = degrees[i];
		cout << "vector degree = " << degrees[i] << ": ";
		MeasureTime(CreateTestPolynomial1(1, degrees[i], interval, value));
	}
	cout << "----" << endl;
}

void Test2(int intervalArg = 0, int value = 0)
{
	int interval = intervalArg;
	int size = sizeof(degrees) / sizeof(degrees[0]);
	for (int i = 0; i < size; i++)
	{
		if (intervalArg == 0)
			interval = degrees[i];
		cout << "map degree = " << degrees[i] << ": ";
		MeasureTime(CreateTestPolynomial2(0, degrees[i], interval, value));
	}
	for (int i = 0; i < size; i++)
	{
		if (intervalArg == 0)
			interval = degrees[i];
		cout << "vector degree = " << degrees[i] << ": ";
		MeasureTime(CreateTestPolynomial2(1, degrees[i], interval, value));
	}
	cout << "----" << endl;
}

int main()
{
	int value = 0;
//	Test1(0, value);
//	Test2(0, value);
	Test1(1, value);
	Test2(1, value);
	Test1(10, value);
	Test2(10, value);
	Test1(25, value);
	Test2(25, value);
	Test1(50, value);
	Test2(50, value);

	getchar();
	getchar();
	return 0;
}