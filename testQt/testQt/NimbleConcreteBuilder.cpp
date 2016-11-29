#include "NimbleConcreteBuilder.h"

#include "character.h"
#include <vector>

using namespace std;



NimbleConcreteBuilder::NimbleConcreteBuilder()
{
}


NimbleConcreteBuilder::~NimbleConcreteBuilder()
{
}

void NimbleConcreteBuilder::setSubtype(){
	toBuild->setSubtype("Nimble");
}

character::abilList NimbleConcreteBuilder::assignAbilities(vector<int> abilities)
{
	character::abilList values = character::abilList();

	values.wisdom = abilities[0];
	values.charisma = abilities[1];
	values.intelligence = abilities[2];
	values.strength = abilities[3];
	values.constitution = abilities[4];
	values.dexterity = abilities[5];

	return values;

	return character::abilList();
}
