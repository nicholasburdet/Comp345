#include "stdafx.h"
#include "baseItem.h"


baseItem::baseItem(itemType type, bonus enhancement)
{
	(*this).type = type;
	(*this).enhancement = enhancement;
	this->id = 0;
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
