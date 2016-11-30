/*
	Alexis Grondin
	ID:26639569

	COMP 345 Assignment 3: Character Builder


*/



#pragma once
#include "character.h"
#include <iostream>
#include <fstream>

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
		
		////Creates default inventory for new characters
		ofstream writer("Resources/" + name + "backpack.txt");
		writer << "1|Helmet|Full Helmet|Wisdom|4|Heavy\n2|Armor|Half Platebody||0|Heavy\n7|Shield|Kiteshield|Armor Class|3|Heavy\n5|Ring|Ruby Ring|Armor Class|2|Light\n8|Belt|Titanium Belt|Strength|1|Heavy\n9|Boots|Rugged boots||0|Heavy\n11|Weapon|Long Sword|Attack Bonus|2|1d12";
		writer.close();

		ofstream writer2("Resources/" + name + "wornItems.txt");
		writer2 << "1|Helmet|Full Helmet|Wisdom|4|Heavy\n2|Armor|Half Platebody||0|Heavy\n7|Shield|Kiteshield|Armor Class|3|Heavy\n5|Ring|Ruby Ring|Armor Class|2|Light\n8|Belt|Titanium Belt|Strength|1|Heavy\n9|Boots|Rugged boots||0|Heavy\n11|Weapon|Long Sword|Attack Bonus|2|1d12";
		writer2.close();
	};
	virtual void buildHP(int hp) {
		toBuild->setHP(hp);
	};
	virtual void buildId(int i) {
		toBuild->setId(i);
	};
	virtual void buildLevel(int l) {
		int lev = l > 0 ? l : 1;
		toBuild->setLevel(lev);
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

