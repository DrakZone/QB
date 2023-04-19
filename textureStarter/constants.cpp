#include "constants.h"

#include<iostream>
#include<cstdlib>
using namespace std;

void seed() {
	// Providing a seed value
	srand((unsigned)time(NULL));
}

float random_getd(float min, float max) {
	int range = max - min + 1;
	float result = min + (rand()%range);

	return result;
}