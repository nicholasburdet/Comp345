#pragma once
#include "characterBuilder.h"
#include "character.h"
#include <vector>

using namespace std;

/*!
Concrete builder for the Tank fighter subtype. Implements the abilities assignment ordering specific to Tank,
and sets the character's subtype to "tank"
*/
class TankConcreteBuilder :
	public characterBuilder
{
public:
	TankConcreteBuilder();
	~TankConcreteBuilder();

	void setSubtype() {
		toBuild->setSubtype("Tank");
	}

	character::abilList assignAbilities(vector<int> abilities);


};

