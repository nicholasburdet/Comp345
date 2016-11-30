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
#include "itemContainer.h"

#include "logic.h"
#include <QDebug>
#include <QMouseEvent>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QtWidgets>
#include <QInputDialog>
#include <QObject>
#include <QComboBox>
#include "characterBuilder.h"
#include "TankConcreteBuilder.h"
#include "NimbleConcreteBuilder.h"
#include "BullyConcreteBuilder.h"
////Item Editor
#include <iostream>
#include <fstream>
using namespace std;
////

//Initialize all menus here upon class initialization
editscreen::editscreen(char n[])
{
	QPixmap backing("Images/background.jpg");
	backing = backing.scaled(this->size(), Qt::IgnoreAspectRatio);
	QPalette pal;
	pal.setBrush(QPalette::Background, backing);
	this->setPalette(pal);
	
	setFocusPolicy(Qt::NoFocus);
	
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

	characterMenuAction = new QAction(tr("&Character Menu"), this);
	connect(characterMenuAction, SIGNAL(triggered()), this, SLOT(createCharacterMenus()));

	characterCloseMenuAction = new QAction(tr("&Close Character Menu"), this);
	connect(characterCloseMenuAction, SIGNAL(triggered()), this, SLOT(characterMenuClose()));

	characterEditorMenuAction = new QAction(tr("&Create New Player Character"), this);
	connect(characterEditorMenuAction, SIGNAL(triggered()), this, SLOT(characterEditorMenu()));

	characterLoadMenuAction = new QAction(tr("&Load Player Character"), this);
	connect(characterLoadMenuAction, SIGNAL(triggered()), this, SLOT(loadCharacter()));

	characterEditorSaveAction = new QAction(tr("&Save Character"), this);
	connect(characterEditorSaveAction, SIGNAL(triggered()), this, SLOT(characterEditorSave()));

	viewCharacterStatsAction = new QAction(tr("&View Character Stats"), this);
	connect(viewCharacterStatsAction, SIGNAL(triggered()), this, SLOT(viewCharacterStats()));

	viewControlsActions = new QAction(tr("&View Controls"), this);
	connect(viewControlsActions, SIGNAL(triggered()), this, SLOT(viewControls()));

	viewItemsAction = new QAction(tr("&View Items"), this);
	connect(viewItemsAction, SIGNAL(triggered()), this, SLOT(viewItems()));

	quitGameAction = new QAction(tr("&Quit Game"), this);
	connect(quitGameAction, SIGNAL(triggered()), this, SLOT(quitGame()));

	viewEnemyStatsAction = new QAction(tr("&View Enemy Stats (CONSOLE)"), this);
	connect(viewEnemyStatsAction, SIGNAL(triggered()), this, SLOT(viewEnemyStats()));

	
	//// VIEW INVENTORY AND WORN ITEMS

	viewBackpackAction = new QAction(tr("&View Backpack"), this);
	connect(viewBackpackAction, SIGNAL(triggered()), this, SLOT(viewBackpack()));

	viewWornItemsAction = new QAction(tr("&View Worn Items"), this);
	connect(viewWornItemsAction, SIGNAL(triggered()), this, SLOT(viewWornItems()));

	/////
	
	////Item Editor && Character Movement
	newItemAction = new QAction(tr("&New Item"), this);
	connect(newItemAction, SIGNAL(triggered()), this, SLOT(newItem()));
	
	newMoveableMapAction = new QAction(tr("&Play Default Map"), this);
	connect(newMoveableMapAction, SIGNAL(triggered()), this, SLOT(newGameMap()));
	////
	viewMapAction = new QAction(tr("&Game Start"), this);
	connect(viewMapAction, SIGNAL(triggered()), this, SLOT(viewMap()));

	menuCloseAction = new QAction(tr("&Close Menu"), this);
	connect(menuCloseAction, SIGNAL(triggered()), this, SLOT(menuClose()));

	editMenu = new QMenu(tr("&Main Menu"), this);
	editMenu->addAction(campaignMenuAction);
	

	
	//// Item Generator && Character Movement
	editMenu->addAction(newItemAction);
	editMenu->addAction(newMoveableMapAction);
	////
	
	editMenu->addAction(characterMenuAction);
	editMenu->addAction(viewMapAction);

	mapMenu = new QMenu(tr("&Map File"), this);
	mapMenu->addAction(newMapAction);
	mapMenu->addAction(openMapAction);
	mapMenu->addAction(resetMapAction);
	mapMenu->addAction(mapMenuCloseAction);
	mapMenu->addAction(viewItemsAction);
	
	mapNavigatorMenu = new QMenu(tr("&Navigate Maps"), this);
	mapNavigatorMenu->addAction(nextMapAction);
	mapNavigatorMenu->addAction(previousMapAction);

	campaignMenu = new QMenu(tr("&Campaign Options"), this);
	campaignMenu->addAction(newCampaignAction);
	campaignMenu->addAction(openCampaignAction);
	campaignMenu->addAction(openMapAction);
	campaignMenu->addAction(menuCloseAction);

	characterMenu = new QMenu(tr("&Character"), this);
	characterMenu->addAction(characterEditorMenuAction);
	characterMenu->addAction(characterLoadMenuAction);
	characterMenu->addAction(characterCloseMenuAction);

	characterCreatorMenu = new QMenu(tr("&Character"), this);
	characterCreatorMenu->addAction(characterEditorMenuAction);
	characterCreatorMenu->addAction(characterEditorSaveAction);
	characterCreatorMenu->addAction(characterCloseMenuAction);

	gameMenu = new QMenu(tr("&Game Menu"), this);
	gameMenu->addAction(viewCharacterStatsAction);
	
	////Add backpack and worn items to menu
	gameMenu->addAction(viewBackpackAction);
	gameMenu->addAction(viewWornItemsAction);
	////
	gameMenu->addAction(viewEnemyStatsAction);
	gameMenu->addAction(quitGameAction);

	viewControlsMenu = new QMenu(tr("View Controls"), this);
	viewControlsMenu->addAction(viewControlsActions);

	editMenu->setFocusPolicy(Qt::NoFocus);
	mapMenu->setFocusPolicy(Qt::NoFocus);
	campaignMenu->setFocusPolicy(Qt::NoFocus);
	mapNavigatorMenu->setFocusPolicy(Qt::NoFocus);
	characterMenu->setFocusPolicy(Qt::NoFocus);
	characterCreatorMenu->setFocusPolicy(Qt::NoFocus);
	gameMenu->setFocusPolicy(Qt::NoFocus);

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
	
	log->setEditmode(true);
	
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
	this->setFixedHeight((height*resolution) + (resolution * 4) + addedHeight);
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


//// Creating a new Item
void editscreen::newItem() 
{

	bool ok1;

	
	int armorClass = 1;
	int enchantmentBonus = 0;
	QString enchantmentType;
	QString armorGrade;
	QStringList enchants;
	QStringList items;
	QStringList armorList;
	armorList << tr("Light") << tr("Medium") << tr("Heavy");

	ifstream file("Resources/items.txt");
	string str;
	string str2;
	string file_contents;
	string symbol = "|";
	while (getline(file, str))
	{
		size_t found = str.find(symbol);
		str2 = str.substr(0, found);
	};

	int temp = atoi(str2.c_str());
	temp = temp + 1;




	
	items << tr("Helmet") << tr("Armor") << tr("Shield") << tr("Ring") << tr("Belt") << tr("Boots") << tr("Weapon");

	QString itemType = QInputDialog::getItem(this, tr("QInputDialog::getItem()"),tr("Select Item Type:"), items, 0, false, &ok1);


	//Currently has to be typed out -- at a later date it'll be a combo box to prevent errors and to improve the ux
	//QString itemType = QInputDialog::getText(this, tr("Item Type"), tr("Enter Item Type: Helmet, Armor, Shield, Ring, Belt, Boots, Weapon"), QLineEdit::Normal, "", &ok1);
	
	
	QString itemName = QInputDialog::getText(this, tr("Item Name"), tr("Give your item a Name!"), QLineEdit::Normal, "", &ok1);
	

	
		//Make Id base on line number in file
		string customItemsFile = "Resources/items.txt";
	
	
		if (ok1) {

			if (itemType == "Helmet") {

				//enchantmentType
				
				enchants << tr("None") << tr("Intelligence") << tr("Wisdom") << tr("Constitution") << tr("Armor Class");
				enchantmentType = QInputDialog::getItem(this, tr("QInputDialog::getItem()"), tr("Select Enchantment:"), enchants, 0, false, &ok1);



				//enchantmentBonus if applicable	
				if (enchantmentType != "") {
					enchantmentBonus = QInputDialog::getInt(this, "Enchantment Bonus", tr("Enter the enchantment bonus. Range: 1 - 5"), 1, 1, 5, 1, &ok1);
				}
				else {
					enchantmentBonus = 0;
				}


				armorGrade = QInputDialog::getItem(this, tr("QInputDialog::getItem()"), tr("Select armor grade:"), armorList, 0, false, &ok1);

			}
			else if (itemType == "Armor" || itemType == "Shield") {
				//armor and shield have the same potential bonuses


				//enchantmentType
			
				enchants << tr("None") << tr("Armor Class");
				enchantmentType = QInputDialog::getItem(this, tr("QInputDialog::getItem()"), tr("Select Item enchantment:"), enchants, 0, false, &ok1);

				//enchantmentBonus if applicable	
				if (enchantmentType != "") {
					enchantmentBonus = QInputDialog::getInt(this, "Enchantment Bonus", tr("Enter the enchantment bonus. Range: 1 - 5"), 1, 1, 5, 1, &ok1);
				}
				else {
					enchantmentBonus = 0;
				}
				armorGrade = QInputDialog::getItem(this, tr("QInputDialog::getItem()"), tr("Select armor grade:"), armorList, 0, false, &ok1);

			}
			else if (itemType == "Ring") {

				//enchantmentType
				enchants << tr("None") << tr("Armor Class") << tr("Strength") << tr("Constitution") << tr("Wisdom") << tr("Charisma");
				enchantmentType = QInputDialog::getItem(this, tr("QInputDialog::getItem()"), tr("Select Item enchantment:"), enchants, 0, false, &ok1);


	
				//enchantmentBonus if applicable	
				if (enchantmentType != "None") {
					enchantmentBonus = QInputDialog::getInt(this, "Enchantment Bonus", tr("Enter the enchantment bonus. Range: 1 - 5"), 1, 1, 5, 1, &ok1);
				}
				else {
					enchantmentBonus = 0;
				}

				armorGrade = QInputDialog::getItem(this, tr("QInputDialog::getItem()"), tr("Select armor grade:"), armorList, 0, false, &ok1);


			}
			else if (itemType == "Belt") {


				//enchantmentType
				enchants << tr("None")  << tr("Armor Class") << tr("Strength") << tr("Constitution") << tr("Wisdom") << tr("Charisma");
				enchantmentType = QInputDialog::getItem(this, tr("QInputDialog::getItem()"), tr("Select Enchantment:"), enchants, 0, false, &ok1);


				//enchantmentBonus if applicable	
				if (enchantmentType != "None") {
					enchantmentBonus = QInputDialog::getInt(this, "Enchantment Bonus", tr("Enter the enchantment bonus. Range: 1 - 5"), 1, 1, 5, 1, &ok1);
				}
				else {
					enchantmentBonus = 0;
				}

				armorGrade = QInputDialog::getItem(this, tr("QInputDialog::getItem()"), tr("Select armor grade:"), armorList, 0, false, &ok1);

			}
			else if (itemType == "Boots") {

				//enchantmentType

				enchants << tr("None") << tr("Armor Class") << tr("Dexteriy");
				enchantmentType = QInputDialog::getItem(this, tr("QInputDialog::getItem()"), tr("Select Enchantment:"), enchants, 0, false, &ok1);

				
				//enchantmentBonus if applicable	
				if (enchantmentType != "None") {
					enchantmentBonus = QInputDialog::getInt(this, "Enchantment Bonus", tr("Enter the enchantment bonus. Range: 1 - 5"), 1, 1, 5, 1, &ok1);
				}
				else {
					enchantmentBonus = 0;
				}

				armorGrade = QInputDialog::getItem(this, tr("QInputDialog::getItem()"), tr("Select armor grade:"), armorList, 0, false, &ok1);

			}
			else if (itemType == "Weapon") {

				//enchantmentType

				enchants << tr("None") << tr("Attack Bonus") << tr("Damage Bonus");
				enchantmentType = QInputDialog::getItem(this, tr("QInputDialog::getItem()"), tr("Select Enchantment:"), enchants, 0, false, &ok1);


				//enchantmentBonus if applicable	
				if (enchantmentType != "None") {
					enchantmentBonus = QInputDialog::getInt(this, "Enchantment Bonus", tr("Enter the enchantment bonus. Range: 1 - 5"), 1, 1, 5, 1, &ok1);
				}
				else {
					enchantmentBonus = 0;
				}

				armorGrade = QInputDialog::getText(this, tr("Dice"), tr("Enter the dice Damage. #d#, example: 1d4"), QLineEdit::Normal, "", &ok1);

			}

			//// Write to file
			//Convert QString to string
			std::string itemTypeString = itemType.toLocal8Bit().constData();
			std::string itemNameString = itemName.toLocal8Bit().constData();
			std::string enchantmentTypeString = enchantmentType.toLocal8Bit().constData();
			std::string ig = armorGrade.toLocal8Bit().constData();



			////Format of items:
			//ID | Type | Name | Enchantment | Bonus | DICE/ARMOR GRADE
			ofstream customItems;
			customItems.open(customItemsFile.c_str(), ios::out | ios::app);


			//itemGrade is not written to file
			customItems << temp << "|" << itemTypeString << "|" << itemNameString << "|" << enchantmentTypeString << "|" << enchantmentBonus << "|" << ig << "\n";
			customItems.close();
			////

		}
}
////

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

void editscreen::characterMenuClose()
{
	setCentralWidget(NULL);
	setWindowTitle(tr("Dungeon and Dragons"));

	createMainMenu();
}

void editscreen::mapMenuClose()
{
	log->closeWindow();
	this->setFixedWidth(400);
	this->setFixedHeight(200);
	createCampaignMenus();
}

void editscreen::menuClose()
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

void editscreen::quitGame()
{
	QDialog * d = new QDialog();
	d->setWindowTitle("Are you sure you want to quit?");

	QDialogButtonBox * buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
		| QDialogButtonBox::Cancel);

	QObject::connect(buttonBox, SIGNAL(accepted()), d, SLOT(accept()));
	QObject::connect(buttonBox, SIGNAL(rejected()), d, SLOT(reject()));

	buttonBox->button(QDialogButtonBox::Ok)->setText("Quit");
	buttonBox->button(QDialogButtonBox::Cancel)->setText("Cancel");

	QVBoxLayout * vbox = new QVBoxLayout();

	vbox->addWidget(buttonBox);
	d->setLayout(vbox);

	int result = d->exec();
	if (result == QDialog::Accepted)
	{
		log->closeWindow();
		createMainMenu();
	}
}

