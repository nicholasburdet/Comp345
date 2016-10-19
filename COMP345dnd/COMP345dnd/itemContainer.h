#pragma once
#include "baseItem.h"
#include <string>
#include <map>
#include <vector>
#include <memory>

class ItemContainer
{
public:
	ItemContainer();
	~ItemContainer();


	virtual int addItem(std::shared_ptr<baseItem> item);

	std::shared_ptr<baseItem> getItem(int position);

	std::shared_ptr<baseItem> getType(baseItem::itemType type);

	std::vector<std::shared_ptr<baseItem>> getItemList();


	virtual int addItemList(std::vector<std::shared_ptr<baseItem>> itemList);

private:
	std::vector<std::shared_ptr<baseItem>> items;
};

