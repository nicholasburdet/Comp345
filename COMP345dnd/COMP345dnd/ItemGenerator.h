#pragma once
#include "baseItem.h"
#include <string>
#include <map>
#include <vector>
#include <random>
#include <memory>

class ItemGenerator
{
public:
	ItemGenerator();
	~ItemGenerator();

	//Struct describing an item class
	struct itemClass{ std::vector<baseItem::BonusType> bonusTypeList;
	};

	//Given an item class, returns an item with random enhancement within item class constrictions
	std::shared_ptr<baseItem> generateItemRnd(baseItem::itemType type);

	//Given an item class and an enhancement, returns an item
	std::shared_ptr<baseItem> generateItem(baseItem::itemType type, baseItem::bonus enhancement);

private:
	std::map<baseItem::itemType, itemClass> itemMap;
};

