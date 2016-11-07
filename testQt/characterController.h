#pragma once

#include "character.h"
#include <qobject.h>
#include <QWidget>
#include <QGraphicsScene>
#include <QMainWindow>
#include <string>
#include <QMessageBox>
#include <qtablewidget.h>

/*!
	This class allows modification of the character class, so as to demonstrate the behavior of the characterObserver class.

*/

class characterController: public QObject
{
	Q_OBJECT
public:
	characterController(character* mod);
	~characterController();


	public slots:

	/*!
		Sets the character name to a predefined value
	*/
	void setCharacterName();

	/*!
		Increases the character level
	*/
	void levelUpCharacter();

	
	

private:
	character* toModify;

};

