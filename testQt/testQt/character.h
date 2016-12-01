#pragma once

/*
Team #8

Authors:
Nicholas Burdet
Nathan Lacasse
Shihao Ning
Alexi Grondin

Course: COMP 345

Final Project Delivery

character header file

*/



#pragma once
#include <string>
#include "observer.h"
#include <set>
#include <memory>
#include "Dice.h"
#include <vector>

#include <QGraphicsRectItem>

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

class characterMovement : public QGraphicsPixmapItem {
public:
	void keyPressEvent(QKeyEvent * event);

};

class character
{
public:
	character();
	character(int i, std::string n, int l, std::string im, std::string subt);
	character(int i, std::string n, int l, std::string im, std::string subt, int abilities[6]);
	~character();
	void initialize(int i, std::string n, int l, std::string im);
	void setId(int i);
	void setName(std::string n);
	void setLevel(int l);
	void setHP(int hp);
	void setSubtype(std::string subt) {
		subtype = subt;
	}
	std::string getSubtype() {
		return subtype;
	}
	void decHP(int damage);
	int getArmorBonus();
	virtual int getDamageBonus();
	virtual int getAttackBonus(int attackNum=0);

	std::vector<int> getAttackBonusList();

	std::string getAttackBonusLstString();

	int getAttackPerRound() {
		return (level-1) / 5 + 1;
	}
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

	//Default to Armor and 0
	struct equipment {
		string helmetStat = "Armor Class";
		int helmetModifier = 0;
		string armorStat = "Armor Class";
		int armorModifier = 0;
		string shieldStat = "Armor Class";
		int shieldModifier = 0;
		string ringStat = "Armor Class";
		int ringModifier = 0;
		string beltStat = "Armor Class";
		int beltModifier = 0;
		string bootsStat = "Armor Class";
		int bootsModifier = 0;
		int equipAC = 0;
		int equipStrength = 0;
		int equipDexterity = 0;
		int equipConstitution= 0;
		int equipIntelligence = 0;
		int equipWisdom = 0;
		int equipCharisma = 0;
	};

	equipment currentEquipment;

	int npcUniqueID;

	int getId();
	string getName();
	int getLevel();
	character::abilList getAbilities();
	string getClassName();
	virtual int levelUp(int incAmount);
	string getImage();

	void setAbilities(abilList abili) {
		abilities = abili;
	}

	int getX();
	int getY();
	virtual abilList generateAbilities();
	//int rollDice(int faces); //Replaced with dice class
	static int getMaxRollSum(int faces, int numRolls);

	int getWeaponRange();

	//Observer related stuff

	void addObserver(observer& obs);
	void removeObserver(observer& obs);
	bool isAttached(observer* obs);
	void notifyObservers();

	bool isPlayerCharacter();
	void setPlayerCharacter(bool pc);

	void saveToFile();
	void loadFromFile(string filepath);

	int getMoveSpeed();
	int getInitiative();
	void setCurrentInitiativeRoll(int initRoll);
	int getCurrentInitiativeRoll();
	void setType(string t);
	string getType();

	void setNumberOfWeaponDice(int n);
	void setWeaponDice(int d);
	void setWeaponRange(int r);
	void setWeaponDamageBonus(int db);
	void setWeaponAttackBonus(int ab);

	int getNumberOfWeaponDice();
	int getWeaponDice();

	void takeDamage(int dmg);
	bool getDamageTaken();
	bool getAlive();
	bool damageTaken = false;
	int getCurrentHP();
	void loadEquipment();
	void checkConstitutionChange();
	void addNpcItem(string it);
	vector<string> getNpcItems();

private:
	int id;
	string name = "NULL";
	string charClassName = "fighter";
	string subtype;
	int level;
	int hitDice = 10;
	//Default 1d4 for fist weapon and 0 armor for no armor
	int numberOfWeaponDice = 1;
	int weaponDice = 4;
	int weaponRange = 1;
	int weaponAttackBonus = 0;
	int weaponDamageBonus = 0;
	//END PLACEHOLDERS
	int HP;
	int currentHP;
	abilList abilities;
	string image = "";
	int xPosition = -1;
	int yPosition = -1;

	int moveSpeed = 6;
	int initiative = 0;
	int currentInitiativeRoll = 0;
	bool playerCharacter = false;
	
	vector<string> npcItems;
	int numberNpcItems = 0;

	bool alive = true;
	int previousConstitutionBonus = 0;

	string type = "hostile"; //Will eventually be "player", "friendly" or "hostile"

	set<observer*, less<observer*>> observers;

};
#pragma once

