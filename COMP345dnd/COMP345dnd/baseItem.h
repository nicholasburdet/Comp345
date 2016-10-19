#pragma once
class baseItem
{
public:

	enum BonusType { Intelligence, Wisdom, ArmorClass, Constitution, Charisma, AttackBonus, DamageBonus, Strength, Dexterity };

	enum itemType { helmet, armor, weapon, shield, boots, ring, belt };

	struct bonus{
		BonusType type;
		int amount;//int below 5
	};

	baseItem(itemType type, bonus enhancement, int id = -1);

	baseItem(itemType type, BonusType bType, int bonusAmount, int id = -1);

	~baseItem();

	virtual bonus getEnhancement();

	itemType getType();

private:
	bonus enhancement;
	itemType type;
	int id;


};

