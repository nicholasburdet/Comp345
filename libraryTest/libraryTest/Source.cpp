#include <iostream>
#include <string>
#include <map>
#include <windows.h>

#include "writer.h"
#include "includes/json.hpp"
#include "includes/jsoncons_ext/jsonpath/json_query.hpp"
using jsoncons::json;
using jsoncons::pretty_print;
using namespace std;





int testMenu() {


	string Menu[3] = { "Start Game", "Options", "Exit" };
	int pointer = 0;

	while (true)
	{
		system("cls");

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "Main Menu\n\n";

		for (int i = 0; i < 3; ++i)
		{
			if (i == pointer)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				cout << Menu[i] << endl;
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << Menu[i] << endl;
			}
		}

		while (true)
		{
			if (GetAsyncKeyState(VK_UP) != 0)
			{
				pointer -= 1;
				if (pointer == -1)
				{
					pointer = 2;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_DOWN) != 0)
			{
				pointer += 1;
				if (pointer == 3)
				{
					pointer = 0;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_RETURN) != 0)
			{
				switch (pointer)
				{
				case 0:
				{
					cout << "\n\n\nStarting new game...";
					Sleep(1000);
				} break;
				case 1:
				{
					cout << "\n\n\nThis is the options...";
					Sleep(1000);
				} break;
				case 2:
				{
					return 0;
				} break;
				}
				break;
			}
		}

		Sleep(150);
	}



};























int main() {
label_topOfProgram:
	system("CLS");
	string option;
	string option2;

	cout << "Menu" << endl;
	cout << "========" << endl;
	cout << "1. Inventory" << endl;
	cout << "2. Add Item to inventory" << endl;
	cout << "3. Add/replace item from equipped" << endl;
	cout << "4. Testing" << endl;
	cout << "5. Exit Program" << endl;
	cout << "6. Extra" << endl;
	cout << "" << endl;
	cout << "Please make your selection:" << endl;

	cin >> option;


	if (option == "1") {
		system("CLS");
		cout << "Inventory" << endl;
		cout << "========" << endl;


		ifstream jsonInventory("includes/inventory.json");
		json weapons;
		jsonInventory >> weapons;


		for (size_t i = 0; i < weapons.size(); ++i)
		{
			json& weapon = weapons[i];
			cout << " " << i + 1 << ". ";
			string name = weapon["name"].as<string>();
			cout << name << endl;

		}


		cout << endl;
		system("pause");

		goto label_topOfProgram;
	}
	// ADD ITEM TO INVENTORY
	else if (option == "2") {
		system("CLS");
		cout << "Add Item to inventory" << endl;
		cout << "========" << endl;

		//Opens the list of weapons to be shown on the screen
		ifstream is("includes/weapons.json");
		json weapons;
		is >> weapons;

		for (size_t i = 0; i < weapons.size(); ++i)
		{
			json& weapon = weapons[i];
			cout << " " << i + 1 << ". ";
			string name = weapon["name"].as<string>();
			cout << name << endl;

		}

		cout << "Enter which item you want to add to your inventory." << endl;
		int option2;
		cin >> option2;


		
		// An array value with four elements
		json arr = json::array();





		//Writes all items from the inventory json file -- Parameter:(FilePath)
		arr = Writer::returnAllFromJson("includes/inventory.json");



		//Appends a single item from the inventory json file -- Parameters:(FilePath, Input option)
		arr.add(Writer::returnSingleFromJson("includes/weapons.json", option2));

		//Writes to json file -- Parameters:(FilePath, json array)
		Writer::writeToJson("includes/inventory.json",arr);


		goto label_topOfProgram;
	}
	else if (option == "3") {
		system("CLS");
		cout << "Add/replace item from equipped" << endl;
		cout << "========" << endl;



		map<string, string> equipped;
		equipped["helmet"] = "Full Helm";
		equipped["armor"] = "Platebody";
		equipped["shield"] = "Shield";
		equipped["ring"] = "Ring";
		equipped["belt"] = "Belt";
		equipped["boots"] = "Boots";
		equipped["weapon"] = "Dagger";


		string name;
		cin >> name;

		if (equipped.find(name) != equipped.end()) {
			cout << name << ": " << equipped[name] << endl;
		}
		else {
			cout << name << " not found." << endl;
		}


		cin >> option2;


		goto label_topOfProgram;
	}

	else if (option == "4") {
		system("CLS");
		cout << "Testing" << endl;
		cout << "========" << endl;

		//itemContainer ic;


		// An object value with four members
		json obj;
		obj["name"] = "Dagger";
		obj["description"] = "A short ornate blade in a serpentine shape.";
		obj["damage"] = "1d4";
		obj["crit"] = "19-20/x2";
		obj["range"] = "1";
		obj["enchantmentTypes"] = "Attack Bonus,Damage Bonus";
		obj["enchantmentBonus"] = "0";

		// An array value with four elements
		json arr = json::array();
		arr.add(obj);

		cout << pretty_print(arr) << endl;

		ofstream outfile("includes/test.json");



		outfile << pretty_print(arr) << endl;

		outfile.close();





		cin >> option2;


		goto label_topOfProgram;
	}
	else if (option == "6") {
		

		testMenu();


	}

	return 0;
}

