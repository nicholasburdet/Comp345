/*
Author: Nicholas Burdet
Id: 29613773
Course: COMP 345
Assignment 2 Part 3: Map

Map Screen cpp file

Map Screen class holds the state of the generated map (its size, passable spaces,
start and exit). Currently has a save function for potential multiple map entities
in the main project. Also contains the method to check if a valid path exists from
entrance to exit. Explanation of method's functionality listed below.

Campaign functionality added, campaigns now have an ordered list of maps that flow
one into the other.
*/


#include <fstream>
#include "MapScreen.h"
#include <QDebug>
#include <string>
#include <iostream>
#include <math.h>
#include <sstream>
using namespace std;

//This structure, Search, is used for the searching of the map to discover
//if a path from start to end exists.
struct Search
{
	bool northSearched = false;
	bool eastSearched = false;
	bool southSearched = false;
	bool westSearched = false;
	string spaceCameFrom = "";
	bool explored = false;
	bool deadEnd = false;
};

MapScreen::MapScreen(void)
{

}
//For the matter of simplicity of coding and not using vectors,
//we will assume map sizes cannot exceed 100x100.
void MapScreen::initMap(int x, int y, string n)
{
	//error checking not done for size constraints
	if (x < 1 || x>100 || y < 1 || y>100)
	{
		cout << "Error in Map Screen size generation";
		exit(1);
	}
	else
	{
		mapName = n;
		maxX = x;
		maxY = y;
		currentX = 0;
		currentY = 0;
		startX = 0;
		startY = 0;
		endX = x-1;
		endY = y-1;
	}
}

int MapScreen::getCurrentX()
{
	return currentX;
};

int MapScreen::getCurrentY()
{
	return currentY;
};

int MapScreen::getStartX()
{
	return startX;
};

int MapScreen::getStartY()
{
	return startY;
};

int MapScreen::getEndX()
{
	return endX;
};

int MapScreen::getEndY()
{
	return endY;
};

int MapScreen::getMaxX()
{
	return maxX;
};

int MapScreen::getMaxY()
{
	return maxY;
};

void MapScreen::setCurrentX(int x)
{
	currentX = x;
};

void MapScreen::setCurrentY(int y)
{
	currentY = y;
};

void MapScreen::setStartX(int x)
{
	startX = x;
};

void MapScreen::setStartY(int y)
{
	startY = y;
};

void MapScreen::setEndX(int x)
{
	endX = x;
};

void MapScreen::setEndY(int y)
{
	endY = y;
};

bool MapScreen::isPassable()
{
	return spaces[currentX][currentY].passable;
};

bool MapScreen::isPassable(int x, int y)
{
	return spaces[x][y].passable;
};

void MapScreen::setPassable(int x, int y, bool pass)
{
	spaces[x][y].passable = pass;
};

bool MapScreen::isOccupied(int x, int y)
{
	return spaces[x][y].occupied;
};

void MapScreen::setOccupied(int x, int y, bool pass)
{
	spaces[x][y].occupied = pass;
};

int MapScreen::getNumberOfDistinctNPCs()
{
	return numberOfDistinctNPCs;
};

int MapScreen::getNumberOfNPCs()
{
	return numberOfNPCs;
};

int MapScreen::getId()
{
	return mapId;
}

string MapScreen::getName()
{
	return mapName;
}

void MapScreen::setId(int i)
{
	mapId = i;
}

void MapScreen::setName(string n)
{
	mapName = n;
}

int MapScreen::getCampaignId()
{
	return campaignId;
}

string MapScreen::getCampaignName()
{
	return campaignName;
}

void MapScreen::setCampaignId(int i)
{
	campaignId = i;
}

