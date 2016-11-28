/*
	Alexis Grondin
	ID:26639569

	COMP 345 Assignment 3: Character Builder


*/



#pragma once
#include "character.h"

using namespace std;
/*!
	Builder for the character class. Possesses three concrete builders, which set different subtypes and abilities attribution order
*/
class characterBuilder
{
public:
	characterBuilder();
	~characterBuilder();

	/*!
		Creates a new character, using the default constructor
	*/
	virtual void createNewCharacter() {
		toBuild = new character();
	}

	/*!
		Returns a pointer to the character
	*/
	character* getCharacter() {

		return toBuild;
	}

	void buildName(string name) {
		toBuild->setName(name);
	};
	virtual void buildHP(int hp) {
		toBuild->setHP(hp);
	};
	virtual void buildId(int i) {
		toBuild->setId(i);
	};
	virtual void buildLevel(int l) {
		toBuild->setLevel(l);
	};

	virtual void buildImage(std::string im) {
		toBuild->setImage(im);
	};

	virtual void buildX(int x) {
		toBuild->setX(x);
	};
	virtual void buildY(int y) {
		toBuild->setY(y);
	};

	virtual void buildPlayerCharacter(bool pc) {
		toBuild->setPlayerCharacter(pc);
	};

	/*!
		Pure virtual method to set subtype
	*/
	virtual void setSubtype() = 0;

	/*!
		Creates an ability list struct from a sorted (in increasing order) int array. Will assign the abilities differently based on the concrete builder 
		implementing the method
	*/
	virtual character::abilList assignAbilities(vector<int> sortedRes)=0;

	/*!
		Sets the character's abilities, using the assignAbilities method
	*/
	virtual void generateAbilities();

protected:
	character* toBuild;


};

