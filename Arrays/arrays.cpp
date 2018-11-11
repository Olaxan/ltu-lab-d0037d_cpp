// Arrays.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "utilslib.h"

#include <iostream>
#include <cstdlib>

using namespace std;
using namespace efiilj;

int main()
{
	int *arr;

	int width = IOUtils::askInt("Enter X dimension: ", "Please enter an integer.");
	int height = IOUtils::askInt("Enter Y dimension: ", "Please enter an integer.");

	arr = new int[ width * height ];

	for (int i = 0; i < width * height; i++) {
		arr[i] = rand() % 10;
	}

	int xSum = 0;
	int ySum = 0;

	for (int y = 0; y < height; y++) {

		xSum = 0;

		for (int x = 0; x < width; x++) {
			printf("%i\t", arr[x * height + y]);
			xSum += arr[x * height + y];
		}

		printf("%i\n", xSum);

	}

	delete[] arr;

	return 0;
}
