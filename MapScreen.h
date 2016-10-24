/*
Author: Nicholas Burdet
Id: 29613773
Course: COMP 345
Assignment 1 Part 2: Map

Map Screen header file
*/

#pragma once

//Space structure will eventually evolve to a class object that will accomodate characters/objects
//occupying the space. For the sake of this assignment, it is assumed that 4 spaces exist (entance,
//exit, grass and dirt walls).
struct Space
{
	bool passable = true;
};

class MapScreen
{
public:
	MapScreen(void);
	void initMap(int x, int y);
	int getCurrentX();
	int getCurrentY();
	int getStartX();
	int getStartY();
	int getEndX();
	int getEndY();
	void setStartX(int x);
	void setStartY(int y);
	void setEndX(int x);
	void setEndY(int y);
	bool isPassable();
	bool isPassable(int x, int y);
	void setPassable(int x, int y, bool pass);
	bool checkExit();
	int getMaxX();
	int getMaxY();
	void saveToFile();
	void loadFromFile();
private:
	//current X and Y can be used for the player location (?)
	//currently unused, to be used in later iterations
	int currentX;
	int currentY;

	Space spaces[100][100];
	//entrance and exit coordinates
	int startX;
	int startY;
	int endX;
	int endY;
	
	//map size in x and y
	int maxX;
	int maxY;
};
#pragma once
