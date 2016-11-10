
/*
Author: Nicholas Burdet
Id: 29613773
Course: COMP 345
Assignment 2 Part 3: Map Editor

Campaign header file

*/

#pragma once
#include <string>
#include "MapScreen.h"
#include <vector>

using namespace std;

//Structure that holds references to campaign map IDs and their fileNames
struct mapReference
{
	int mapIdentifier;
	string mapFileName;
};

class campaign
{
public:
	campaign();
	void loadCampaign(string filename);
	void saveCampaign();
	void setId(int i);
	void setName(string n);
	void setNumberOfMaps(int m);
	void setCurrentMapId(int i);

	string getMapFilename(int i);
	int getId();
	string getName();
	int getNumberOfMaps();
	int getCurrentMapId();

	void addMap(string filename);
private:
	vector<mapReference> mapVector;
	int numberOfMaps = 0;
	string name;
	int id;
	int currentMapId = 0;
};

