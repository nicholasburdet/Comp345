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