void MapScreen::setCampaignName(string n)
{
	campaignName = n;
}
/*************************************************************************************************************
Basic explantion for how the checkExit algorithm works.
Using a depth first algorithm, the code will establish a search array (of type search) that
will allow us to keep track of where we have searched in the map, where we have come from, etc.

The algorithm checks goes (in this order) north, west, south or east to check if a passable space exists.

If a space exists, the search algorithm moves to that space and keeps checking, while leaving behind in that
array space a trail of where it came from, so it knows which was to go back when it hits a dead end.

If the search comes to a space, and excluding the direction it came in, it finds that all 3 other directions
have either been visited OR are not passable, it marks the current space as a dead end and
the search goes back to the previous space in the trail.

If the search comes back to the beginning and finds that all 4 directions do not yield a suitable path, the
algorithm returns false.

Once the algorithm finds the exit space, it returns true and stops looking.

NOTE: This will not ensure that the fastest path is discovered. Only that at least 1 path exists.

There are more fine details about the execution of this algorithm, but the above explanation is enough to
get the jist of it.
***************************************************************************************************************/
bool MapScreen::checkExit()
{
	bool endFound = false;
	bool searching = true;
	int cX = startX;
	int cY = startY;
	Search searchArray[100][100];

	while (endFound == false)
	{
		searching = true;
		if ((searchArray[cX][cY].northSearched == false) && (searching == true) && (searchArray[cX][cY].spaceCameFrom != "North"))
		{
			//Check if north space exists
			if ((cY - 1) >= 0)
			{
				//Check if north space is passable or hasn't been explored
				if ((this->isPassable(cX, (cY - 1))) && (searchArray[cX][cY - 1].explored == false) && (searchArray[cX][cY - 1].deadEnd == false))
				{
					if (this->getEndX() == cX && this->getEndY() == cY - 1)
					{
						endFound = true;
					}
					searchArray[cX][cY].explored = true;
					searchArray[cX][cY].northSearched = true;
					cY--;
					searchArray[cX][cY].spaceCameFrom = "South";
					searching = false;
				}
				else
				{
					searchArray[cX][cY].northSearched = true;
				}

			}
			else
			{
				searchArray[cX][cY].northSearched = true;
			}
		}
		if ((searchArray[cX][cY].westSearched == false) && (searching == true) && (searchArray[cX][cY].spaceCameFrom != "West"))
		{
			//Check if east space exists
			if ((cX - 1) >= 0)
			{
				//Check if east space is passable or explored
				if ((this->isPassable((cX - 1), cY)) && (searchArray[cX - 1][cY].explored == false) && (searchArray[cX - 1][cY].deadEnd == false))
				{
					if (this->getEndX() == cX - 1 && this->getEndY() == cY)
					{
						endFound = true;
					}
					searchArray[cX][cY].explored = true;
					searchArray[cX][cY].westSearched = true;
					cX--;
					searchArray[cX][cY].spaceCameFrom = "East";
					searching = false;
				}
				else
				{
					searchArray[cX][cY].westSearched = true;
				}

			}
			else
			{
				searchArray[cX][cY].westSearched = true;
			}
		}
		if ((searchArray[cX][cY].southSearched == false) && (searching == true) && (searchArray[cX][cY].spaceCameFrom != "South"))
		{
			//Check if east space exists
			if ((cY + 1) <= maxY - 1)
			{
				//Check if east space is passable or explored
				if ((this->isPassable(cX, (cY + 1))) && (searchArray[cX][cY + 1].explored == false) && (searchArray[cX][cY + 1].deadEnd == false))
				{
					if (this->getEndX() == cX && this->getEndY() == cY + 1)
					{
						endFound = true;
					}
					searchArray[cX][cY].explored = true;
					searchArray[cX][cY].southSearched = true;
					cY++;
					searchArray[cX][cY].spaceCameFrom = "North";
					searching = false;
				}
				else
				{
					searchArray[cX][cY].southSearched = true;
				}

			}
			else
			{
				searchArray[cX][cY].southSearched = true;
			}
		}
		if ((searchArray[cX][cY].eastSearched == false) && (searching == true) && (searchArray[cX][cY].spaceCameFrom != "East"))
		{
			//Check if east space exists
			if ((cX + 1) <= maxX - 1)
			{
				//Check if east space is passable
				if ((this->isPassable((cX + 1), cY)) && (searchArray[cX + 1][cY].explored == false) && (searchArray[cX + 1][cY].deadEnd == false))
				{
					if (this->getEndX() == cX + 1 && this->getEndY() == cY)
					{
						endFound = true;
					}
					searchArray[cX][cY].explored = true;
					searchArray[cX][cY].eastSearched = true;
					cX++;
					searchArray[cX][cY].spaceCameFrom = "West";
					searching = false;
				}
				else
				{
					searchArray[cX][cY].eastSearched = true;
				}

			}
			else
			{
				searchArray[cX][cY].eastSearched = true;
			}
		}
		if (searching == true)
		{
			if (searchArray[cX][cY].spaceCameFrom.compare("North") == 0)
			{
				searchArray[cX][cY].deadEnd = true;
				cY--;
			}
			else if (searchArray[cX][cY].spaceCameFrom.compare("East") == 0)
			{
				searchArray[cX][cY].deadEnd = true;
				cX++;
			}
			else if (searchArray[cX][cY].spaceCameFrom.compare("South") == 0)
			{
				searchArray[cX][cY].deadEnd = true;
				cY++;
			}
			else if (searchArray[cX][cY].spaceCameFrom.compare("West") == 0)
			{
				searchArray[cX][cY].deadEnd = true;
				cX--;
			}
			else
			{
				return false;
			}
		}
	}
	return true;
};