void editscreen::viewEnemyStats()
{
	log->viewEnemyStats();
}

//This section is so that the user can see any size of map on screen (roughly) 100x100 max
int editscreen::checkResolution(int w, int h)
{
	if (h > 80)
	{
		return 8;
	}
	if (h > 70)
	{
		return 10;
	}
	if (h > 50)
	{
		return 12;
	}
	if (w > 80 || h > 35)
	{
		return 15;
	}
	if (w > 70 || h > 30)
	{
		return 20;
	}
	if (w > 60 || h > 25)
	{
		return 25;
	}
	if (w > 50 || h > 20)
	{
		return 30;
	}
	if (w > 40 || h > 15)
	{
		return 35;
	}
	if (w > 30 || h > 12)
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
	this->setFixedWidth(400);
	this->setFixedHeight(200);

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

void editscreen::createCharacterMenus()
{
	currentMenu = "charactermenu";
	menuBar()->clear();
	menuBar()->addMenu(characterMenu);
}

void editscreen::characterEditorMenu()
{
	currentMenu = "charactereditormenu";
	menuBar()->clear();
	menuBar()->addMenu(characterCreatorMenu);

	string charName;
	int charLevel;

	QDialog characterCreatorDialog(this);
	QFormLayout characterForm(&characterCreatorDialog);

	characterForm.addRow(new QLabel("Character Creation Window"));

	QList<QLineEdit *> characterFields;

	QLineEdit *lineEdit = new QLineEdit(&characterCreatorDialog);
	QString label = QString("Name");
	characterForm.addRow(label, lineEdit);
	characterFields << lineEdit;
	
	lineEdit = new QLineEdit(&characterCreatorDialog);
	label = QString("Level");
	characterForm.addRow(label, lineEdit);
	characterFields << lineEdit;

	QComboBox *characterType = new QComboBox(&characterCreatorDialog);
	QString typeLabel = QString("Fighter Type");
	characterType->addItem(QString("Tank"), QVariant(0));
	characterType->addItem(QString("Nimble"), QVariant(1));
	characterType->addItem(QString("Bully"), QVariant(2));
	characterForm.addRow(typeLabel, characterType);

	QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &characterCreatorDialog);
	characterForm.addRow(&buttonBox);
	QObject::connect(&buttonBox, SIGNAL(accepted()), &characterCreatorDialog, SLOT(accept()));
	QObject::connect(&buttonBox, SIGNAL(rejected()), &characterCreatorDialog, SLOT(reject()));


	if (characterCreatorDialog.exec() == QDialog::Accepted) {

		characterBuilder* builder;

		//TODO: Proper string comparison
		if (characterType->currentData().toInt()==1) {
			builder = new NimbleConcreteBuilder();
		}else if (characterType->currentData().toInt() == 0) {
			builder = new TankConcreteBuilder();
		}else {
			builder = new BullyConcreteBuilder();//Default value for now
		}

		charName = characterFields.value(0)->text().toStdString();
		charLevel = characterFields.value(1)->text().toInt();
	
		builder->buildName(charName);
		builder->buildLevel(charLevel);
		builder->buildHP(builder->getCharacter()->getMaxHP());
		builder->buildPlayerCharacter(true);
		builder->setSubtype();

		builder->generateAbilities();

		newCharacter = builder->getCharacter();

		characterObserver* charTable = new characterObserver(NULL, newCharacter);
		characterController* driver = new characterController(newCharacter);

		setCentralWidget(charTable);
		setWindowTitle(tr("Character"));

		this->setFixedWidth(400);
		this->setFixedHeight(500);
	}
}

