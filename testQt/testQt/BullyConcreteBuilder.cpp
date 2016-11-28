#include "BullyConcreteBuilder.h"
#include <vector>
#include "character.h"



BullyConcreteBuilder::BullyConcreteBuilder()
{
}


BullyConcreteBuilder::~BullyConcreteBuilder()
{
}

character::abilList BullyConcreteBuilder::assignAbilities(vector<int> abilities)
{

	character::abilList values=character::abilList();

	values.wisdom = abilities[0];
	values.charisma = abilities[1];
	values.intelligence = abilities[2];
	values.dexterity = abilities[3];
	values.constitution = abilities[4];
	values.strength = abilities[5];

	return values;
}


