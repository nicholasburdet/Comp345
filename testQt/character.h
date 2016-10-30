#pragma once

/*
Author: Nicholas Burdet
Id: 29613773
Course: COMP 345
Assignment 2 Part 2: Map Editor

Character header file

*/

#pragma once
#include <string>
#include "observer.h"
#include <set>
#include <memory>



class character
{
public:
	character();
	character(int i, std::string n, int l, std::string im);
	character(int i, std::string n, int l, std::string im, int abilities[6]);
	~character();
	void setId(int i);
	void setName(std::string n);
	void setLevel(int l);
	void setHP(int hp);
	void decHP(int damage);
	int getArmorBonus();
	virtual int getDamageBonus();
	virtual int getAttackBonus();
	int getMaxHP();

	void setImage(std::string im);



	void setX(int x);
	void setY(int y);

	void moveBy(int x, int y);
	void moveTo(int x, int y);

	static int getModifier(int abilityScore);

	virtual int getHP();

	struct abilList{
		int strength;
 		int intelligence;
 		int wisdom;
 		int dexterity;
 		int constitution;
 		int charisma;
	};

	int getId();
	std::string getName();
	int getLevel();
	character::abilList getAbilities();
	string getClassName();
	virtual int levelUp(int incAmount);
	std::string getImage();

	int getX();
	int getY();
	abilList generateAbilities();
	int rollDice(int faces);
	int getMaxRollSum(int faces, int numRolls);


	//Observer related stuff

	void addObserver(observer& obs);
	void removeObserver(observer& obs);
	void notifyObservers();




private:
	int id;
	std::string name = "NULL";
	std::string charClassName = "fighter";
	int level;
	int hitDice;
	//PLACEHOLDERS
	int weaponDice=4;
	int weaponRange = 1;
	int shieldBonus = 1;
	int armorBonus = 3;
	//END PLACEHOLDERS
	int HP;
	abilList abilities;
	std::string image;
	int xPosition = -1;
	int yPosition = -1;

	std::set<observer*, std::less<observer*>> observers;

};
#pragma once