void editscreen::loadCharacter() 
{
	currentMenu = "charactereditormenu";
	menuBar()->clear();
	menuBar()->addMenu(characterCreatorMenu);

	string charName;
	int charLevel;

	QDialog characterLoadDialog(this);
	QFormLayout characterLoadForm(&characterLoadDialog);

	characterLoadForm.addRow(new QLabel("Character Loading Window"));

	QString fileName = "";
	string characterFileName;
	QString extension = "/PlayerCharacters";
	fileName = QFileDialog::getOpenFileName(this, tr("View Character"), QDir::currentPath().append(extension));
	if (fileName != "")
	{
		characterFileName = fileName.toStdString();
	}
	while (fileName == "")
	{
		fileName = QFileDialog::getOpenFileName(this, tr("View Character"), QDir::currentPath().append(extension));
		characterFileName = fileName.toStdString();
	}

	newCharacter = new character();
	newCharacter->loadFromFile(characterFileName);

	newCharacter->setPlayerCharacter(true);

	characterObserver* charTable = new characterObserver(NULL, newCharacter);
	characterController* driver = new characterController(newCharacter);

	setCentralWidget(charTable);
	setWindowTitle(tr("Character"));
	this->setFixedWidth(400);
	this->setFixedHeight(500);
	
}

void editscreen::characterEditorSave()
{
	newCharacter->saveToFile();
	QMessageBox message;
	message.setText("Character saved successfully!");
	message.exec();
}

