/*
Author: Nicholas Burdet
Id: 29613773
Course: COMP 345
Assignment 2 Part 3: Map

Editscreen cpp file

This cpp file handles menu and window functionalities and calls the appropriate methods in the widget depending
on user commands.

Menu commands are generally handled here, allowing the user to choose between program options. This file will eventually
serve as the UI controller for the entire game project for the most part
*/
#include "editscreen.h"
#include "logic.h"
#include <QDebug>
#include <QMouseEvent>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QtWidgets>
#include <QInputDialog>
#include <QObject>

//Initialize all menus here upon class initialization
editscreen::editscreen(char n[])
{
	this->setFixedWidth(400);
	this->setFixedHeight(200);
	
	newMapAction = new QAction(tr("&New Map"), this);
	connect(newMapAction, SIGNAL(triggered()), this, SLOT(newMap()));

	openMapAction = new QAction(tr("&Open Map"), this);
	connect(openMapAction, SIGNAL(triggered()), this, SLOT(openMap()));

	previousMapAction = new QAction(tr("&Previous Map"), this);
	connect(previousMapAction, SIGNAL(triggered()), this, SLOT(previousMap()));

	nextMapAction = new QAction(tr("&Next Map"), this);
	connect(nextMapAction, SIGNAL(triggered()), this, SLOT(nextMap()));

	resetMapAction = new QAction(tr("&Reset Current Map"), this);
	connect(resetMapAction, SIGNAL(triggered()), this, SLOT(resetMap()));

	mapMenuCloseAction = new QAction(tr("&Close Map Menu"), this);
	connect(mapMenuCloseAction, SIGNAL(triggered()), this, SLOT(mapMenuClose()));

	newCampaignAction = new QAction(tr("&New Campaign"), this);
	connect(newCampaignAction, SIGNAL(triggered()), this, SLOT(newCampaign()));

	openCampaignAction = new QAction(tr("&Load Campaign"), this);
	connect(openCampaignAction, SIGNAL(triggered()), this, SLOT(loadCampaign()));

	campaignMenuAction = new QAction(tr("&Campaign and Map Editor"), this);
	connect(campaignMenuAction, SIGNAL(triggered()), this, SLOT(createCampaignMenus()));

	campaignMenuCloseAction = new QAction(tr("&Close Campaign Menu"), this);
	connect(campaignMenuCloseAction, SIGNAL(triggered()), this, SLOT(campaignMenuClose()));

	editMenu = new QMenu(tr("&Main Menu"), this);
	editMenu->addAction(campaignMenuAction);
	
	mapMenu = new QMenu(tr("&Map File"), this);
	mapMenu->addAction(newMapAction);
	mapMenu->addAction(openMapAction);
	mapMenu->addAction(resetMapAction);
	mapMenu->addAction(mapMenuCloseAction);
	
	mapNavigatorMenu = new QMenu(tr("&Navigate Maps"), this);
	mapNavigatorMenu->addAction(nextMapAction);
	mapNavigatorMenu->addAction(previousMapAction);

	campaignMenu = new QMenu(tr("&Campaign Options"), this);
	campaignMenu->addAction(newCampaignAction);
	campaignMenu->addAction(openCampaignAction);
	campaignMenu->addAction(openMapAction);
	campaignMenu->addAction(campaignMenuCloseAction);

	
	createMainMenu();
}

