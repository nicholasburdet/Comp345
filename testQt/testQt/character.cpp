#pragma once


/*

Alexis Grondin
ID:26639569

COMP 345 Assignment 3: Character Builder

Added to this file: 
-GetAttackBonusLst returns a list of attack bonuses, given by the table (as provided in the requirement) plus an ability bonus (based on strength if using short-range weapon and dexterity otherwise)
-Data sanitation in setLevel
-Various others, unrelated to assignment requirements


*/


#include "character.h"
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <set>
#include <QDebug>
#include <sstream>

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
	subtype = "Bully";
	currentHP = HP;
	initiative = getModifier(abilities.dexterity + currentEquipment.equipDexterity);
}
character::character(int i, string n, int l, string im, string subt) :observers()
{
	id = i;
	name = n;
	level = l;
	image = im;
	abilities = generateAbilities();
	hitDice = 10; //Fighter hit dice
	HP = getMaxHP();
	subtype = subt;

	currentHP = HP;
	initiative = getModifier(abilities.dexterity + currentEquipment.equipDexterity);
}

character::character(int i, string n, int l, string im, string subt, int abList[6]) :observers()
{
	
	id = i;
	name = n;
	level = l;
	image = im;
	abilities = abilList{ abList[0],abList[1],abList[2],abList[3],abList[4],abList[5]};
	HP = getMaxHP();
	subtype = subt;
	currentHP = HP;
	initiative = getModifier(abilities.dexterity + currentEquipment.equipDexterity);

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
	currentHP = HP;
	initiative = getModifier(abilities.dexterity + currentEquipment.equipDexterity);
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
	if (l > 20) {
		level = 20;
	}
	else if (l < 0) {
		level = 1;
	}
	else {
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
	level = level+  incAmount;
	HP = HP + getModifier(abilities.constitution)*incAmount + Dice::roll(incAmount, hitDice, 0);

	currentHP = HP + currentEquipment.equipConstitution*level;
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
	currentHP = HP;
	notifyObservers();
}

void character::decHP(int damage) {
	currentHP -= damage;
}

int character::getArmorBonus() {
	return 10 + currentEquipment.equipAC + getModifier((abilities.dexterity)+ currentEquipment.equipDexterity);
}

int character::getDamageBonus() {
	return getModifier(abilities.strength + currentEquipment.equipStrength)+weaponDamageBonus;
}

/*!
	parameter: the index (starting at 0) of the attack 
	returns: -1 if index >= max number of attacks, else attack bonus
*/
int character::getAttackBonus(int attackNum)
{
	if (attackNum >= getAttackPerRound()) {
		return -1;
	}

	int levBonus = level - (attackNum * 5);

	int abBonus = weaponRange < 1 ? getModifier(abilities.strength + currentEquipment.equipStrength) : getModifier(abilities.dexterity + currentEquipment.equipDexterity);

	return levBonus + abBonus + weaponAttackBonus;

}

/*!
	Returns a vector containing the attack bonuses in order 
*/
std::vector<int> character::getAttackBonusList()
{
	int n_attack = getAttackPerRound();

	std::vector<int> attackBonuses;

	for (int i = 0; i < n_attack; i++) {
		attackBonuses.push_back(getAttackBonus(i));
	}

	return attackBonuses;
}

/*!
	Returns the attack bonuses as a string of format [0-9]+(/[0-9]+)*
*/
std::string character::getAttackBonusLstString() {

	std::stringstream ss=std::stringstream();

	std::vector<int> bonuses = getAttackBonusList();

	for (int i = 0; i < bonuses.size(); i++) {
		if (i != 0) {
			ss << "/";
		}
		ss << std::to_string(bonuses[i]);
	}

	return ss.str();
}

int character::getWeaponRange()
{
	return weaponRange;
}

void character::takeDamage(int dmg)
{
	currentHP = currentHP - dmg;
	if (currentHP <= 0)
	{
		alive = false;
	}
}

bool character::getDamageTaken()
{
	if (damageTaken)
	{
		damageTaken = false;
		return true;
	}
	return false;
}

bool character::getAlive()
{
	return alive;
}

int character::getCurrentHP()
{
	return currentHP;
}

int character::getModifier(int abilityScore) {
	return (abilityScore - 10) / 2;
}

int character::getMaxHP() {
	int maxHP = (getModifier(this->abilities.constitution + currentEquipment.equipConstitution)*((this->level)) + this->hitDice + Dice::roll(level-1, this->hitDice, 0));
	return maxHP;
}

int character::getMoveSpeed() {
	return moveSpeed;
}

int character::getInitiative() {
	return initiative;
}

void character::setCurrentInitiativeRoll(int initRoll)
{
	currentInitiativeRoll = initRoll;
}

int character::getCurrentInitiativeRoll()
{
	return currentInitiativeRoll;
}

void character::setType(string t)
{
	type = t;
}

string character::getType()
{
	return type;
}

void character::setNumberOfWeaponDice(int n)
{
	numberOfWeaponDice = n;
}

void character::setWeaponDice(int d)
{
	weaponDice = d;
}

void character::setWeaponRange(int r)
{
	weaponRange = r;
}

void character::setWeaponDamageBonus(int db)
{
	weaponDamageBonus = db;
}

void character::setWeaponAttackBonus(int ab)
{
	weaponAttackBonus = ab;
}

int character::getNumberOfWeaponDice()
{
	return numberOfWeaponDice;
}

int character::getWeaponDice()
{
	return weaponDice;
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
		output << "level" << " " << level << endl;
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
		
		//Load equipment here?
		loadEquipment();

		currentHP = HP + ((currentEquipment.equipConstitution)/2)*level;
		initiative = getModifier(abilities.dexterity + currentEquipment.equipDexterity);
	}
}

