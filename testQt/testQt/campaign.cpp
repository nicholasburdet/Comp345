/*
Author: Nicholas Burdet
Id: 29613773
Course: COMP 345
Assignment 2 Part 3: Map Editor

Campaign cpp file

The campaign class is used to group and navigate through the maps in the adventure.
Instead of saving entire maps in the campaign file, the campaign file only holds
references to the maps themselves and the order they appear in.

Vectors are used and grown larger as the number of maps in the campaign increases.
*/

#include "campaign.h"
#include <iostream>
#include <fstream>

campaign::campaign()
{
	mapVector.reserve(10);
}

//Loads campaign from file, filename is absolute path and has appropriate folder passed to it
void campaign::loadCampaign(string filename)
{
	ifstream input;
	string file = filename;
	input.open(file, ios::in);

	string type;
	string mapFile;
	int mapId;

	input >> name >> id >> type >> numberOfMaps;

	mapReference tempMap;
	tempMap.mapFileName = file;
	tempMap.mapIdentifier = numberOfMaps - 1;
	
	for(int i = 0; i < numberOfMaps; i++)
	{
		if (numberOfMaps > mapVector.capacity())
		{
			mapVector.resize(mapVector.capacity() + 10);
		}
		input >> type >> mapId >> type >> mapFile;
		tempMap.mapFileName = mapFile;
		tempMap.mapIdentifier = mapId;
		mapVector.push_back(tempMap);
	}

	input.close();
}

//Saves Campaign to file, includes appropriate folder to save into for ease of navigation
void campaign::saveCampaign()
{
	ofstream output;

	string extension = "Campaigns/";
	string campaignFilename = extension;
	campaignFilename.append(name);
	campaignFilename.append(to_string(id));
	output.open(campaignFilename.append(".txt"));

	output << name << " " << id << " " << "numberOfMaps" << " " << numberOfMaps << endl;

	for (int i = 0; i < numberOfMaps; i++)
	{
		output << "id" << " " << i << " " << "fname" << " " << mapVector[i].mapFileName << endl;
	}

	output.close();
}

void campaign::setId(int i)
{
	id = i;
}

void campaign::setName(string n)
{
	name = n;
}

void campaign::setNumberOfMaps(int m)
{
	numberOfMaps = m;
}

void campaign::setCurrentMapId(int i)
{
	currentMapId = i;
}

string campaign::getMapFilename(int i)
{
	return mapVector[i].mapFileName;
}

int campaign::getId()
{
	return id;
}

string campaign::getName()
{
	return name;
}

int campaign::getNumberOfMaps()
{
	return numberOfMaps;
}

int campaign::getCurrentMapId()
{
	return currentMapId;
}

//Pushes a map structure to the mapVector and increases the number of maps by one.
void campaign::addMap(string filename)
{
	numberOfMaps++;
	if (numberOfMaps > mapVector.capacity())
	{
		mapVector.resize(mapVector.capacity() + 10);
	}
	mapReference tempMap;
	tempMap.mapFileName = filename;
	tempMap.mapIdentifier = numberOfMaps - 1;
	mapVector.push_back(tempMap);
}