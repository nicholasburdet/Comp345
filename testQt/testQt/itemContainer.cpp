#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "itemContainer.h"


using namespace std;


itemContainer::itemContainer() {};
itemContainer::~itemContainer() {}


string itemContainer::getAllFromFile(string filePath)
{

	string line, result;
	ifstream myfile(filePath);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			result += line + '\n';
		}
		myfile.close();
	}

	return result;
}

string itemContainer::getType(string filePath, int id)
{

	ifstream file(filePath);
	string str;
	string file_contents;
	string symbol = "|";
	while (getline(file, str))
	{
		size_t found = str.find(symbol);
		string str2 = str.substr(0, found);
		int temp = atoi(str2.c_str());

		if (temp == id) {
			
			std::size_t found = str.find(symbol);
			str = str.substr(found + 1, str.length());

			found = str.find(symbol);
			str = str.substr(0, found);
		}
	}

	return str;
}

string itemContainer::getName(string filePath, int id)
{

	ifstream file(filePath);
	string str;
	string file_contents;
	string symbol = "|";
	while (getline(file, str))
	{
		size_t found = str.find(symbol);
		string str2 = str.substr(0, found);
		int temp = atoi(str2.c_str());

		if (temp == id) {

			size_t found = str.find(symbol);
			str = str.substr(found + 1, str.length());

			found = str.find(symbol);
			str = str.substr(found+1,str.length());

			found = str.find(symbol);
			str = str.substr(0, found);
		}
	}

	return str;
}

string itemContainer::getEnchantment(string filePath, int id)
{

	ifstream file(filePath);
	string str;
	string file_contents;
	string symbol = "|";
	while (getline(file, str))
	{
		size_t found = str.find(symbol);
		string str2 = str.substr(0, found);
		int temp = atoi(str2.c_str());

		if (temp == id) {

			size_t found = str.find(symbol);
			str = str.substr(found + 1, str.length());

			found = str.find(symbol);
			str = str.substr(found + 1, str.length());

			found = str.find(symbol);
			str = str.substr(found + 1, str.length());

			found = str.find(symbol);
			str = str.substr(0, found);

		}
	}
	return str;
}


void itemContainer::addItemBackpack(int id)
{

	ifstream file("Resources/items.txt");
	string str;
	string file_contents;
	string symbol = "|";
	while (getline(file, str))
	{
		size_t found = str.find(symbol);
		string str2 = str.substr(0, found);
		int temp = atoi(str2.c_str());

		if (temp == id) {
			file_contents += str;
			file_contents.push_back('\n');
		}

	}
	file.close();

	ofstream myfile;
	myfile.open("Resources/backpack.txt", std::ios_base::app);
	myfile << file_contents;
	myfile.close();

}


//Accepts the Id of the item to be removed
void itemContainer::removeItemBackpack(int id)
{
	ifstream file("Resources/backpack.txt");
	string str;
	string file_contents;
	string symbol = "|";
	while (getline(file, str))
	{
		size_t found = str.find(symbol);
		string str2 = str.substr(0, found);
		int temp = atoi(str2.c_str());
	
		if (temp != id) {
			file_contents += str;
			file_contents.push_back('\n');
		}
		
	}
	file.close();

	ofstream myfile;
	myfile.open("Resources/backpack.txt");
	myfile << file_contents;
	myfile.close();

}


void itemContainer::addItemWorn(int id)
{

	ifstream file("Resources/items.txt");
	string str;
	string file_contents;
	string symbol = "|";
	int itemType=-1;
	while (getline(file, str))
	{
		size_t found = str.find(symbol);
		string str2 = str.substr(0, found);
		int temp = atoi(str2.c_str());

		if (temp == id) {
			file_contents += str;
			file_contents.push_back('\n');
		}

	}


	string file_contents2 = file_contents;

	size_t found = file_contents2.find(symbol);
	file_contents2 = file_contents2.substr(found + 1, file_contents2.length());
	found = file_contents2.find(symbol);
	file_contents2 = file_contents2.substr(0, found);


	if (file_contents2 =="Helmet")
			itemType = 0;
		
	else if (file_contents2 == "Armor")
		itemType = 1;

	else if (file_contents2 == "Shield")
		itemType = 2;

	else if (file_contents2 == "Ring")
		itemType = 3;

	else if (file_contents2 == "Belt")
		itemType = 4;

	else if (file_contents2 == "Boots")
		itemType = 5;

	else if (file_contents2 == "Weapon")
		itemType = 6;


	ifstream myfile("Resources/"+ dirName +"wornItems.txt");
	
	string new1;
	string fc;
	int count = 0;
	while (getline(myfile, new1)) {
	
		if (count != itemType) {

			fc += new1;
			fc.push_back('\n');
		}
		else {
			fc += file_contents;
		}

		count++;
	};

	myfile.close();

	ofstream writer("Resources/"+ dirName +"wornItems.txt");
	writer << fc;
	writer.close();
}


void itemContainer::removeItemWorn(string file_contents2)
{
	
	int itemType = -1;

	if (file_contents2 == "Helmet")
		itemType = 0;

	else if (file_contents2 == "Armor")
		itemType = 1;

	else if (file_contents2 == "Shield")
		itemType = 2;

	else if (file_contents2 == "Ring")
		itemType = 3;

	else if (file_contents2 == "Belt")
		itemType = 4;

	else if (file_contents2 == "Boots")
		itemType = 5;

	else if (file_contents2 == "Weapon")
		itemType = 6;


	ifstream myfile("Resources/wornItems.txt");
	string new1;
	string fc;
	int count = 0;
	while (getline(myfile, new1)) {

		if (count != itemType) {

			fc += new1;
			fc.push_back('\n');
		}
		else {
			fc += "\n";
		}

		count++;
	};

	myfile.close();


	ofstream writer("Resources/wornItems.txt");
	writer << fc;
	writer.close();

}
;




//opens file, reads each line until the ID is found, then returns the bonus for the item with the corresponding ID
int itemContainer::getBonus(string filePath, int id) {

	ifstream file(filePath);
	string str;
	string file_contents;
	string symbol = "|";
	while (getline(file, str))
	{
		size_t found = str.find(symbol);
		string str2 = str.substr(0, found);
		int temp = atoi(str2.c_str());

		if (temp == id) {

			size_t found = str.find(symbol);
			str = str.substr(found + 1, str.length());

			found = str.find(symbol);
			str = str.substr(found + 1, str.length());

			found = str.find(symbol);
			str = str.substr(found + 1, str.length());

			found = str.find(symbol);
			str = str.substr(found + 1, str.length());

			found = str.find(symbol);
			str = str.substr(0, found);

		}
	}

	int temp2 = atoi(str.c_str());
	return temp2;

}
string itemContainer::getDiceOrGrade(string filePath, int id)
{

	ifstream file(filePath);
	string str;
	string file_contents;
	string symbol = "|";
	while (getline(file, str))
	{
		size_t found = str.find(symbol);
		string str2 = str.substr(0, found);
		int temp = atoi(str2.c_str());

		if (temp == id) {

			size_t found = str.find(symbol);
			str = str.substr(found + 1, str.length());

			found = str.find(symbol);
			str = str.substr(found + 1, str.length());

			found = str.find(symbol);
			str = str.substr(found + 1, str.length());

			found = str.find(symbol);
			str = str.substr(found + 1, str.length());

			found = str.find(symbol);
			str = str.substr(found + 1, str.length());

			found = str.find(symbol);
			str = str.substr(0, found);


		}
	}
	return str;

}
;



