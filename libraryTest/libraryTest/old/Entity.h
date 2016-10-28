#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>

#include "includes/json.hpp"


class EntityManager;

class Entity {
public:
	std::string id;
	//Entity(std::string id) {
	//	this->id = id;
	//}
	//Destructor
	//virtual ~Entity() {}
	//virtual void load(Json::Value& v, EntityManager* mgr) = 0;

};


#endif