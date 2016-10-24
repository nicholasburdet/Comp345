/*
Author: Nicholas Burdet
Id: 29613773
Course: COMP 345
Assignment 1 Part 2: Map

Map Screen cpp file

Map Screen class holds the state of the generated map (its size, passable spaces,
start and exit). Currently has a save function for potential multiple map entities
in the main project. Also contains the method to check if a valid path exists from
entrance to exit. Explanation of method's functionality listed below.
*/

#include <iostream>
#include <fstream>
#include <string>
#include "MapScreen.h"
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
void MapScreen::initMap(int x, int y)
{
	//error checking not done for size constraints
	if (x < 1 || x>100 || y < 1 || y>100)
	{
		cout << "Error in Map Screen size generation";
		exit(1);
	}
	else
	{
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

void MapScreen::saveToFile(void)
{
	ofstream output;

	output.open("mapscreen1.txt");
	
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

	output.close();
}


void MapScreen::loadFromFile(void)
{
	ifstream input("mapscreen1.txt");

	string type;
	int value;

	input >> type >> value;
	currentX = value;
	input >> type >> value;
	currentY = value;
	input >> type >> value;
	startX = value;
	input >> type >> value;
	startY = value;
	input >> type >> value;
	endX = value;
	input >> type >> value;
	endY = value;
	input >> type >> value;
	maxX = value;
	input >> type >> value;
	maxY = value;

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

	input.close();
}