#pragma once


#include <QWidget>
#include <qapplication.h>
#include <qdesktopwidget.h>
#include <qtablewidget.h>
#include <qheaderview.h>
#include <QGraphicsScene>
#include <QMainWindow>
#include <string>
#include <QMessageBox>
#include <qtablewidget.h>
#include <stdio.h>
#include "character.h"
#include "observer.h"

class characterMenu:public observer, public QMainWindow
{
Q_OBJECT

public:
	characterMenu(QWidget* parent, character* sub);
	~characterMenu();

	void setTable();

	void populateTable();

	void onItemChanged(QTableWidgetItem* item);

private:

	QTableWidget* cTable;
	character* subject;
	string attrList[] = { "Name", "id", "level", "image", "HP", "Class", "Strenght", "Intelligence", "Wisdom", "Constitution", "Charisma", "Dexterity" };

};

