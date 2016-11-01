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
	void campaignMenuClose();
private:
	logic *log;
	int checkResolution(int w, int h);
	void createMainMenu();
	void createEditorMenus();

	string fName;
	string campaignfName;
	int choice = 0;

	bool campaignCreation = false;
	bool logicPersistence = false;
	bool openingMap = false;
	string currentMenu = "main";

	QMenu *editMenu;
	QMenu *mapMenu;
	QMenu *campaignMenu;
	QMenu *mapNavigatorMenu;

	QAction *campaignMenuAction;
	QAction *newCampaignAction;
	QAction *openCampaignAction;
	QAction *newMapAction;
	QAction *openMapAction;
	QAction *nextMapAction;
	QAction *previousMapAction;
	QAction *resetMapAction;
	QAction *mapMenuCloseAction;
	QAction *campaignMenuCloseAction;
};