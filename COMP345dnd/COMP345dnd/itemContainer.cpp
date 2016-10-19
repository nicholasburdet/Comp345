#include "stdafx.h"
#include "ItemContainer.h"
#include "baseItem.h"


ItemContainer::ItemContainer() : items()
{

}


ItemContainer::~ItemContainer()
{
}

//Adds an item in the list and returns its position
int ItemContainer::addItem(std::shared_ptr<baseItem> item){
	this->items.push_back(item);

	return this->items.size() - 1;
};

//Return item at a given position in the list
std::shared_ptr<baseItem> ItemContainer::getItem(int position){

	return this->items[position];
};

std::shared_ptr<baseItem> ItemContainer::getType(baseItem::itemType type){

	for (int i = 0; i < this->items.size; i++){
		if ((this->items[i])->getType() == type){
			return this->items[i];
		}
	}

	return nullptr;

}


//Returns the list of items
std::vector<std::shared_ptr<baseItem>> ItemContainer::getItemList(){
	return this->items;
};

//Inserts a list of items in the container and returns the index of the first item of the list
int ItemContainer::addItemList(std::vector<std::shared_ptr<baseItem>> itemList){
	int position = this->items.size() - 1;
	
	this->items.insert(items.begin(), itemList.begin(), itemList.end());

	return position;
};