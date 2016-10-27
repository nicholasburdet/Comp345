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
#include <QObject>

editscreen::editscreen(char n[])
{
	createMenus();
}

void editscreen::editMap()
{
	bool ok1;
	bool ok2;
	bool ok3;

	//Minimum width, height, default resolution, and minimum x resolution
	int width = 4;
	int height = 4;
	int resolution = 50;
	int minimumXRes = 7;
	int addedHeight = 20;
	
	//NEW
	int minimumWidth = 1;
	int minimumHeight = 1;

	int newOrLoad = 0;
	log = new logic;

	newOrLoad = QInputDialog::getInt(this, "=Map Editor=", tr("New Map (0) or Load Map (1)"), 0, 0, 1, 1, &ok3);

	if (newOrLoad == 0)
	{
		//should have default wid/hei and values for int values below
		width = QInputDialog::getInt(this, "==Width==", tr("Enter the width:"), minimumWidth, minimumWidth, 100, 1, &ok1);
		if (width < 4)
		{
			//This was added to check in case we want to make hallways
			minimumHeight = minimumHeight + (4 - width);
		}
		height = QInputDialog::getInt(this, "=Height=", tr("Enter the height:"), minimumHeight, minimumHeight, 100, 1, &ok2);
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
	setWindowTitle(tr("Edit Map"));
	int windowResX = width*resolution;
	if (width < minimumXRes)
	{
		windowResX = minimumXRes*resolution;
	}

	//resize(windowResX, (height*resolution)+(resolution*2)+addedHeight);

	//This code allows it so the window cannot be resized
	this->setFixedWidth(windowResX);
	this->setFixedHeight((height*resolution) + (resolution * 3) + addedHeight);
	
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

void editscreen::closeEvent(QCloseEvent *event)
{
	
}
bool editscreen::getWindowOpen()
{
	return log->getWindowOpen();
}

void editscreen::createMenus()
{
	editMapAction = new QAction(tr("&Edit Map"), this);
	connect(editMapAction, SIGNAL(triggered()), this, SLOT(editMap()));

	editMenu = new QMenu(tr("&Edit"), this);
	editMenu->addAction(editMapAction);

	menuBar()->addMenu(editMenu);

}

