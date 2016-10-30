#include "characterObserver.h"
#include "character.h"
#include <QWidget>
#include <QGraphicsScene>
#include <QMainWindow>
#include <string>
#include <QMessageBox>
#include <stdio.h>



characterObserver::characterObserver(character& sub):observer(),QTableWidget(12,2)
{
	subject = &sub;

	sub.addObserver(*this);

	initialize();

}


characterObserver::~characterObserver()
{
}


void characterObserver::notify() {
	initialize();
}

void characterObserver::initialize()
{
	setItem(0, 0, new QTableWidgetItem("Name"));
	setItem(0, 1, new QTableWidgetItem(subject->getName().c_str()));
	setItem(1, 0, new QTableWidgetItem("Class Name"));
	setItem(1, 1, new QTableWidgetItem(subject->getClassName().c_str()));
	setItem(2, 0, new QTableWidgetItem("Level"));
	setItem(2, 1, new QTableWidgetItem(std::to_string(subject->getLevel()).c_str()));
	setItem(3, 0, new QTableWidgetItem("HP"));
	setItem(3, 1, new QTableWidgetItem(std::to_string(subject->getHP()).c_str()));
	setItem(4, 0, new QTableWidgetItem("Strength"));
	setItem(4, 1, new QTableWidgetItem(std::to_string(subject->getAbilities().strength).c_str()));
	setItem(5, 0, new QTableWidgetItem("Intelligence"));
	setItem(5, 1, new QTableWidgetItem(std::to_string(subject->getAbilities().intelligence).c_str()));
	setItem(6, 0, new QTableWidgetItem("Wisdom"));
	setItem(6, 1, new QTableWidgetItem(std::to_string(subject->getAbilities().wisdom).c_str()));
	setItem(7, 0, new QTableWidgetItem("Dexterity"));
	setItem(7, 1, new QTableWidgetItem(std::to_string(subject->getAbilities().dexterity).c_str()));
	setItem(8, 0, new QTableWidgetItem("Constitution"));
	setItem(8, 1, new QTableWidgetItem(std::to_string(subject->getAbilities().constitution).c_str()));
	setItem(9, 0, new QTableWidgetItem("Charisma"));
	setItem(9, 1, new QTableWidgetItem(std::to_string(subject->getAbilities().charisma).c_str()));
	setItem(10, 0, new QTableWidgetItem("Damage Bonus"));
	setItem(10, 1, new QTableWidgetItem(std::to_string(subject->getDamageBonus()).c_str()));
	setItem(11, 0, new QTableWidgetItem("Attack Bonus"));
	setItem(11, 1, new QTableWidgetItem(std::to_string(subject->getAttackBonus()).c_str()));


}
