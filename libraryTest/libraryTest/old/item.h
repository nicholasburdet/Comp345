#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include "includes/json.hpp"


#include "Entity.h"

class EntityManager;

class Item :public Entity {
public:
	std::string name;
	std::string description;

	Item(std::string id, std::string name, std::string description);
	//Item(std::string id, JsonBox::Value& v, EntityManager* mgr);

	//virtual void load(JsonBox::Value&, EntityManager* mgr);


};

#endif