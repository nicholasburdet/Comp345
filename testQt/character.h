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
#include "characterObserver.h"
#include <set>
#include <memory>
using namespace std;



class character
{
public:
	character();
	character(int i, string n, int l, string im);
	character(int i, string n, int l, string im, int abilities[6]);
	void setId(int i);
	void setName(string n);
	void setLevel(int l);
	void setHP(int hp);
	void decHP(int damage);
	int getArmorBonus();
	virtual int getDamageBonus();
	virtual int getAttackBonus();
	int getMaxHP();

	void setImage(string im);



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
	string getName();
	int getLevel();
	virtual int levelUp(int incAmount);
	string getImage();

	int getX();
	int getY();
	abilList generateAbilities();
	int rollDice(int faces);
	int getMaxRollSum(int faces, int numRolls);

	void addObserver(shared_ptr<characterObserver> obs);

	void removeObserver(shared_ptr<characterObserver> obs);

	//Observer related stuff

	void addObserver(characterObserver& obs);
	void removeObserver(characterObserver& obs);
	void notifyObservers();




private:
	int id;
	string name = "NULL";
	string charClassName = "fighter";
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
	string image;
	int xPosition = -1;
	int yPosition = -1;

	set<shared_ptr<characterObserver>> observers;

};
#pragma once
