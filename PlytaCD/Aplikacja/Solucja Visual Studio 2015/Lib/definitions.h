#pragma once
#include <iostream>
#include <string>
#include <exception>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

#define DEBUG_MODE 1

static int TYPE = 0;
static int DISPLAYING_ROOTS = 1;
static int DISPLAYING_STURM = 0;
static int DISPLAYING_SIGNS = 0;
static int DISPLAYING_AFTER_ELIMINATION = 0;
static int MEASURING_TIME = 0;

inline void SetDebugMode(int isActive = DEBUG_MODE)
{
	if (isActive == 0)
		return;

	DISPLAYING_ROOTS = 1;
	DISPLAYING_STURM = 1;
	DISPLAYING_SIGNS = 1;
	DISPLAYING_AFTER_ELIMINATION = 1;
	MEASURING_TIME = 1;
}

inline int SetOption(string s)
{
	if (s == "set type map" || s == "set 1 m" || s == "set 1 0" || s == "s 1 m" || s == "s 1 0")
	{
		TYPE = 0;
		return 0;
	}
	if (s == "set type vector" || s == "set 1 v" || s == "set 1 1" || s == "s 1 v" || s == "s 1 1")
	{
		TYPE = 1;
		return 0;
	}

	if (s == "set displaying roots 0" || s == "set 2 0" || s == "s 2 0")
	{
		DISPLAYING_ROOTS = 0;
		return 0;
	}
	if (s == "set displaying roots 1" || s == "set 2 1" || s == "s 2 1")
	{
		DISPLAYING_ROOTS = 1;
		return 0;
	}

	if (s == "set displaying sturm 0" || s == "set 3 0" || s == "s 3 0")
	{
		DISPLAYING_STURM = 0;
		return 0;
	}
	if (s == "set displaying sturm 1" || s == "set 3 1" || s == "s 3 1")
	{
		DISPLAYING_STURM = 1;
		return 0;
	}

	if (s == "set displaying signs 0" || s == "set 4 0" || s == "s 4 0")
	{
		DISPLAYING_SIGNS = 0;
		return 0;
	}
	if (s == "set displaying signs 1" || s == "set 4 1" || s == "s 4 1")
	{
		DISPLAYING_SIGNS = 1;
		return 0;
	}

	if (s == "set displaying after elimination 0" || s == "set 5 0" || s == "s 5 0")
	{
		DISPLAYING_AFTER_ELIMINATION = 0;
		return 0;
	}
	if (s == "set displaying after elimination 1" || s == "set 5 1" || s == "s 5 1")
	{
		DISPLAYING_AFTER_ELIMINATION = 1;
		return 0;
	}

	if (s == "set measuring time 0" || s == "set 6 0" || s == "s 6 0")
	{
		MEASURING_TIME = 0;
		return 0;
	}
	if (s == "set measuring time 1" || s == "set 6 1" || s == "s 6 1")
	{
		MEASURING_TIME = 1;
		return 0;
	}
	return -1;
}