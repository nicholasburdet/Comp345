#pragma once

/*
Author: Nicholas Burdet
Id: 29613773
Course: COMP 345
Assignment 2 Part 3: Map Editor

Character cpp file

Bare bones file to show off NPC capability on the editor screen
*/

#include "character.h"
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <set>
#include <QDebug>

#include <QKeyEvent>

using namespace std;


void characterMovement::keyPressEvent(QKeyEvent *event) {
	if (event->key() == Qt::Key_Left) {
		if (x() != 0)
			setPos(x() - 50, y());
	}

	else if (event->key() == Qt::Key_Right) {
		if (x() != 700)
			setPos(x() + 50, y());

	}
	else if (event->key() == Qt::Key_Up) {
		if (y() != 0)
			setPos(x(), y() - 50);

	}
	else if (event->key() == Qt::Key_Down) {
		if (y() != 450)
			setPos(x(), y() + 50);
	}

};

character::character() :observers()
{
	id = rand();
	level = 1;
	image = "";
	abilities = generateAbilities();
	hitDice = 10;
	HP = getMaxHP();
}
character::character(int i, string n, int l, string im) :observers()
{
	id = i;
	name = n;
	level = l;
	image = im;
	abilities = generateAbilities();
	hitDice = 10; //Fighter hit dice
	HP = getMaxHP();
}

character::character(int i, string n, int l, string im, int abList[6]) :observers()
{
	id = i;
	name = n;
	level = l;
	image = im;
	abilities = abilList{ abList[0] % 18,abList[1] % 18,abList[2] % 18,abList[3] % 18,abList[4] % 18,abList[5] % 18 };
	hitDice = 10;
	HP = getMaxHP();

}

character::~character() {
	observers.clear();
}

void character::initialize(int i, string n, int l, string im) {
	id = i;
	name = n;
	level = l;
	image = im;
	abilities = generateAbilities();
	hitDice = 10; //Fighter hit dice
	HP = getMaxHP();
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
	if (l <= 20) {
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

int character::levelUp(int incAmount = 1) {
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

int character::getMaxRollSum(int faces, int numRolls)
{
	int sum = 0;
	int min = faces;

	for (int i = 0; i < numRolls; i++) {
		int thrw = Dice::roll(1, faces, 0);
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

bool character::isAttached(observer* obs) {
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

int character::getHP() {
	return HP;
}

void character::setHP(int hp) {
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

	return profBonus + abBonus + Dice::roll(1, weaponDice, 0);

}

int character::getModifier(int abilityScore) {
	return (abilityScore - 10) / 2;
}

int character::getMaxHP() {
	//Fixed get Max HP, was not adding a hitDice for every level
	return (getModifier(this->abilities.constitution)*((this->level)-1) + this->hitDice + Dice::roll(level-1, this->hitDice, 0));
}

bool character::isPlayerCharacter() {
	return playerCharacter;
}

void character::setPlayerCharacter(bool pc) {
	playerCharacter = pc;
}

void character::saveToFile()
{
	if (playerCharacter)
	{
		ofstream output;
		string extension = "PlayerCharacters/";
		string fName = extension;
		fName.append("p");
		fName.append(to_string(id));
		fName.append("n");
		fName.append(name);
		output.open(fName.append(".txt"));

		output << "id" << " " << id << endl;
		output << "name" << " " << name << endl;
		output << "level" << " " << id << endl;
		output << "hp" << " " << HP << endl;
		output << "hitdice" << " " << hitDice << endl;
		output << "className" << " " << charClassName << endl;
		output << "strength" << " " << this->abilities.strength << endl;
		output << "dexterity" << " " << this->abilities.dexterity << endl;
		output << "constitution" << " " << this->abilities.constitution << endl;
		output << "intelligence" << " " << this->abilities.intelligence << endl;
		output << "wisdom" << " " << this->abilities.wisdom << endl;
		output << "charisma" << " " << this->abilities.charisma << endl;

		output.close();
	}
}

void character::loadFromFile(string filepath)
{
	ifstream input(filepath);

	string result;

	if (input.is_open()) {
		while (getline(input, result)) {
			size_t delim = result.find(' ');
			string attribute = result.substr(0, delim);
			string val = result.substr(delim);

			if (attribute == "name") {
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
			else if (attribute == "hp") {
				this->setHP(std::stoi(val));
			}
			else if (attribute == "className") {
				this->charClassName = val;
			}
			else if (attribute == "strength") {
				this->abilities.strength = std::stoi(val);
			}
			else if (attribute == "intelligence") {
				this->abilities.intelligence = std::stoi(val);
			}
			else if (attribute == "wisdom") {
				this->abilities.wisdom = std::stoi(val);
			}
			else if (attribute == "constitution") {
				this->abilities.constitution = std::stoi(val);
			}
			else if (attribute == "charisma") {
				this->abilities.charisma = std::stoi(val);
			}
			else if (attribute == "dexterity") {
				this->abilities.dexterity = std::stoi(val);
			}


		}
		input.close();

	}


}
