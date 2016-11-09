#pragma once
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>
using namespace std;


class itemContainer {
public:
	string line;

	int id;
	string item;
	string name;


	itemContainer();
	~itemContainer();


	string static getAllFromFile(string filePath); // get all from either: Items, wornItems, backpack, treasureChest


	string getType(string filePath, int id);
	string getName(string filePath, int id);
	string getEnchantment(string filePath, int id);
	int getBonus(string filePath, int id);
	string getDiceOrGrade(string filePath, int id); //returns the dice damage if it's a weapon, else gets the armor grade

	//Backpack itemcontainer
	void addItemBackpack(int id);
	void removeItemBackpack(int rnd);

	//For the character worn item container
	void addItemWorn(int id);
	void removeItemWorn(string itemType);
	
};


#endif