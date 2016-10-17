#include "stdafx.h"
#include "ItemGenerator.h"
#include <memory>

ItemGenerator::ItemGenerator()
{
	//Map of item Types to itemClass description

	std::map<baseItem::itemType, itemClass> itemMapInit = {
			{ baseItem::armor, itemClass{ { baseItem::ArmorClass } } },
			{ baseItem::weapon, itemClass{ { baseItem::AttackBonus, baseItem::DamageBonus } } },
			{ baseItem::shield, itemClass{ { baseItem::ArmorClass } } },
			{ baseItem::helmet, itemClass{ { baseItem::Wisdom, baseItem::Intelligence, baseItem::ArmorClass } } },
			{ baseItem::ring, itemClass{ { baseItem::ArmorClass, baseItem::Constitution, baseItem::Strength, baseItem::Wisdom, baseItem::Charisma } } },
			{ baseItem::belt, itemClass{ { baseItem::Constitution, baseItem::Strength } } },
			{ baseItem::boots, itemClass{ { baseItem::ArmorClass, baseItem::Dexterity } } }
	};

	this->itemMap.swap(itemMapInit);

}


ItemGenerator::~ItemGenerator()
{
}

std::shared_ptr<baseItem> ItemGenerator::generateItemRnd(baseItem::itemType type){
	//Bonus value between 1 and 5
	int bonusVal = 1 + rand() % 5;

	//Get one of the enhancement types for given type
	int bonusType = rand() % (this->itemMap[type].bonusTypeList.size());

	return std::make_shared<baseItem>(type, baseItem::bonus{ (baseItem::BonusType)bonusType, bonusVal });
}

std::shared_ptr<baseItem> ItemGenerator::generateItem(baseItem::itemType type, baseItem::bonus enhancement){

	return std::make_shared<baseItem>(type, enhancement);

}