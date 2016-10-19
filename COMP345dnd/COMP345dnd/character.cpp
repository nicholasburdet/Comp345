#include "stdafx.h"
#include "character.h"
#include <string>


Character::Character(Character::CharacterClass _charClass, int level){

	this->_charClass = _charClass;
	this->level = level;


};


Character::Character(std::string _charClass, int level){


	Character::CharacterClass _class = Character::fighter;

	if (_charClass == "Fighter") _class = Character::fighter;
	else if (_charClass == "Barbarian") _class = Character::Barbarian;
	else if (_charClass == "Druid") _class = Character::Druid;
	else if (_charClass == "Warlock") _class = Character::Warlock;
	else if (_charClass == "Wizard") _class = Character::Wizard;
	else if (_charClass == "Paladin") _class = Character::Paladin;
	else if (_charClass == "Cleric") _class = Character::Cleric;
	else if (_charClass == "Ranger") _class = Character::Ranger;
	else if (_charClass == "Sorcerer") _class = Character::Sorcerer;
	else if (_charClass == "Thief") _class = Character::Thief;
	else if (_charClass == "Bard") _class = Character::Bard;

	this->_charClass = _class;

	this->level = level;



}


Character::~Character()
{
}
