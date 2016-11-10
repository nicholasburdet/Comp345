#pragma once

/*
Author: Nicholas Burdet
Id: 29613773
Course: COMP 345
Assignment 2 Part 3: Map Editor

Character header file

Bare bones file to show off NPC capability on the editor screen
*/


#pragma once
#include <string>
#include "observer.h"
#include <set>
#include <memory>
#include "Dice.h"
using namespace std;


/*!
Character class. Contains all information related to a character. For the time being, the only character class is fighter.
A character can be linked to an image file, which will be used to display him on the map.

DnD Rules:
-Level: For the level, we use a maximum level of 20. This level is first set at character creation, but can afterwards be increased.

-Abilities: There are six different abilities, represented by a struct, and which can be set by the player of generated randomly. If generated randomly, each
ability will be given by rolling a 6-dice four times and taking the sum of the 3 highest throws.

-Ability modifiers: Ability modifiers are given by the formula (ability level-10)/2

-HP: HP upon character creation is defined by the formula: (Hit Dice)+(Character Level)*(Constitution modifier). Afterwards, the HP can be increased or decreased,
when a character heals or is injured. When a character levels up, his HP is increased by an amount equal to his constitution modifier.

-Hit Dice: fighters have a hit dice of 10, which represents some sort of value related to their ability to survive, I suppose.

-Armor Bonus: Armor bonus is the sum of: 10+(armor bonus)+(shield bonus)+(dexterity modifier)

-Attack Bonus: Attack bonus is given by: proficiency bonus (see below) plus a modifier (strenght if short range weapon, dexterity if long range) plus
a dice roll of the weapon's dice.

Design:
The character class keeps a set of observers. When the character's state changes, the observers are notified. Std::set was used to keep the set of observers,
because it doesn't allow for duplicates and generally corresponds to our needs.

*/
class character
{
public:
	character();
	character(int i, std::string n, int l, std::string im);
	character(int i, std::string n, int l, std::string im, int abilities[6]);
	~character();
	void initialize(int i, std::string n, int l, std::string im);
	void setId(int i);
	void setName(std::string n);
	void setLevel(int l);
	void setHP(int hp);
	void decHP(int damage);
	int getArmorBonus();
	virtual int getDamageBonus();
	virtual int getAttackBonus();
	/*!
	returns the maximum starting HP for the character's level, class and constitution
	*/
	int getMaxHP();

	void setImage(std::string im);



	void setX(int x);
	void setY(int y);

	void moveBy(int x, int y);
	void moveTo(int x, int y);

	static int getModifier(int abilityScore);

	virtual int getHP();

	struct abilList {
		int strength;
		int intelligence;
		int wisdom;
		int dexterity;
		int constitution;
		int charisma;
	};

	int getId();
	string getName();
	int getLevel();
	character::abilList getAbilities();
	string getClassName();
	virtual int levelUp(int incAmount);
	string getImage();

	int getX();
	int getY();
	abilList generateAbilities();
	//int rollDice(int faces); //Replaced with dice class
	int getMaxRollSum(int faces, int numRolls);


	//Observer related stuff

	void addObserver(observer& obs);
	void removeObserver(observer& obs);
	bool isAttached(observer* obs);
	void notifyObservers();

	bool isPlayerCharacter();
	void setPlayerCharacter(bool pc);

	void saveToFile();
	void loadFromFile(string filepath);

private:
	int id;
	string name = "NULL";
	string charClassName = "fighter";
	int level;
	int hitDice;
	//PLACEHOLDERS
	int weaponDice = 4;
	int weaponRange = 1;
	int shieldBonus = 1;
	int armorBonus = 3;
	//END PLACEHOLDERS
	int HP;
	abilList abilities;
	string image = "";
	int xPosition = -1;
	int yPosition = -1;

	bool playerCharacter = false;

	set<observer*, less<observer*>> observers;

};
#pragma once

