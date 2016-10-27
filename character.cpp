#pragma once

/*
Author: Nicholas Burdet
Id: 29613773
Course: COMP 345
Assignment 2 Part 2: Map Editor

Character cpp file
*/

#include "character.h"

character::character()
{

}
character::character(int i, string n, int l, string im) 
{
	id = i;
	name = n;
	level = l;
	image = im;
}

void character::setId(int i)
{
	id = i;
}
void character::setName(string n)
{
	name = n;
}
void character::setLevel(int l)
{
	level = l;
}
void character::setImage(string im)
{
	image = im;
}
void character::setX(int x)
{
	xPosition = x;
}
void character::setY(int y)
{
	yPosition = y;
}


int character::getId()
{
	return id;
}
string character::getName()
{
	return name;
}
int character::getLevel()
{
	return level;
}
string character::getImage()
{
	return image;
}
int character::getX()
{
	return xPosition;
}
int character::getY()
{
	return yPosition;
}