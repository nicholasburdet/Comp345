
/*

Alexis Grondin
ID:26639569

COMP 345 Assignment 3: Character Builder


*/


#pragma once
#include "characterBuilder.h"
#include "character.h"
#include <vector>

using namespace std;
/*!
	Concrete builder for the Nimble fighter subtype. Implements the abilities assignment ordering specific to Nimbles,
	and sets the character's subtype to "Nimble"
*/
class NimbleConcreteBuilder :
	public characterBuilder
{
public:
	NimbleConcreteBuilder();
	~NimbleConcreteBuilder();

	//Sets the subtype of the character class to "Nimble"
	void setSubtype();

	character::abilList assignAbilities(vector<int> abilities);
	
};

