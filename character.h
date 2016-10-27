#pragma once

/*
Author: Nicholas Burdet
Id: 29613773
Course: COMP 345
Assignment 2 Part 2: Map Editor

Character header file

This is purely a temporary arrangement file
*/

#pragma once
#include <string>
using namespace std;



class character
{
public:
	character();
	character(int i, string n, int l, string im);
	void setId(int i);
	void setName(string n);
	void setLevel(int l);
	void setImage(string im);

	void setX(int x);
	void setY(int y);

	int getId();
	string getName();
	int getLevel();
	string getImage();

	int getX();
	int getY();
private:
	int id;
	string name = "NULL";
	int level;
	string image;
	int xPosition = -1;
	int yPosition = -1;
};
#pragma once