void MapScreen::saveToFile()
{
	ofstream output;
	string extension = "Maps/";
	string fName = extension;
	fName.append(campaignName);
	fName.append(to_string(campaignId));
	fName.append("m");
	fName.append(to_string(mapId));
	fName.append(mapName);

	output.open(fName.append(".txt"));
	
	output << "campaignName" << " " << campaignName << " " << "campaignId" << " " << campaignId << " " << "mapId" << " " << mapId << " " << "mapName" << " " << mapName << endl;
	output << "currentX" << " " << currentX << endl;
	output << "currentY" << " " << currentY << endl;
	output << "startX" << " " << startX << endl;
	output << "startY" << " " << startY << endl;
	output << "endX" << " " << endX << endl;
	output << "endY" << " " << endY << endl;
	output << "maxX" << " " << maxX << endl;
	output << "maxY" << " " << maxY << endl;

	for (int x = 0; x < maxX; x++)
	{
		for (int y = 0; y < maxY; y++)
		{
			output << "space" << " " << x << " " << y << " " << spaces[x][y].passable << endl;
		}
	}

	output << "numberOfNPCs" << " " << numberOfNPCs << endl;

	int count = 0;
	int index = 0;
	while (count < numberOfNPCs)
	{
		if (characterEntities[index].getName() != "NULL")
		{
			output << "npcID" << " " << characterEntities[index].getId() << " " << "xPos" << " " << characterEntities[index].getX() << " " << "yPos" << " " << characterEntities[index].getY() << endl;
			count++;
		}
		index++;
	}

	output << "numberOfItems" << " " << numberOfItems << endl;

	count = 0;
	index = 0;
	while (count < numberOfItems)
	{
		if (mapItems[index].itemName != "NULL")
		{
			output << "itemX" << " " << mapItems[index].itemX << " " << "itemY" << " " << mapItems[index].itemY << " " << "itemID" << " " << mapItems[index].itemID << endl; 
			count++;
		}
		index++;
	}

	output.close();
}


