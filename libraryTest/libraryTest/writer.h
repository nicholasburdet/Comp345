#pragma once
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>
#include "includes/json.hpp"

using namespace std;




class Writer {
public:
	jsoncons::json static returnAllFromJson(string filePath);
	jsoncons::json static returnSingleFromJson(string filePath,int itemNo);
	static void writeToJson(string filePath,jsoncons::json arr);

	


};


#endif
