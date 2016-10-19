#include "stdafx.h"
#include "baseItem.h"


baseItem::baseItem(itemType type, bonus enhancement, int id)
{
	(*this).type = type;
	(*this).enhancement = enhancement;
	this->id = id < 0 ? rand() : id;
}

baseItem::baseItem(itemType type, BonusType bType, int bonusAmount, int id){
	this->type = type;
	this->enhancement = bonus{ bType, bonusAmount };
	this->id = id < 0 ? rand() : id;
}


baseItem::~baseItem()
{
}

//Returns the item enhancement struct
baseItem::bonus baseItem::getEnhancement(){

	return this->enhancement;

};


//Returns the type of the items
baseItem::itemType baseItem::getType(){

	return this->type;
};