//// Character Movement
void editscreen::newGameMap()
{
	//Initilize QT Application and images
	QImage image("Resources/grass.png");
	QPixmap playerImage("Resources/player.png");

	//Create and adds bg to screen
	QGraphicsPixmapItem* bg = new QGraphicsPixmapItem(QPixmap::fromImage(image));
	QGraphicsScene* scene = new QGraphicsScene;
	scene->addItem(bg);

	//Create and adds player to screen
	characterMovement * player = new characterMovement();
	player->setPixmap(playerImage);
	scene->addItem(player);
	player->setFlag(QGraphicsItem::ItemIsFocusable);
	player->setFocus();

	//Creates and adds scene
	QGraphicsView view(scene);
	view.show();

	QEventLoop loop;
	connect(this, SIGNAL(destroyed()), &loop, SLOT(quit()));
	loop.exec();
}

//**********************************************
//
// GAME START IS HERE IN VIEW MAP
//
//**********************************************
void editscreen::viewMap()
{
	//Main implementation of game start code
	bool ok1;
	int width, height;
	int resolution = 50;
	int addedHeight = 20;

	log = new logic(0, this);
	log->setEditmode(false);

	QString fileName = "";
	QString extension = "/Campaigns";
	//Asks user which campaign to load
	fileName = QFileDialog::getOpenFileName(this, tr("Open Campaign"), QDir::currentPath().append(extension));
	if (fileName != "")
	{
		fName = fileName.toStdString();
	}
	while (fileName == "")
	{
		fileName = QFileDialog::getOpenFileName(this, tr("Open Campaign"), QDir::currentPath().append(extension));
		fName = fileName.toStdString();
	}

	log->loadCampaign(fName);
	width = log->getWidth();
	height = log->getHeight();

	extension = "/PlayerCharacters";
	//Asks user which character to load
	fileName = "";
	fileName = QFileDialog::getOpenFileName(this, tr("Choose Character"), QDir::currentPath().append(extension));
	if (fileName != "")
	{
		fName = fileName.toStdString();
	}
	while (fileName == "")
	{
		fileName = QFileDialog::getOpenFileName(this, tr("Choose Character"), QDir::currentPath().append(extension));
		fName = fileName.toStdString();
	}

	//Load Character goes here
	log->loadPlayerCharacter(fName);

	resolution = checkResolution(width, height);
	log->setResolution(resolution);

	setCentralWidget(log);
	setWindowTitle(tr("Map Editor"));
	int windowResX = width*resolution;
	
	int windowDisplayHeightAdd = 3 * 50;
	int windowDisplayWidthMinimum = 12 * resolution;

	if (windowResX < windowDisplayWidthMinimum)
	{
		windowResX = windowDisplayWidthMinimum;
	}


	//Menu for the game appears
	currentMenu = "gamemenu";
	menuBar()->clear();
	menuBar()->addMenu(gameMenu);
	menuBar()->addMenu(viewControlsMenu);

	this->setFixedWidth(windowResX);
	this->setFixedHeight((height*resolution) + addedHeight + windowDisplayHeightAdd);
	log->setFocus();
}

