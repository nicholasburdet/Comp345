/*
Author: Nicholas Burdet
Id: 29613773
Course: COMP 345
Assignment 1 Part 2: Map

Main cpp file

The main driver will invoke the QT application (more info in readme) and creates a
main window for the map widget to be displayed.

The user will be prompted to create a new map (enter 0) or load the existing map (enter 1).
For the moment, only one file will be saved to memory for the purpose of this assignment.

The user can then enter a map of size 4x4 to 100x100.

User will then have an empty map with default squares and an entrance and exit. They can select
the tile they wish to use at the bottom of the screeen to populate the map. Only 1 entrance and
exit can exist (for now, can be scoped differently for main project).

A green or red button can be pressed to determine if a path from start to finish exists. Green
indicates that the path exists. Red indicates such path exists. The floppy disc icon represents
saving the current map to file. This will overwrite the current map on file.
*/

//#include "testqt.h"
#include "editscreen.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	editscreen screen("Map Editor Screen");
	screen.show();
	return a.exec();
}
