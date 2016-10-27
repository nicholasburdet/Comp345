/*
Author: Nicholas Burdet
Id: 29613773
Course: COMP 345
Assignment 1 Part 2: Map

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
	bool getWindowOpen();
public slots:
	void editMap();
private:
	logic *log;
	int checkResolution(int w, int h);
	void createMenus();

	QMenu *editMenu;
	QAction *editMapAction;

protected:
	void closeEvent(QCloseEvent *event);

};