#pragma once
#include <iostream>
#include <limits>

using namespace std;

void clearInputBuffer()
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}