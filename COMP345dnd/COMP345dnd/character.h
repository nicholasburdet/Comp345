#pragma once
#include "ItemContainer.h"
#include "stdio.h"
#include "baseItem.h"
#include <string>
#include <map>

class Character
{
public:

	enum CharacterClass { fighter, Barbarian, Bard, Cleric, Druid, Wizard, Paladin, Ranger, Sorcerer, Thief, Warlock };


	Character(CharacterClass _charClass, int level);
	Character(std::string _charClass, int level);
	~Character();



private:
	CharacterClass _charClass;
	int level;
	ItemContainer bag;

	std::map<baseItem::BonusType, int> abilities;

};

