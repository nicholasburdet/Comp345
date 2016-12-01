/*
Team #8

Authors:
Nicholas Burdet
Nathan Lacasse
Shihao Ning
Alexi Grondin

Course: COMP 345

Final Project Delivery

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
	void characterMenuClose();
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
	void viewEnemyStats();
	void viewMap();
	void viewControls();
	void viewItems();
	void quitGame();

	void viewBackpack();
	void viewWornItems();

	////For Item && Character movement
	void newItem();
	void newGameMap();
	////
	void combatLogToggle();
	void movementLogToggle();
	void miscLogToggle();

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

	QMessageBox messageBox;

	QMenu *editMenu;
	QMenu *mapMenu;
	QMenu *campaignMenu;
	QMenu *mapNavigatorMenu;
	QMenu *characterMenu;
	QMenu *characterCreatorMenu;
	QMenu *gameMenu;
	QMenu *viewControlsMenu;
	QMenu *toggleLogView;

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
	QAction *characterCloseMenuAction;
	QAction *characterEditorMenuAction;
	QAction *characterLoadMenuAction;
	QAction *characterEditorSaveAction;
	QAction *viewCharacterStatsAction;
	QAction *viewMapAction;
	QAction *viewControlsActions;
	QAction *viewItemsAction;
	QAction *quitGameAction;
	QAction *viewEnemyStatsAction;
	
	QAction *viewBackpackAction;
	QAction *viewWornItemsAction;

	QAction *combatLogToggleAction;
	QAction *movementLogToggleAction;
	QAction *miscLogToggleAction;

	////Item Action && Character movement
	QAction *newItemAction;
	QAction *newMoveableMapAction;
	////
};