void editscreen::editMap()
{
	bool ok1;

	//Minimum width, height, default resolution, and minimum x resolution
	int width = 4;
	int height = 4;
	int resolution = 50;
	int minimumXRes = 7;
	int addedHeight = 20;
	
	//NEW
	int minimumWidth = 1;
	int minimumHeight = 1;

	//Occasionally, we will want the logic object for the editor to persist beyond
	//iterations, incase the campaign doesn't change, for instance.
	if (!logicPersistence)
	{
		log = new logic;
	}
	logicPersistence = false;
	
	if (choice == 0)
	{
		//This choice is for new maps being created
		if (campaignCreation)
		{
			//Runs this extra code if campaign is created from scratch. New map is created afterwards
			QString campaignName = "";
			bool ok;
			while (campaignName == "")
			{
				campaignName = QInputDialog::getText(this, "==Campaign Name?==", tr("Enter Campaign Name:"), QLineEdit::Normal, "", &ok);
			}
			string cName = campaignName.toStdString();
			cName.erase(std::remove(cName.begin(), cName.end(), ' '), cName.end());
			int cId = QInputDialog::getInt(this, "==Campaign Id?==", tr("Enter Campaign Id:"), 0, 0, 100000, 1, &ok);
			log->newCampaign(cName, cId);
			campaignCreation = false;
		}
		
		//Obtains width and height from user. This makes sure rooms with less than a certain number of spaces aren't created.
		//Extremely small rooms (2-4 spaces) are extremely redundant
		width = QInputDialog::getInt(this, "==Map Width==", tr("Enter map width:"), minimumWidth, minimumWidth, 100, 1, &ok1);
		if (width < 4)
		{
			minimumHeight = minimumHeight + (4 - width);
		}
		height = QInputDialog::getInt(this, "=Map Height=", tr("Enter map height:"), minimumHeight, minimumHeight, 100, 1, &ok1);

		QString mapN = "";
		while (mapN == "")
		{
			mapN = QInputDialog::getText(this, tr("==Map Name=="), tr("Enter map name:"), QLineEdit::Normal, "", &ok1);
		}
		string mapname = mapN.toStdString();
		//All text for eventual filenames is removed of spaces to avoid read errors
		mapname.erase(std::remove(mapname.begin(), mapname.end(), ' '), mapname.end());
		log->initialize(width, height, mapname);
		
	}
	else if (choice == 1)
	{
		//This choice is for loading maps from file
		log->loadMap(fName);
		width = log->getWidth();
		height = log->getHeight();
		if (openingMap)
		{
			//This is incase you want to load a map before loading the campaign, this will load the corresponding campaign
			//without loading to last map in the campaign
			log->loadJustCampaign();
			openingMap = false;
		}
	}
	else if (choice == 2)
	{
		//This choice will load the campaign and consequently loads the last map in the campaign at the same time
		log->loadCampaign(campaignfName);
		width = log->getWidth();
		height = log->getHeight();
	}
	else if (choice == 3)
	{
		//This choice is purely incase the user wants to reset the current map on screen
		width = QInputDialog::getInt(this, "==Map Width==", tr("Enter map width:"), minimumWidth, minimumWidth, 100, 1, &ok1);
		if (width < 4)
		{
			//This was added to check in case we want to make hallways
			minimumHeight = minimumHeight + (4 - width);
		}
		height = QInputDialog::getInt(this, "=Map Height=", tr("Enter map height:"), minimumHeight, minimumHeight, 100, 1, &ok1);
		log->resetMap(width, height);
	}

	resolution = checkResolution(width, height);
	log->setResolution(resolution);

	setCentralWidget(log);
	setWindowTitle(tr("Map Editor"));
	int windowResX = width*resolution;
	if (width < minimumXRes)
	{
		windowResX = minimumXRes*resolution;
	}

	//This code allows it so the window cannot be resized by the user
	this->setFixedWidth(windowResX);
	this->setFixedHeight((height*resolution) + (resolution * 3) + addedHeight);
	//Creates map editor menu if coming from a higher menu
	if (currentMenu != "mapeditor")
	{
		createEditorMenus();
	}
}

//For creating a brand new map, assumed for an existing campaign
void editscreen::newMap()
{
	log->newMap();
	logicPersistence = true;
	choice = 0;
	editMap();
}

//Opens a map from file, both from inside and outside a loaded campaign
void editscreen::openMap()
{
	QString fileName = "";
	QString extension = "/Maps";
	fileName = QFileDialog::getOpenFileName(this, tr("Open Map"), QDir::currentPath().append(extension));
	if(fileName != "")
	{
		fName = fileName.toStdString();
		choice = 1;
	}
	while(fileName == "")
	{
		fileName = QFileDialog::getOpenFileName(this, tr("Open Map"), QDir::currentPath().append(extension));
		fName = fileName.toStdString();
		choice = 1;
	}
	openingMap = true;
	editMap();
}

//Navigates to previous map in campaign. Displays error if reached beginning
void editscreen::previousMap()
{
	if(log->previousMap())
	{
		logicPersistence = true;
		string extension = "Maps/";
		fName = extension;
		fName.append(log->getFilename());

		choice = 1;
		editMap();
	}
	else
	{
		QMessageBox message;
		message.setText("This is the first map of the campaign.");
		message.exec();
	}
}

//Navigates to next map in campaign. Displays error if end is reached.
void editscreen::nextMap()
{
	if (log->nextMap())
	{
		logicPersistence = true;
		string extension = "Maps/";
		fName = extension;
		fName.append(log->getFilename());

		choice = 1;
		editMap();
	}
	else
	{
		QMessageBox message;
		message.setText("This is the last map of the campaign.");
		message.exec();
	}
}

//Calls to reset the map, but will maintain the logic object to preserve the campaign info
void editscreen::resetMap()
{
	logicPersistence = true;
	choice = 3;
	editMap();
}

void editscreen::mapMenuClose()
{
	log->closeWindow();
	createCampaignMenus();
}

void editscreen::campaignMenuClose()
{
	createMainMenu();
}

void editscreen::newCampaign()
{
	campaignCreation = true;
	editMap();
}

void editscreen::loadCampaign()
{
	QString fileName = "";
	QString extension = "/Campaigns";
	fileName = QFileDialog::getOpenFileName(this, tr("Open Campaign"), QDir::currentPath().append(extension));
	if (fileName != "")
	{
		campaignfName = fileName.toStdString();
		choice = 2;
	}
	while (fileName == "")
	{
		fileName = QFileDialog::getOpenFileName(this, tr("Open Campaign"), QDir::currentPath().append(extension));
		campaignfName = fileName.toStdString();
		choice = 2;
	}

	editMap();
}

//This section is so that the user can see any size of map on screen (roughly) 100x100 max
int editscreen::checkResolution(int w, int h)
{
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

//These methods populate and manage the menus at the top of the screen for the user to navigate
void editscreen::createMainMenu()
{
	menuBar()->clear();
	menuBar()->addMenu(editMenu);
}

void editscreen::createEditorMenus()
{
	currentMenu = "mapeditor";
	menuBar()->clear();
	menuBar()->addMenu(mapMenu);
	menuBar()->addMenu(mapNavigatorMenu);
	
}

void editscreen::createCampaignMenus()
{
	currentMenu = "campaignmenu";
	menuBar()->clear();
	menuBar()->addMenu(campaignMenu);
}
