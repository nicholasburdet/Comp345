#include <string>
#include "includes/json.hpp"
#include "writer.h"
using jsoncons::json;
using jsoncons::pretty_print;


json Writer::returnAllFromJson(string filePath) {

	json myArr = json::array();

	ifstream path(filePath);
	json inventory;
	path >> inventory;

	
	json obj;
	for (size_t i = 0; i < inventory.size(); ++i)
	{
		json& weapon = inventory[i];

		obj["name"] = weapon["name"].as<string>();
		obj["description"] = weapon["description"].as<string>();
		obj["damage"] = weapon["damage"].as<string>();
		obj["crit"] = weapon["crit"].as<string>();
		obj["range"] = weapon["range"].as<string>();
		obj["enchantmentTypes"] = weapon["enchantmentTypes"].as<string>();
		obj["enchantmentBonus"] = weapon["enchantmentBonus"].as<string>();

		myArr.add(obj);
	}
		path.close();
		return myArr;
}

json Writer::returnSingleFromJson(string filePath,int itemNo) {

	json arr = json::array();

	ifstream path(filePath);
	json weapons;
	path >> weapons;

	json obj;
	for (size_t i = 1; i <= weapons.size(); ++i)
	{
		json& weapon = weapons[i - 1];
		if (i == itemNo) {
			

			obj["name"] = weapon["name"].as<string>();
			obj["description"] = weapon["description"].as<string>();
			obj["damage"] = weapon["damage"].as<string>();
			obj["crit"] = weapon["crit"].as<string>();
			obj["range"] = weapon["range"].as<string>();
			obj["enchantmentTypes"] = weapon["enchantmentTypes"].as<string>();
			obj["enchantmentBonus"] = weapon["enchantmentBonus"].as<string>();



		}
	}
	path.close();
	return obj;
}

void Writer::writeToJson(string filePath, jsoncons::json arr){

	ofstream outfile(filePath);
	outfile << pretty_print(arr) << endl;
	outfile.close();

}

