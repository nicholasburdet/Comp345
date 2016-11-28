/*
Author: Alexis Grondin
Id : 26639569
Course : COMP 345
Assignment 2 Part 2 : Character Observer

Character observer cpp file
*/



#include "characterObserver.h"
#include "character.h"
#include <QWidget>
#include <qapplication.h>
#include <qdesktopwidget.h>
#include <qtablewidget.h>
#include <qheaderview.h>
#include <QGraphicsScene>
#include <QMainWindow>
#include <string>
#include <QMessageBox>
#include <stdio.h>



characterObserver::characterObserver(QWidget* parent, character* sub):observer(), QMainWindow(parent)
{
	subject = sub;

	QStringList headers;
	headers << "Attribute" << "Value";


	cTable = new QTableWidget(13, 2, this);

	QString tableStyle = "QTableWidget {background-color: lightGrey;";
	tableStyle += "padding: 25%;";
	tableStyle += "width: 40%;";
	tableStyle += "border - color: black;";
	tableStyle += "border - style: outset;";
	tableStyle += "border - radius: 30px;";

	tableStyle += "}\n";

	tableStyle += "QHeaderView::section{background: grey;}\n";
	tableStyle += "QHeaderView{background: lightGrey;}\n";


	cTable->setStyleSheet(tableStyle);

	cTable->setHorizontalHeaderLabels(headers);

	cTable->verticalHeader()->setVisible(false);

	cTable->setGeometry(QApplication::desktop()->screenGeometry());
	setWindowTitle(tr("Character Data"));

	this->setFixedWidth(400);
	this->setFixedHeight(500);

	sub->addObserver(*this);

	initialize();

}


characterObserver::~characterObserver()
{
}


void characterObserver::notify() {
	if (cTable != NULL) {
		updateTable();
	}
}

void characterObserver::initialize()
{
	if (cTable != NULL) {
		cTable->setItem(0, 0, new QTableWidgetItem("Name"));
		cTable->setItem(0, 1, new QTableWidgetItem(subject->getName().c_str()));
		cTable->setItem(1, 0, new QTableWidgetItem("Class Name"));
		cTable->setItem(1, 1, new QTableWidgetItem(subject->getClassName().c_str()));
		cTable->setItem(2, 0, new QTableWidgetItem("Class Subtype"));
		cTable->setItem(2, 1, new QTableWidgetItem(subject->getSubtype().c_str()));
		cTable->setItem(3, 0, new QTableWidgetItem("Level"));
		cTable->setItem(3, 1, new QTableWidgetItem(std::to_string(subject->getLevel()).c_str()));
		cTable->setItem(4, 0, new QTableWidgetItem("HP"));
		cTable->setItem(4, 1, new QTableWidgetItem(std::to_string(subject->getHP()).c_str()));
		cTable->setItem(5, 0, new QTableWidgetItem("Strength"));
		cTable->setItem(5, 1, new QTableWidgetItem(std::to_string(subject->getAbilities().strength).c_str()));
		cTable->setItem(6, 0, new QTableWidgetItem("Intelligence"));
		cTable->setItem(6, 1, new QTableWidgetItem(std::to_string(subject->getAbilities().intelligence).c_str()));
		cTable->setItem(7, 0, new QTableWidgetItem("Wisdom"));
		cTable->setItem(7, 1, new QTableWidgetItem(std::to_string(subject->getAbilities().wisdom).c_str()));
		cTable->setItem(8, 0, new QTableWidgetItem("Dexterity"));
		cTable->setItem(8, 1, new QTableWidgetItem(std::to_string(subject->getAbilities().dexterity).c_str()));
		cTable->setItem(9, 0, new QTableWidgetItem("Constitution"));
		cTable->setItem(9, 1, new QTableWidgetItem(std::to_string(subject->getAbilities().constitution).c_str()));
		cTable->setItem(10, 0, new QTableWidgetItem("Charisma"));
		cTable->setItem(10, 1, new QTableWidgetItem(std::to_string(subject->getAbilities().charisma).c_str()));
		cTable->setItem(11, 0, new QTableWidgetItem("Damage Bonus"));
		cTable->setItem(11, 1, new QTableWidgetItem(std::to_string(subject->getDamageBonus()).c_str()));
		cTable->setItem(12, 0, new QTableWidgetItem("Attack Bonus"));
		cTable->setItem(12, 1, new QTableWidgetItem(subject->getAttackBonusLstString().c_str()));

		for (int i = 0; i < 12; i++) {
			cTable->item(i, 0)->setFlags(cTable->item(i, 0)->flags() ^ Qt::ItemIsEditable);
			cTable->item(i, 1)->setFlags(cTable->item(i, 1)->flags() ^ Qt::ItemIsEditable);
		}
	}
	
}

void characterObserver::updateTable() {
	cTable->item(0, 1)->setText(subject->getName().c_str());
	cTable->item(1, 1)->setText(subject->getClassName().c_str());
	cTable->item(2, 1)->setText(subject->getSubtype().c_str());
	cTable->item(3, 1)->setText(std::to_string(subject->getLevel()).c_str());
	cTable->item(4, 1)->setText(std::to_string(subject->getHP()).c_str());
	cTable->item(5, 1)->setText(std::to_string(subject->getAbilities().strength).c_str());
	cTable->item(6, 1)->setText(std::to_string(subject->getAbilities().intelligence).c_str());
	cTable->item(7, 1)->setText(std::to_string(subject->getAbilities().wisdom).c_str());
	cTable->item(8, 1)->setText(std::to_string(subject->getAbilities().dexterity).c_str());
	cTable->item(9, 1)->setText(std::to_string(subject->getAbilities().constitution).c_str());
	cTable->item(10, 1)->setText(std::to_string(subject->getAbilities().charisma).c_str());
	cTable->item(11, 1)->setText(std::to_string(subject->getDamageBonus()).c_str());
	cTable->item(12, 1)->setText(subject->getAttackBonusLstString().c_str());


	cTable->update();
	this->update();
	cTable->repaint();
	this->repaint();
}