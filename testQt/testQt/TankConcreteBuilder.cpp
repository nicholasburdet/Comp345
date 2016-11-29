
/*

Alexis Grondin
ID:26639569

COMP 345 Assignment 3: Character Builder


*/



#include "TankConcreteBuilder.h"
#include "character.h"
#include <vector>

using namespace std;



TankConcreteBuilder::TankConcreteBuilder()
{
}


TankConcreteBuilder::~TankConcreteBuilder()
{
}

character::abilList TankConcreteBuilder::assignAbilities(vector<int> abilities)
{
	character::abilList values = character::abilList();

	values.wisdom = abilities[0];
	values.charisma = abilities[1];
	values.intelligence = abilities[2];
	values.strength = abilities[3];
	values.dexterity = abilities[4];
	values.constitution = abilities[5];

	return values;

	return character::abilList();
}
