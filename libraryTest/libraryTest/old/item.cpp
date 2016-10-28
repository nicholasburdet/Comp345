#include <string>
#include "includes/json.hpp"

#include "item.h"
#include "entity.h"
#include "entity_manager.h"

Item::Item(std::string id, std::string name, std::string description) :Entity(id) {
	this->name = name;
	this->description = description;
}

//Item::Item(std::string id, JsonBox::Value& v, EntityManager* mgr) : Entity(id) {
//	this->load(v, mgr);
//}

//void Item::load(JsonBox::Value& v, EntityManager* mgr) {
//	JsonBox::Object o = v.getObject();
//	this->name = o["name"].getString();
//	this->description = o["description"].getString();

//	return;
//}