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
	int count = 0;
	for (int i = degree; i >= 0; i -= interval)
	{
		count++;
		if (value)
		{
			if (count % 2 == 0)
				p.SetValue(i, value);
			else
				p.SetValue(i, -value);
		}
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
	cout << durationInNs / 1000000 << endl;
	//cout << durationInNs / 1000000000 << "s ~= " << durationInNs/1000000 << "ms " << endl;
}

int degrees[] = { 100, 200, 500 };// 1000, 2000 }; //, 5000, 10000 };

void Test1(int countWord = 0, int value = 0)
{
	int interval = countWord;
	int size = sizeof(degrees) / sizeof(degrees[0]);
	for (int i = 0; i < size; i++)
	{
		srand(degrees[i] + i);
		if (countWord == 0)
			interval = degrees[i];
		else if (countWord < 0)
			interval = -countWord;
		else
			interval = degrees[i] / countWord;
		//cout << "map degree = " << degrees[i] << ": ";
		MeasureTime(CreateTestPolynomial1(0, degrees[i], interval, value));
	}
	for (int i = 0; i < size; i++)
	{
		srand(degrees[i] + i);
		if (countWord == 0)
			interval = degrees[i];
		else if (countWord < 0)
			interval = -countWord;
		else
			interval = degrees[i] / countWord;
		//cout << "vector degree = " << degrees[i] << ": ";
		MeasureTime(CreateTestPolynomial1(1, degrees[i], interval, value));
	}
	cout << "----" << endl;
}

void Test2(int countWord = 0, int value = 0)
{
	int interval = countWord;
	int size = sizeof(degrees) / sizeof(degrees[0]);
	for (int i = 0; i < size; i++)
	{
		srand(degrees[i] + i);
		if (countWord == 0)
			interval = degrees[i];
		else if (countWord < 0)
			interval = - countWord;
		else
			interval = degrees[i] / countWord;
		//cout << "map degree = " << degrees[i] << ": ";
		MeasureTime(CreateTestPolynomial2(0, degrees[i], interval, value));
	}
	for (int i = 0; i < size; i++)
	{
		srand(degrees[i] + i);
		if (countWord == 0)
			interval = degrees[i];
		else if (countWord < 0)
			interval = -countWord;
		else
			interval = degrees[i] / countWord;
		//cout << "vector degree = " << degrees[i] << ": ";
		MeasureTime(CreateTestPolynomial2(1, degrees[i], interval, value));
	}
	cout << "----" << endl;
}

int main()
{
	int value = 1;
//	Test1(0, value);
//	Test1(10, value);
//	Test1(-2, value);
//	Test1(-1, value);

	Test2(0, value);
	Test2(10, value);
	Test2(-2, value);
	Test2(-1, value);

	getchar();
	getchar();
	return 0;
}