void MapScreen::loadFromFile(string filename)
{
	vector<string> itemsFromFile;

	ifstream itemInput("Resources/items.txt");

	for (string itemline; getline(itemInput, itemline);)
	{
		itemsFromFile.push_back(itemline);
	}

	itemInput.close();

	ifstream input;
	input.open(filename, ios::in);

	string type;

	input >> type >> campaignName >> type >> campaignId >> type >> mapId >> type >> mapName;
	input >> type >> currentX;
	input >> type >> currentY;
	input >> type >> startX;
	input >> type >> startY;
	input >> type >> endX;
	input >> type >> endY;
	input >> type >> maxX;
	input >> type >> maxY;

	int spaceX, spaceY;
	int pass;
	for (int x = 0; x < maxX; x++)
	{
		for (int y = 0; y < maxY; y++)
		{
			input >> type >> spaceX >> spaceY >> pass;
			if (pass == 1)
			{
				spaces[spaceX][spaceY].passable = true;
			}
			else
			{
				spaces[spaceX][spaceY].passable = false;
			}
		}
	}

	input >> type >> numberOfNPCs;

	int i, xP, yP;

	for (int x = 0; x < numberOfNPCs; x++)
	{
		input >> type >> i >> type >> xP >> type >> yP;
		characterEntities[x] = characterTable[i];
		characterEntities[x].setX(xP);
		characterEntities[x].setY(yP);
		characterEntities[x].setType("hostile"); //This can be changed later
		spaces[xP][yP].occupied = true;
	}

	
	input >> type >> i;
	string itemText;
	int itemID;
	
	for (int x = 0; x < i; x++)
	{
		input >> type >> xP >> type >> yP >> type >> itemID;
		itemText = itemsFromFile[itemID];
		addItem(xP, yP, itemText);
	}
	
	input.close();
}

//This method will load all DISTINCT NPCs into an identity table, so in the case of
//adding or retrieving them, it won't go into the .txt file every time.
void MapScreen::loadNPCs(void)
{
	ifstream input("npc.txt");

	string type;

	int id;
	string name;
	int level;
	string image;

	input >> type >> id >> type >> name >> type >> level >> type >> image;
	
	if (!input.eof())
	{
		characterTable[id] = character(id, name, level, image);
		numberOfDistinctNPCs++;
	}

	while (!input.eof())
	{
		input >> type >> id >> type >> name >> type >> level >> type >> image;
		characterTable[id] = character(id, name, level, image);
		numberOfDistinctNPCs++;
	}

	input.close();
}

//This method adds an NPC onto the map, with its ID and position and adds them
//to the entity table
//NOTE: This is not for creating new NPCs
bool MapScreen::addNPC(int id, int xPos, int yPos)
{
	if (numberOfNPCs >= 100)
	{
		return false;
	}
	numberOfNPCs++;

	int i = 0;
	while (characterEntities[i].getName() != "NULL")
	{
		i++;
	}

	characterEntities[i] = characterTable[id];
	characterEntities[i].setX(xPos);
	characterEntities[i].setY(yPos);
	spaces[xPos][yPos].occupied = true;

	return true;
}

//This method removes the NPC at the location on the map given and
//removes them from the entity table. This method is only called if
//the widget wants to change the contents of the space containing an NPC
void MapScreen::removeNPC(int xPos, int yPos)
{
	int index = 0;
	int count = 0;
	bool found = false;


	for(int i = 0; i < numberOfNPCs+numberOfRemovedNPCs; i++)
	{
		if (characterEntities[i].getName() != "NULL")
		{
			if (characterEntities[i].getX() == xPos && characterEntities[i].getY() == yPos)
			{
				found = true;
				characterEntities[i] = character(); //Fills with empty character
			}
		}
	}

	if (found)
	{
		numberOfRemovedNPCs++;
		numberOfNPCs--;
		spaces[xPos][yPos].occupied = false;
	}
	if (numberOfNPCs < 0)
	{
		numberOfNPCs = 0; //Potentially useless
	}
}

//Generates the filename for this map to pass along to campaign or whatnot
string MapScreen::getFilename()
{
	string fName;
	fName = campaignName;
	fName.append(to_string(campaignId));
	fName.append("m");
	fName.append(to_string(mapId));
	fName.append(mapName);
	fName.append(".txt");

	return fName;
}

