/*
Team #8

Authors:
Nicholas Burdet
Nathan Lacasse
Shihao Ning
Alexi Grondin

Course: COMP 345

Final Project Delivery

Main cpp file

The main driver will invoke the QT application and creates a main window for the map widget to be displayed.

Details about features in the README file

QT Libraries are used in order to display the UI of the game and it's components
*/

//#include "testqt.h"
#include "editscreen.h"
#include <QtWidgets/QApplication>
#include <QInputDialog>
#include <ctime>

int main(int argc, char *argv[])
{
	srand(time(0));
	QApplication a(argc, argv);
	editscreen screen("Map Editor Screen");

	screen.show();
	a.exec();

	return 0;
}
