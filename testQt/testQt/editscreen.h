/*
Author: Nicholas Burdet
Id: 29613773
Course: COMP 345
Assignment 2 Part 3: Map

Editscreen header file
*/

#include <QWidget>
#include <QGraphicsScene>
#include <QMainWindow>
#include <string>
#include <QMessageBox>
#include "character.h"
#include "characterObserver.h"
#include "characterController.h"
#include <QPixmap>

using namespace std;

class logic;

class editscreen : public QMainWindow {
	Q_OBJECT
public:
	editscreen(char n[]);
public slots:
	void editMap();
	void openMap();
	void newMap();
	void nextMap();
	void previousMap();
	void resetMap();
	void mapMenuClose();
	void newCampaign();
	void loadCampaign();
	void createCampaignMenus();
	void menuClose();
	void createCharacterMenus();
	void characterEditorMenu();
	void characterEditorSave();
	void loadCharacter();
	void viewCharacterStats();
	void viewMap();

	////For Item && Character movement
	void newItem();
	void newGameMap();
	////
private:
	logic *log;
	character *newCharacter = new character();
	int checkResolution(int w, int h);
	void createMainMenu();
	void createEditorMenus();

	string fName;
	string campaignfName;
	int choice = 0;

	bool campaignCreation = false;
	bool logicPersistence = false;
	bool openingMap = false;
	bool viewingMap = false; //For simply viewing the map without edits
	string currentMenu = "main";

	QMenu *editMenu;
	QMenu *mapMenu;
	QMenu *campaignMenu;
	QMenu *mapNavigatorMenu;
	QMenu *characterMenu;
	QMenu *characterCreatorMenu;
	QMenu *gameMenu;

	QAction *campaignMenuAction;
	QAction *newCampaignAction;
	QAction *openCampaignAction;
	QAction *newMapAction;
	QAction *openMapAction;
	QAction *nextMapAction;
	QAction *previousMapAction;
	QAction *resetMapAction;
	QAction *mapMenuCloseAction;
	QAction *menuCloseAction;
	QAction *characterMenuAction;
	QAction *characterEditorMenuAction;
	QAction *characterLoadMenuAction;
	QAction *characterEditorSaveAction;
	QAction *viewCharacterStatsAction;
	QAction *viewMapAction;

	////Item Action && Character movement
	QAction *newItemAction;
	QAction *newMoveableMapAction;
	////
};
