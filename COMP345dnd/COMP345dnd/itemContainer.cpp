#include "stdafx.h"
#include "itemContainer.h"


itemContainer::itemContainer() : items()
{

}


itemContainer::~itemContainer()
{
}

//Adds an item in the list and returns its position
int itemContainer::addItem(std::shared_ptr<baseItem> item){
	this->items.push_back(item);

	return this->items.size() - 1;
};

//Return item at a given position in the list
std::shared_ptr<baseItem> itemContainer::getItem(int position){

	return this->items[position];
};

//Returns the list of items
std::vector<std::shared_ptr<baseItem>> itemContainer::getItemList(){
	return this->items;
};

//Inserts a list of items in the container and returns the index of the first item of the list
int itemContainer::addItemList(std::vector<std::shared_ptr<baseItem>> itemList){
	int position = this->items.size() - 1;
	
	this->items.insert(items.begin(), itemList.begin(), itemList.end());

	return position;
};