void editscreen::viewControls()
{
	messageBox.setText("Use the arrow keys to move during your turn.\n-Can move up to player's movement speed-\n\nPress (N) to advance game when NPC(s) turn.\nDuring Player turn:\n(S) Stops player movement if any move is available.\n(E) Immediately Ends player turn.\n(A) Attack an enemy. (Functionality not fully implemented)\n(L) Loot an adjacent item or chest (Functionality not fully implemented)\n\nCan only do a full attack if the player has not moved.\n\nOnce attack (A) has been selected, pick a direction (arrows) to attack.\nRanged attacks need to be in line with target to attack.");
	messageBox.exec();
}

void editscreen::viewItems()
{
	log->viewItems();
}

void editscreen::viewCharacterStats()
{
	//Add code to view player stats here
	log->viewPlayer();
}


void editscreen::viewBackpack()
{
	//Add Interface to view backpack
	
	QDialog * d = new QDialog();
	d->setWindowTitle("Backpack");
	QLabel *spaceLabel = new QLabel("");

	QVBoxLayout * vbox = new QVBoxLayout();


	QFile myTextFile("Resources/backpack.txt");
	QStringList myStringList;

	if (!myTextFile.open(QIODevice::ReadOnly))
	{
		QMessageBox::information(0, "Error opening file", myTextFile.errorString());
	}
	else
	{
		while (!myTextFile.atEnd())
		{
			myStringList.append(myTextFile.readLine());
		}

		myTextFile.close();
	}


	QListWidget * backpack = new QListWidget();

	backpack->addItems(myStringList);

	QDialogButtonBox * buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);
	buttonBox->button(QDialogButtonBox::Ok)->setText("Back");

	QObject::connect(buttonBox, SIGNAL(accepted()), d, SLOT(accept()));

	backpack->setMinimumWidth(400);
	backpack->setMinimumHeight(400);
	vbox->addWidget(backpack);

	vbox->addWidget(spaceLabel);
	vbox->addWidget(buttonBox);

	d->setLayout(vbox);

	int result = d->exec();
	if (result == QDialog::Accepted)
	{
		//Return to Game
	}
}