void character::loadEquipment()
{
	//Potentially more robust for NPCs?
	//Currently just for single player

	string result;
	string customItemsFile = "Resources/wornItems.txt";
	ifstream equipInput(customItemsFile);

	if (equipInput.is_open()) {
		while (getline(equipInput, result))
		{
			std::istringstream idS(result);
			string sID;
			string slot;
			string attribute;
			string type;
			std::getline(idS, sID, '|');
			std::getline(idS, slot, '|');
			std::getline(idS, sID, '|');
			std::getline(idS, attribute, '|');
			std::getline(idS, sID, '|');
			string valS = sID;
			int val = atoi(sID.c_str());
			std::getline(idS, type);

			if (slot == "Helmet")
			{
				currentEquipment.helmetModifier = val;
				currentEquipment.helmetStat = attribute;
			}
			if (slot == "Armor")
			{
				currentEquipment.armorModifier = val;
			}
			if (slot == "Shield")
			{
				currentEquipment.shieldModifier = val;
			}
			if (slot == "Ring")
			{
				currentEquipment.ringModifier = val;
				currentEquipment.ringStat = attribute;
			}
			if (slot == "Belt")
			{
				currentEquipment.beltModifier = val;
				currentEquipment.beltStat = attribute;
			}
			if (slot == "Boots")
			{
				currentEquipment.bootsModifier = val;
				currentEquipment.bootsStat = attribute;
			}
			if (slot == "Weapon")
			{
				std::istringstream inputString(type);
				std::getline(inputString, sID, 'd');
				numberOfWeaponDice = atoi(sID.c_str());
				std::getline(inputString, sID);
				weaponDice = atoi(sID.c_str());

				if (attribute == "Attack Bonus")
				{
					weaponDamageBonus = 0;
					weaponAttackBonus = val;
				}
				if (attribute == "Damage Bonus")
				{
					weaponAttackBonus = 0;
					weaponDamageBonus = val;
				}
			}
		}
	}
	equipInput.close();

	//Incase player constitution changes after equip, will modify amount (equip CON only affects CURRENT hp)
	previousConstitutionBonus = currentEquipment.equipConstitution;

	//Equip mods calculated here
	//Start by resetting them
	currentEquipment.equipAC = 0;
	currentEquipment.equipStrength = 0;
	currentEquipment.equipDexterity = 0;
	currentEquipment.equipConstitution = 0;
	currentEquipment.equipIntelligence = 0;
	currentEquipment.equipWisdom = 0;
	currentEquipment.equipCharisma = 0;

	int totalAC = 0;
	int totalStr = 0;
	int totalDex = 0;
	int totalCon = 0;
	int totalInt = 0;
	int totalWis = 0;
	int totalCha = 0;

	totalAC = currentEquipment.armorModifier + currentEquipment.shieldModifier;

	//This part is a bit messy, but its aggregating all the modifiers together
	if (currentEquipment.helmetStat == "Armor Class")
	{
		totalAC = totalAC + currentEquipment.helmetModifier;
	}
	if (currentEquipment.ringStat == "Armor Class")
	{
		totalAC = totalAC + currentEquipment.ringModifier;
	}
	if (currentEquipment.beltStat == "Armor Class")
	{
		totalAC = totalAC + currentEquipment.beltModifier;
	}
	if (currentEquipment.bootsStat == "Armor Class")
	{
		totalAC = totalAC + currentEquipment.bootsModifier;
	}
	currentEquipment.equipAC = totalAC;


	if (currentEquipment.helmetStat == "Intelligence")
	{
		totalInt = currentEquipment.helmetModifier;
	}
	currentEquipment.equipIntelligence = totalInt;


	if (currentEquipment.helmetStat == "Wisdom")
	{
		totalWis = totalWis + currentEquipment.helmetModifier;
	}
	if (currentEquipment.ringStat == "Wisdom")
	{
		totalWis = totalWis + currentEquipment.ringModifier;
	}
	if (currentEquipment.beltStat == "Wisdom")
	{
		totalWis = totalWis + currentEquipment.beltModifier;
	}
	currentEquipment.equipWisdom = totalWis;


	if (currentEquipment.bootsStat == "Dexterity")
	{
		totalDex = currentEquipment.bootsModifier;
	}
	currentEquipment.equipDexterity = totalDex;


	if (currentEquipment.helmetStat == "Constitution")
	{
		totalCon = totalCon + currentEquipment.helmetModifier;
	}
	if (currentEquipment.ringStat == "Constitution")
	{
		totalCon = totalCon + currentEquipment.ringModifier;
	}
	if (currentEquipment.beltStat == "Constitution")
	{
		totalCon = totalCon + currentEquipment.beltModifier;
	}
	currentEquipment.equipConstitution = totalCon;


	if (currentEquipment.ringStat == "Charisma")
	{
		totalCha = totalCha + currentEquipment.ringModifier;
	}
	if (currentEquipment.beltStat == "Charisma")
	{
		totalCha = totalCha + currentEquipment.beltModifier;
	}
	currentEquipment.equipCharisma = totalCha;


	if (currentEquipment.ringStat == "Strength")
	{
		totalStr = totalStr + currentEquipment.ringModifier;
	}
	if (currentEquipment.beltStat == "Strength")
	{
		totalStr = totalStr + currentEquipment.beltModifier;
	}
	currentEquipment.equipStrength = totalStr;
}

void character::checkConstitutionChange()
{
	if (previousConstitutionBonus > currentEquipment.equipConstitution)
	{
		currentHP = currentHP - (((previousConstitutionBonus - currentEquipment.equipConstitution) / 2)*level);
	}
	if (previousConstitutionBonus < currentEquipment.equipConstitution)
	{
		currentHP = currentHP + (((currentEquipment.equipConstitution - previousConstitutionBonus) / 2)*level);
	}
}
