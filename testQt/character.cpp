#pragma once

/*
Author: Nicholas Burdet
Id: 29613773
Course: COMP 345
Assignment 2 Part 2: Map Editor

Character cpp file
*/

#include "character.h"
#include <stdlib.h>
#include <set>

using namespace std;

character::character():observers()
{
	id=rand();
	level=1;
	image="";
	abilities = generateAbilities();
	HP = getMaxHP();
}
character::character(int i, string n, int l, string im):observers()
{
	id = i;
	name = n;
	level = l;
	image = im;
	abilities = generateAbilities();
	HP = getMaxHP();
}

character::character(int i, string n, int l, string im, int abList[6]) :observers()
{
	id = i;
	name = n;
	level = l;
	image = im;
	abilities = abilList{ abList[0],abList[1],abList[2],abList[3],abList[4],abList[5] };

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

void character::notifyObservers()
{
	for (observer* i : observers) {
		if (i != NULL) {
			i->notify();
		}
	}
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

