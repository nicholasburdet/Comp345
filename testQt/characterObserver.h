
#pragma once
#include "observer.h"
#include "character.h"
#include <QWidget>
#include <QGraphicsScene>
#include <QMainWindow>
#include <string>
#include <QMessageBox>
#include <qtablewidget.h>

/*!
Character observer class, implementing the observer pattern. It also inherits the QMainWindow class of the QT framework.
This class generates a QT table widget, where the character's stats are displayed. In the final application, this will be used by the player
to monitor his character's or the npc's stats.

The QT framework was chosen because of its simplicity and good documentation

*/


class characterObserver:public observer, public QMainWindow
{
public:
	characterObserver(QWidget* parent, character* sub);
	~characterObserver();


	/*!
		Notifies the observer of a state change in the subject, prompting it to update its display
	*/
	void notify();

	/*!
		Initializes the table displaying the character's stats
	*/
	void initialize();

	/*!
		Updates the table with the new character's stats
	*/
	void updateTable();


private:
	QTableWidget* cTable;
	character* subject;

};

