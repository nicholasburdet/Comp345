/*
Author: Nicholas Burdet
Id: 29613773
Course: COMP 345
Assignment 1 Part 2: Map

Editscreen cpp file

This cpp file queries the user for new/load options for map generation as well as map size
if new map is created.

Initializes the size of the map and sets the tile resolution lower to accomodate more tiles 
on screen so the user can view the whole map at once while editing.
*/
#include "editscreen.h"
#include "logic.h"
#include <QDebug>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QtWidgets>
#include <QInputDialog>


editscreen::editscreen(char n[])
{
	bool ok1;
	bool ok2;
	bool ok3;

	//Minimum width, height, default resolution, and minimum x resolution
	int width = 4;
	int height = 4;
	int resolution = 50;
	int minimumXRes = 7;

	int newOrLoad = 0;
	log = new logic;

	newOrLoad = QInputDialog::getInt(this, "New Map (0) or Load Map (1)", tr("Choose:"), 0, 0, 1, 1, &ok3);

	if (newOrLoad == 0)
	{
		//should have default wid/hei and values for int values below
		width = QInputDialog::getInt(this, "Enter the width", tr("Width:"), width, width, 100, 1, &ok1);
		height = QInputDialog::getInt(this, "Enter the height", tr("Height:"), height, height, 100, 1, &ok2);
		log->initialize(width, height);
	}
	else
	{
		log->loadMap();
		width = log->getWidth();
		height = log->getHeight();
	}

	resolution = checkResolution(width, height);
	log->setResolution(resolution);

	setCentralWidget(log);
	setWindowTitle(tr(n));
	int windowResX = width*resolution;
	if (width < minimumXRes)
	{
		windowResX = minimumXRes*resolution;
	}

	resize(windowResX, (height*resolution)+resolution*2);
}

int editscreen::checkResolution(int w, int h)
{
	//This section is so that the user can see any size of map on screen (roughly) 100x100 max
	if (h > 95)
	{
		return 8;
	}
	if (h > 80)
	{
		return 10;
	}
	if (h > 60)
	{
		return 12;
	}
	if (w > 80 || h > 40)
	{
		return 15;
	}
	if (w > 70 || h > 35)
	{
		return 20;
	}
	if (w > 60 || h > 30)
	{
		return 25;
	}
	if (w > 50 || h > 25)
	{
		return 30;
	}
	if (w > 40 || h > 20)
	{
		return 35;
	}
	if (w > 30 || h > 15)
	{
		return 40;
	}
	return 50;
	

	
}


