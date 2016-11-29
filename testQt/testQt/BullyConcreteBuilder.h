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
Concrete builder for the Bully fighter subtype. Implements the abilities assignment ordering specific to bullies,
and sets the character's subtype to "Bully"
*/
class BullyConcreteBuilder :
	public characterBuilder
{
public:
	BullyConcreteBuilder();
	~BullyConcreteBuilder();

	void setSubtype() {
		toBuild->setSubtype("Bully");
	}

	character::abilList assignAbilities(vector<int> abilities);

};

