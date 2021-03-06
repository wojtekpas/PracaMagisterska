#pragma once
#include "../Lib/Parser.h"

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
	p = p.PolynomialAfterEliminationOfMultipleRoots();
	//p.Print();
	Number a = MAX_NEGATIVE_VALUE;
	Number b = MAX_VALUE;
	cout << "changes in a = " << p.NumberOfChangesSign(a) << endl;
	cout << "changes in b = " << p.NumberOfChangesSign(b) << endl;
	p.PrintRoots(Number(-100), Number(100));
	//p.FindRoots(Number(-100), Number(100));
	auto end = chrono::high_resolution_clock::now();
	auto durationInMs = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
	cout << durationInMs / 1000000 << endl;
	//cout << durationInNs / 1000000000 << "s ~= " << durationInNs/1000000 << "ms " << endl;
}

vector<int> degrees;

void Test1(int countWord = 0, int value = 0)
{
	int interval = countWord;
	int size = degrees.size();
	for (int i = 0; i < size; i++)
	{
		srand(degrees[i] + i);
		if (countWord == 0)
			interval = degrees[i];
		else if (countWord < 0)
			interval = -countWord;
		else
			interval = degrees[i] / countWord;
		cout << "degree = " << degrees[i] << endl;
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
		cout << "degree = " << degrees[i] << endl;
		MeasureTime(CreateTestPolynomial1(1, degrees[i], interval, value));
	}
	cout << "----" << endl;
}

void Test2(int countWord = 0, int value = 0)
{
	int interval = countWord;
	int size = degrees.size();
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

void TestWithRoots(int type, vector<double>roots)
{
	Polynomial& p = CreatePolynomial(type);
	Polynomial& p2 = CreatePolynomial(type);
	p.SetValue(0, 1);
	for(auto r: roots)
	{
		p2.SetValue(1, 1);
		p2.SetValue(0, -r);
		p *= p2;
		//p.Print();
	}
	MeasureTime(p);
	cout << "----" << endl;
}

vector<double> CreateVectorWithNextValues(int size)
{
	vector<double> values;
	for (int i = 1; i <= size; i++)
	{
		values.push_back(i);
	}
	return values;
}

vector<double> CreateVectorWithDoubleValues(int size)
{
	vector<double> values;
	for (int i = 1; i <= size; i++)
	{
		double tmp = 1 + ((double)i) / 100;
		//cout << tmp << endl;
		values.push_back(tmp);
	}
	return values;
}

vector<double> CreateVectorWithBigValues(int size)
{
	vector<double> values;
	for (int i = 1; i <= size; i++)
	{
		double tmp = 10;
		for (int j = 1; j < i; j++)
		{
			tmp *= 10;
		}
		//cout << tmp << endl;
		values.push_back(tmp);
	}
	return values;
}

void TestCase_1()
{
	degrees = { 100, 200, 400, 800, 1600, 3200 };
	Test1(1, 1);
}

void TestCase_2()
{
	degrees = { 101, 201, 401, 801, 1601, 3201 };
	Test1(1, 1);
}

void TestCase_3()
{
	degrees = { 1, 2, 4, 8, 16, 32 };
	for(auto deg: degrees)
	{
		cout << "deg = " << deg << endl;
		TestWithRoots(0, CreateVectorWithNextValues(deg));
		TestWithRoots(1, CreateVectorWithNextValues(deg));
	}
}

void TestCase_4()
{
	degrees = { 1, 2, 4, 8, 16, 32 };
	for (auto deg : degrees)
	{
		cout << "deg = " << deg << endl;
		TestWithRoots(0, CreateVectorWithDoubleValues(deg));
		TestWithRoots(1, CreateVectorWithDoubleValues(deg));
	}
}

void TestCase_5()
{
	degrees = { 1, 2, 4, 8, 16, 32 };
	for (auto deg : degrees)
	{
		cout << "deg = " << deg << endl;
		TestWithRoots(0, CreateVectorWithBigValues(deg));
		TestWithRoots(1, CreateVectorWithBigValues(deg));
	}
}

int main()
{
	InitConstants();
	printf("tc_1\n");
	//TestCase_1();
	printf("tc_2\n");
	//TestCase_2();
	printf("tc_3\n");
	TestCase_3();
	printf("tc_4\n");
	//TestCase_4();
	printf("tc_5\n");
	//TestCase_5();

//	Test1(10, value);
//	Test1(-2, value);
//	Test1(-1, value);

//	Test2(0, value);
//	Test2(10, value);
//	Test2(-2, value);
//	Test2(-1, value);

	getchar();
	getchar();
	while (1);
	return 0;
}