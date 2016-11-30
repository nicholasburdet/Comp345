#include "Dice.h"
#include <iostream>
#include <string>
using namespace std;

int Dice::roll(int quantity, int type, int modifier)
{
	int sum = 0;

	for (int i = 0; i < quantity; i++)
	{
		sum = sum + (rand() % type) + 1;
	}
	
	sum = sum + modifier;

	return sum;
}
