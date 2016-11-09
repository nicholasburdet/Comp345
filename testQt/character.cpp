#pragma once

/*
Author: Alexis Grondin
Id: 26639569
Course: COMP 345
Assignment 2 Part 2: Character Observer

Character cpp file
*/

#include "character.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <set>
#include <QDebug>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

character::character():observers()
{
	id=rand();
	level=1;
	image="";
	abilities = generateAbilities();
	hitDice = 10;
	HP = getMaxHP();
}
character::character(int i, string n, int l, string im):observers()
{
	id = i;
	name = n;
	level = l;
	image = im;
	abilities = generateAbilities();
	hitDice = 10;
	HP = getMaxHP();
}

character::character(int i, string n, int l, string im, int abList[6]) :observers()
{
	id = i;
	name = n;
	level = l;
	image = im;
	abilities = abilList{ abList[0]%18,abList[1]%18,abList[2]%18,abList[3]%18,abList[4]%18,abList[5]%18 };
	hitDice = 10;
	HP = getMaxHP();

}

character::~character() {
	observers.clear();
}


void character::setId(int i)
{
	id = i;
	notifyObservers();

}
void character::setName(string n)
{
	name = n;
	notifyObservers();

}
void character::setLevel(int l)
{
	if(l<=20){
			level = l;
	}

	notifyObservers();
}

void character::setImage(string im)
{
	image = im;
	notifyObservers();
}
void character::setX(int x)
{
	xPosition = x;
	notifyObservers();

}
void character::setY(int y)
{
	yPosition = y;
	notifyObservers();
}

void character::moveBy(int x, int y)
{
	xPosition += x;
	yPosition += y;
	notifyObservers();
}

void character::moveTo(int x, int y)
{
	setX(x);
	setY(y);
	notifyObservers();
}

int character::getId()
{
	return id;
}
string character::getName()
{
	return name;
}
int character::getLevel()
{
	return level;
}

character::abilList character::getAbilities() {
	return abilities;
}

string character::getClassName() {
	return charClassName;
}

int character::levelUp(int incAmount=1){
	level += incAmount;
	HP += getModifier(abilities.constitution)*incAmount;

	notifyObservers();

	return HP;
}
string character::getImage()
{
	return image;
}
int character::getX()
{
	return xPosition;
}
int character::getY()
{
	return yPosition;
}

character::abilList character::generateAbilities() {

	abilList newAbs = { getMaxRollSum(6,4), getMaxRollSum(6, 4), getMaxRollSum(6, 4), getMaxRollSum(6, 4) ,getMaxRollSum(6, 4), getMaxRollSum(6,4) };

	return newAbs;
}

int character::rollDice(int faces)
{
	return 1 + rand() % faces;
}

int character::getMaxRollSum(int faces, int numRolls)
{
	int sum = 0;
	int min = faces + 1;
	for (int i = 0; i < numRolls; i++) {
		int thrw = rollDice(faces);
		sum += thrw;
		if (thrw < min) min = thrw;
	}

	return sum - min;
}


void character::addObserver(observer & obs)
{
	observer* o = &obs;

	observers.insert(o);
}

void character::removeObserver(observer & obs)
{

	observers.erase(&obs);

}

bool character::isAttached(observer* obs){
	return observers.find(obs) != observers.end();
}

void character::notifyObservers()
{
	for (observer* i : observers) {
		if (i != NULL) {
			i->notify();
		}
	}
}

character * character::loadFromFile(std::string filepath)
{
	ifstream characterFile(filepath);

	if (characterFile.is_open()) {

		string str;
		string file_contents;
		string symbol = ":";
		character* charac = new character();
		while (getline(characterFile, str))
		{
			size_t found = str.find(symbol);
			string attribute = str.substr(0, found);
			string value = str.substr(found);

			charac->setAttribute(attribute, value);

		}

		return charac;
	}

	return nullptr;
}

void character::saveToFile(std::string filepath, character * toSave)
{
	string attrList[] = { "Name", "id", "level", "image", "HP", "Class", "Strenght", "Intelligence", "Wisdom", "Constitution", "Charisma", "Dexterity" };

	ofstream file(filepath);

	if (file.is_open()) {
		for (auto i : attrList) {
			file << i;
			file << toSave->getAttribute(i);
			file << "\n";
		};
	}

}

void character::setAttribute(string attribute, string val)
{
	if (attribute == "Name") {
		this->setName(val);
	}
	else if (attribute == "id") {
		this->setId(std::stoi(val));
	}
	else if (attribute == "level") {
		this->setLevel(std::stoi(val));
	}
	else if (attribute == "image") {
		this->setImage(val);
	}
	else if (attribute == "HP") {
		this->setHP(std::stoi(val));
	}
	else if (attribute == "Class") {
		this->charClassName = val;
	}
	else if (attribute == "Strength") {
		this->abilities.strength = std::stoi(val);
	}
	else if (attribute == "Intelligence") {
		this->abilities.intelligence = std::stoi(val);
	}
	else if (attribute == "Wisdom") {
		this->abilities.wisdom = std::stoi(val);
	}
	else if (attribute == "Constitution") {
		this->abilities.constitution = std::stoi(val);
	}
	else if (attribute == "Charisma") {
		this->abilities.charisma = std::stoi(val);
	}
	else if (attribute == "Dexterity") {
		this->abilities.dexterity = std::stoi(val);
	}
	

}

string character::getAttribute(string attribute)
{
	if (attribute == "Name") {
		return getName();
	}
	else if (attribute == "id") {
		return std::to_string(getId());
	}
	else if (attribute == "level") {
		return std::to_string(getLevel());
	}
	else if (attribute == "image") {
		return getImage();
	}
	else if (attribute == "HP") {
		return std::to_string(getHP());
	}
	else if (attribute == "Class") {
		return this->charClassName;
	}
	else if (attribute == "Strength") {
		return std::to_string(this->abilities.strength);
	}
	else if (attribute == "Intelligence") {
		return std::to_string(this->abilities.intelligence );
	}
	else if (attribute == "Wisdom") {
		return std::to_string(this->abilities.wisdom );
	}
	else if (attribute == "Constitution") {
		return std::to_string(this->abilities.constitution );
	}
	else if (attribute == "Charisma") {
		return std::to_string(this->abilities.charisma );
	}
	else if (attribute == "Dexterity") {
		return std::to_string(this->abilities.dexterity );
	}



	return string();
}

int character::getHP(){
	return HP;
}

void character::setHP(int hp){
	HP = hp;
	notifyObservers();
}

void character::decHP(int damage) {
	HP -= damage;
}

int character::getArmorBonus() {
	return 10 + armorBonus + shieldBonus + getModifier(abilities.dexterity);
}

int character::getDamageBonus() {
	return getModifier(abilities.strength);
}

int character::getAttackBonus() {

	int profBonus = ((level - 1) / 4) + 2;

	int abBonus = weaponRange < 1 ? getModifier(abilities.strength) : getModifier(abilities.dexterity);

	return profBonus + abBonus + rollDice(weaponDice);

}

int character::getModifier(int abilityScore){
	return (abilityScore-10)/2;
}

int character::getMaxHP(){

	return (getModifier(this->abilities.constitution)*this->level + this->hitDice);
}
