#include "Dice.h"
#include <iostream>
#include <string>
using namespace std;

int Dice::roll(int quantity, int type, int modifier)
{
	int sum = 0;

	for (int i = 0; i < quantity; i++)
	{
		sum += (1 + rand() % type);
	}
	
	sum += modifier;

	return sum;
}
