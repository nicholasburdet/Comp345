/*
Author: Nicholas Burdet
Id: 29613773
Course: COMP 345
Assignment 2 Part 3: Map

Main cpp file

The main driver will invoke the QT application (more info in readme) and creates a
main window for the map widget to be displayed.

The user can currently choose to enter the campaign editor menu, in which they can create a new
campaign, load an existing one, or load a map from file (which loads its corresponding campaign).
Once in the map editor menu, users can create new maps and add them onto the current campaign, load
another map (potentially from another campaign), navigate through the campaign maps or reset the contents
of the current map.

The user will then have an empty map with default squares and an entrance and exit. They can select
the tile they wish to use at the bottom of the screeen to populate the map. Only 1 entrance and
exit can exist (for now, can be scoped differently for main project).

NPCs can now be added to the map to add enemies that will be obstacles for the player character. NPCs
ability to occupy spaces functions identically to the way items will eventually, so this update does not include
items.

A green or red button can be pressed to determine if a path from start to finish exists. Green
indicates that the path exists. Red indicates such path exists. The floppy disc icon represents
saving the current map to file. This will overwrite the current map on file. The file will now ONLY save 
if the map is currently valid (start to end has a path).

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
