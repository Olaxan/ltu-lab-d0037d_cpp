// Pyramid.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "utilslib.h"

#include <iostream>

using namespace std;
using namespace efiilj;

void pyramid(int n);
void pyramid(char n);

int main()
{

	char input;

	printf("Enter the number/character you want printed in the last row.\n> ");
	scanf("%c", input);

	if (isdigit(input)) {
		pyramid((int)input);
	}
	else {
		pyramid(input);
	}
}

void pyramid(int n) {

	for (int i = 0; i < n; i++) {

		for (int j = 0; j < n; j++)
		{
			printf("%i ", j);
		}

	}
}

void pyramid(char c) {

	for (int i = 1; i <= (toupper(c) - 'A'); i++) {
		printf(string(i, 'A' + i).c_str());
	}

}
