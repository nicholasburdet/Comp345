#pragma once
#include "Character.h"
class characterGenerator
{
public:
	characterGenerator();
	~characterGenerator();

	struct classAttribute{

	};


private:

	std::map<Character::CharacterClass, classAttributes> characterClassMap;

};