void editscreen::viewWornItems()
{
	//Add Interface to view worn Items
	QDialog * d = new QDialog();
	d->setWindowTitle("Worn Items");
	QLabel *spaceLabel = new QLabel("");

	QVBoxLayout * vbox = new QVBoxLayout();


	QFile myTextFile("Resources/backpack.txt");
	QStringList myStringList;

	QStringList helmetList;
	QStringList armorList;
	QStringList shieldList;
	QStringList ringList;
	QStringList beltList;
	QStringList bootsList;
	QStringList weaponList;


	if (!myTextFile.open(QIODevice::ReadOnly))
	{
		QMessageBox::information(0, "Error opening file", myTextFile.errorString());
	}
	else
	{

		while (!myTextFile.atEnd())
		{
			QString tempLine = myTextFile.readLine();

			myStringList.append(tempLine);

			//myTextFile.readLine().find("|");


			//QString s_data = QString::fromAscii(myTextFile.readLine());

			//QString(myTextFile.readLine());

			string newLine = QString(tempLine).toUtf8().constData();


			//QInputDialog::getText(this, newLine, myTextFile.readLine(), QLineEdit::Normal, "", &ok1);
			

			std::size_t found = newLine.find("|");
			newLine = newLine.substr(found + 1, newLine.length());
			found = newLine.find("|");
			newLine = newLine.substr(0, found);


			bool ok1;

			
			
			if (string(newLine) == "Helmet")
				helmetList.append(tempLine);

			if (string(newLine) == "Armor")
				armorList.append(tempLine);

			if (string(newLine) == "Shield")
				shieldList.append(tempLine);

			if (string(newLine) == "Ring")
				ringList.append(tempLine);

			if (string(newLine) == "Belt")
				beltList.append(tempLine);

			if (string(newLine) == "Boots")
				bootsList.append(tempLine);

			if (string(newLine) == "Weapon")
				weaponList.append(tempLine);

		}

		myTextFile.close();
	}

	
	QLabel *helmetLabel = new QLabel("Helmet");
	QComboBox * comboBoxHelmet = new QComboBox();
	comboBoxHelmet->addItems(helmetList);


	QLabel *armorLabel = new QLabel("Armor");
	QComboBox * comboBoxArmor = new QComboBox();
	comboBoxArmor->addItems(armorList);

	QLabel *shieldLabel = new QLabel("Shield");
	QComboBox * comboBoxShield = new QComboBox();
	comboBoxShield->addItems(shieldList);

	QLabel *ringLabel = new QLabel("Ring");
	QComboBox * comboBoxRing = new QComboBox();
	comboBoxRing->addItems(ringList);

	QLabel *beltLabel = new QLabel("Belt");
	QComboBox * comboBoxBelt = new QComboBox();
	comboBoxBelt->addItems(beltList);


	QLabel *bootsLabel = new QLabel("Boots");
	QComboBox * comboBoxBoots = new QComboBox();
	comboBoxBoots->addItems(bootsList);

	QLabel *weaponLabel = new QLabel("Weapon");
	QComboBox * comboBoxWeapon = new QComboBox();
	comboBoxWeapon->addItems(weaponList);


	QDialogButtonBox * buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
		| QDialogButtonBox::Cancel);

	QObject::connect(buttonBox, SIGNAL(accepted()), d, SLOT(accept()));
	QObject::connect(buttonBox, SIGNAL(rejected()), d, SLOT(reject()));

	buttonBox->button(QDialogButtonBox::Ok)->setText("Equip");
	buttonBox->button(QDialogButtonBox::Cancel)->setText("Back");

	comboBoxHelmet->setMinimumHeight(30);
	comboBoxArmor->setMinimumHeight(30);
	comboBoxShield->setMinimumHeight(30);
	comboBoxRing->setMinimumHeight(30);
	comboBoxBelt->setMinimumHeight(30);
	comboBoxBoots->setMinimumHeight(30);
	comboBoxWeapon->setMinimumHeight(30);

	vbox->addWidget(helmetLabel);
	vbox->addWidget(comboBoxHelmet);

	vbox->addWidget(armorLabel);
	vbox->addWidget(comboBoxArmor);

	
	vbox->addWidget(shieldLabel);
	vbox->addWidget(comboBoxShield);

	vbox->addWidget(ringLabel);
	vbox->addWidget(comboBoxRing);

	
	vbox->addWidget(beltLabel);
	vbox->addWidget(comboBoxBelt);

	vbox->addWidget(bootsLabel);
	vbox->addWidget(comboBoxBoots);

	vbox->addWidget(weaponLabel);
	vbox->addWidget(comboBoxWeapon);

	vbox->addWidget(spaceLabel);
	vbox->addWidget(buttonBox);

	d->setLayout(vbox);

	int result = d->exec();
	if (result == QDialog::Accepted)
	{

		itemContainer ic;

		std::string lineHelmet = comboBoxHelmet->currentText().toUtf8().constData();
		size_t found = lineHelmet.find("|");
		lineHelmet = lineHelmet.substr(0, found);

		std::string lineArmor = comboBoxArmor->currentText().toUtf8().constData();
		found = lineArmor.find("|");
		lineArmor = lineArmor.substr(0, found);

		std::string lineShield = comboBoxShield->currentText().toUtf8().constData();
		found = lineShield.find("|");
		lineShield = lineShield.substr(0, found);

		std::string lineRing = comboBoxRing->currentText().toUtf8().constData();
		found = lineRing.find("|");
		lineRing = lineRing.substr(0, found);

		std::string lineBelt = comboBoxBelt->currentText().toUtf8().constData();
		found = lineBelt.find("|");
		lineBelt = lineBelt.substr(0, found);

		std::string lineBoots = comboBoxBoots->currentText().toUtf8().constData();
		found = lineBoots.find("|");
		lineBoots = lineBoots.substr(0, found);

		std::string lineWeapon = comboBoxWeapon->currentText().toUtf8().constData();
		found = lineWeapon.find("|");
		lineWeapon = lineWeapon.substr(0, found);


		ic.addItemWorn(stoi(lineHelmet));
		ic.addItemWorn(stoi(lineArmor));
		ic.addItemWorn(stoi(lineShield));
		ic.addItemWorn(stoi(lineRing));
		ic.addItemWorn(stoi(lineBelt));
		ic.addItemWorn(stoi(lineBoots));
		ic.addItemWorn(stoi(lineWeapon));


		QDialog * d = new QDialog();
		d->setWindowTitle("Equipped Items");
		QLabel *titleLabel = new QLabel("Currently Equipped Items");
		QLabel *spaceLabel = new QLabel("");

		QVBoxLayout * vbox = new QVBoxLayout();

		QFile myTextFile("Resources/wornItems.txt");
		QStringList myStringList;

		if (!myTextFile.open(QIODevice::ReadOnly))
		{
			QMessageBox::information(0, "Error opening file", myTextFile.errorString());
		}
		else
		{
			while (!myTextFile.atEnd())
			{
				myStringList.append(myTextFile.readLine());
			}

			myTextFile.close();
		}


		QListWidget * backpack = new QListWidget();

		backpack->addItems(myStringList);

		QDialogButtonBox * buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);
		buttonBox->button(QDialogButtonBox::Ok)->setText("Back");

		QObject::connect(buttonBox, SIGNAL(accepted()), d, SLOT(accept()));

		
		backpack->setMinimumHeight(350);
		vbox->addWidget(titleLabel);
		vbox->addWidget(backpack);

		vbox->addWidget(spaceLabel);
		vbox->addWidget(buttonBox);

		d->setLayout(vbox);

		int result = d->exec();
		if (result == QDialog::Accepted)
		{
			//Return to Game
			log->loadEquipment(); //Will make equipment changes for the player immediately
		}

	}
	
}