bool MapScreen::npcMovement(int npcID, int destX, int destY)
{
	int beginX = characterEntities[npcID].getX();
	int beginY = characterEntities[npcID].getY();
	//Dead NPCs may get changed to name DEAD to signify dead?
	if (characterEntities[npcID].getName() != "DEAD" || characterEntities[npcID].getName() != "NULL")
	{
		int npcX = characterEntities[npcID].getX();
		int npcY = characterEntities[npcID].getY();

		struct moveArray
		{
			int xSpace;
			int ySpace;
			int stepsTaken = -1;
			bool checked = false;
			double distance = 1000;
		};

		vector<moveArray> pathfinding;

		moveArray mv;
		moveArray checkMoves[100][100];
		mv.xSpace = npcX;
		mv.ySpace = npcY;
		mv.stepsTaken = 0;

		checkMoves[npcX][npcY].stepsTaken = 0;
		pathfinding.push_back(mv);
		//Goes through each step
		for (int i = 1; i <= characterEntities[npcID].getMoveSpeed(); i++)
		{
			//Goes through the pathfinding array
			for (int index = 0; index < pathfinding.size(); index++)
			{
				//CHECK IF ADDING TO ARRAY PATHFINDING WHILE ITERATING THROUGH IT CAUSES ISSUES
				//If it sees a space with current steps - 1, we will check the adjacent squares if it is -1
				if (pathfinding[index].stepsTaken == (i - 1))
				{
					//up
					if (!(spaces[pathfinding[index].xSpace][pathfinding[index].ySpace - 1].occupied) && spaces[pathfinding[index].xSpace][pathfinding[index].ySpace - 1].passable && (pathfinding[index].ySpace) > 0)
					{
						if (checkMoves[pathfinding[index].xSpace][pathfinding[index].ySpace - 1].stepsTaken < 0)
						{
							checkMoves[pathfinding[index].xSpace][pathfinding[index].ySpace-1].stepsTaken = i;
							mv.xSpace = pathfinding[index].xSpace;
							mv.ySpace = pathfinding[index].ySpace - 1;
							mv.stepsTaken = i;
							pathfinding.push_back(mv);
						}
					}
					
					//down
					if (!(spaces[pathfinding[index].xSpace][pathfinding[index].ySpace + 1].occupied) && spaces[pathfinding[index].xSpace][pathfinding[index].ySpace + 1].passable && (pathfinding[index].ySpace) < (maxY - 1))
					{
						if (checkMoves[pathfinding[index].xSpace][pathfinding[index].ySpace + 1].stepsTaken < 0)
						{
							checkMoves[pathfinding[index].xSpace][pathfinding[index].ySpace+1].stepsTaken = i;
							mv.xSpace = pathfinding[index].xSpace;
							mv.ySpace = pathfinding[index].ySpace + 1;
							mv.stepsTaken = i;
							pathfinding.push_back(mv);
						}
					}
					
					//left
					if (!(spaces[pathfinding[index].xSpace - 1][pathfinding[index].ySpace].occupied) && spaces[pathfinding[index].xSpace - 1][pathfinding[index].ySpace].passable && (pathfinding[index].xSpace) > 0)
					{
						if (checkMoves[pathfinding[index].xSpace-1][pathfinding[index].ySpace].stepsTaken < 0)
						{
							checkMoves[pathfinding[index].xSpace-1][pathfinding[index].ySpace].stepsTaken = i;
							mv.xSpace = pathfinding[index].xSpace - 1;
							mv.ySpace = pathfinding[index].ySpace;
							mv.stepsTaken = i;
							pathfinding.push_back(mv);
						}
					}

					//right
					if (!(spaces[pathfinding[index].xSpace + 1][pathfinding[index].ySpace].occupied) && spaces[pathfinding[index].xSpace + 1][pathfinding[index].ySpace].passable && (pathfinding[index].xSpace) < (maxX - 1))
					{
						if (checkMoves[pathfinding[index].xSpace + 1][pathfinding[index].ySpace].stepsTaken < 0)
						{
							checkMoves[pathfinding[index].xSpace + 1][pathfinding[index].ySpace].stepsTaken = i;
							mv.xSpace = pathfinding[index].xSpace + 1;
							mv.ySpace = pathfinding[index].ySpace;
							mv.stepsTaken = i;
							pathfinding.push_back(mv);
						}
					}
				}
			}
		}

		moveArray closestSpace;
		closestSpace.stepsTaken = 1000;
		//Now to determine which space is closest to the player
		for (int index = 0; index < pathfinding.size(); index++)
		{
			double length = sqrt((destX - pathfinding[index].xSpace)*(destX - pathfinding[index].xSpace) + (destY - pathfinding[index].ySpace)*(destY - pathfinding[index].ySpace));
			
			if (length < closestSpace.distance && length != 0)
			{
				closestSpace.stepsTaken = pathfinding[index].stepsTaken;
				closestSpace.xSpace = pathfinding[index].xSpace;
				closestSpace.ySpace = pathfinding[index].ySpace;
				closestSpace.distance = length;
			}
			else if(length == closestSpace.distance)
			{
				if (pathfinding[index].stepsTaken < closestSpace.stepsTaken)
				{
					closestSpace.stepsTaken = pathfinding[index].stepsTaken;
					closestSpace.xSpace = pathfinding[index].xSpace;
					closestSpace.ySpace = pathfinding[index].ySpace;
				}
			}
		}

		spaces[characterEntities[npcID].getX()][characterEntities[npcID].getY()].occupied = false;
		spaces[closestSpace.xSpace][closestSpace.ySpace].occupied = true;
		characterEntities[npcID].moveTo(closestSpace.xSpace, closestSpace.ySpace);
		if (beginX == characterEntities[npcID].getX() && beginY == characterEntities[npcID].getY())
		{
			return false; //did not move
		}
		else
		{
			return true; //moved
		}
	}

	return false;
}

