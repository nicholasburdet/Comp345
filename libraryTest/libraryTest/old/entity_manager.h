#ifndef ENTITY_MANGER_HPP
#define ENTITY_MANAGER_HPP

#include <string>
//#include <map>

#include "includes/json.hpp"

class EntityManager {
//private:
	//std::map<std::string, Entity*> data;

public:
	template<typename T>
	void loadJson(std::string filename);

	template<typename T>
	T* getEntity(std::string id);

	EntityManager();

	~EntityManager();

};

//template<typename T>
//std::string entityToString();





#endif