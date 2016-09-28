#pragma once
#include "baseItem.h"
#include <string>
#include <map>
#include <vector>
#include <memory>

class itemContainer
{
public:
	itemContainer();
	~itemContainer();


	int addItem(std::shared_ptr<baseItem> item);

	std::shared_ptr<baseItem> getItem(int position);

	std::vector<std::shared_ptr<baseItem>> getItemList();


	int addItemList(std::vector<std::shared_ptr<baseItem>> itemList);

private:
	std::vector<std::shared_ptr<baseItem>> items;
};