void MapScreen::loadPlayerCharacter(string filename)
{
	playerCharacter.loadFromFile(filename);
}

string MapScreen::playerAttack(int sX, int sY, string dir, bool fullAttack)
{
	string combatText = "";

	int foundNPC = -1;

	int weaponRange = playerCharacter.getWeaponRange();
	bool npcFound = false;
	bool rangeError = false;
	int rangeCheck = 1;

	while (!npcFound && rangeCheck <= weaponRange && !rangeError)
	{
		for (int i = 0; i < numberOfNPCs; i++)
		{
			if (characterEntities[i].getX() == sX && characterEntities[i].getY() == sY)
			{
				foundNPC = i;
				npcFound = true;
			}
		}

		if (spaces[sX][sY].passable == false)
		{
			foundNPC = -2;
			rangeError = true;
		}

		if (weaponRange > 1)
		{
			if (dir == "up")
			{
				sY--;
				if (sY < 0)
				{
					rangeError = true;
				}
			}
			else if (dir == "down")
			{
				sY++;
				if (sY > maxY-1)
				{
					rangeError = true;
				}
			}
			else if (dir == "left")
			{
				sX--;
				if (sX < 0)
				{
					rangeError = true;
				}
			}
			else if (dir == "right")
			{
				sX++;
				if (sX > maxX-1)
				{
					rangeError = true;
				}
			}
		}
		
		rangeCheck++;
	}
	if (foundNPC == -1)
	{
		return "You attack into an empty space! Nothing happens.";
	}
	else if (foundNPC == -2)
	{
		return "You attack a wall! Nothing happens.";
	}
	else
	{
		//Combat rolls and stuff goes here
		int roll = Dice::roll(1, 20, 0);
		combatText.append("Attack roll (d20): ");
		combatText.append(std::to_string(roll));
		if (roll == 1)
		{
			combatText.append(". Critical miss!");
		}
		else if (roll == 20)
		{
			combatText.append(". Critical hit!");
			combatText.append(" DAMAGE TEXT GOES HERE.");
		}
		else
		{
			if ((roll + playerCharacter.getAttackBonus() > characterEntities[foundNPC].getArmorBonus()))
			{
				combatText.append("+");
				combatText.append(std::to_string(playerCharacter.getAttackBonus()));
				combatText.append(". Enemy hit!");
				combatText.append(" DAMAGE TEXT GOES HERE.");
			}
			else
			{
				combatText.append("+");
				combatText.append(std::to_string(playerCharacter.getAttackBonus()));
				combatText.append(". Enemy dodges your attack!");
			}
		}
		//NPCs that are friendly will become hostile when attacked
		if (characterEntities[foundNPC].getType() == "friendly")
		{
			characterEntities[foundNPC].setType("hostile");
			combatText.append(" Enemy is now hostile!");
		}
	}
	return combatText;
}

string MapScreen::npcAttack(int npcID, bool moved)
{
	string combatText = "Nothing";

	int npcX = characterEntities[npcID].getX();
	int npcY = characterEntities[npcID].getY();
	bool attack = false;

	for (int i = 1; i <= characterEntities[npcID].getWeaponRange(); i++)
	{
		//Check up
		if (npcX == currentX && (npcY-i) == currentY)
		{
			attack = true;
		}
		//Check down
		if (npcX == currentX && (npcY+i) == currentY)
		{
			attack = true;
		}
		//Check left
		if ((npcX - i) == currentX && npcY == currentY)
		{
			attack = true;
		}
		//Check right
		if ((npcX + i) == currentX && npcY == currentY)
		{
			attack = true;
		}
	}

	if (attack)
	{
		combatText = "NPC ";
		combatText.append(std::to_string(npcID));
		combatText.append(" attacks!");

		//Combat rolls and stuff goes here
		int roll = Dice::roll(1, 20, 0);
		if (roll == 1)
		{
			combatText.append(" Critical miss!");
			return combatText;
		}
		else if (roll == 20)
		{
			combatText.append(" Critical hit!");
			combatText.append(" DAMAGE TEXT GOES HERE.");
			return combatText;
		}
		else
		{
			if ((roll + characterEntities[npcID].getAttackBonus() > playerCharacter.getArmorBonus()))
			{
				combatText.append(" You were hit!");
				combatText.append(" DAMAGE TEXT GOES HERE.");
				return combatText;
			}
			else
			{
				combatText.append(" You dodge the enemy attack!");
				return combatText;
			}
		}
	}
	return combatText;
}

void MapScreen::addItem(int x, int y, string itemText)
{
	Items tempItem;
	tempItem.itemX = x;
	tempItem.itemY = y;
	tempItem.itemName = itemText;

	std::istringstream idS(itemText);
	string sID;
	std::getline(idS, sID, '|');

	tempItem.itemID = atoi(sID.c_str());

	setOccupied(x, y, true);

	mapItems.push_back(tempItem);
	numberOfItems++;
}

void MapScreen::removeItem(int x, int y)
{
	int index = -1;
	for (int i = 0; i < mapItems.size(); i++)
	{
		if (mapItems[i].itemX == x && mapItems[i].itemY == y)
		{
			index = i;
		}
	}
	if (index != -1)
	{
		mapItems.erase(mapItems.begin()+index);
		numberOfItems--;
		setOccupied(x, y, false);
	}
}

int MapScreen::getNumberOfItems()
{
	return numberOfItems;
}

string MapScreen::viewItems()
{
	string itemList = "";

	for (int i = 0; i < mapItems.size(); i++)
	{
		itemList.append("X: ");
		itemList.append(std::to_string(mapItems[i].itemX));
		itemList.append(" Y: ");
		itemList.append(std::to_string(mapItems[i].itemY));
		itemList.append(" ItemID: ");
		itemList.append(std::to_string(mapItems[i].itemID));
		itemList.append(" Item: ");
		itemList.append(mapItems[i].itemName);
		itemList.append("\n");
	}
	return itemList;
}