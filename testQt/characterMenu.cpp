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
#include "characterMenu.h"
#include "character.h"
#include "observer.h"

using namespace std;

characterMenu::characterMenu(QWidget* parent, character* sub) : observer(), QMainWindow(parent)
{
	subject = sub;

	QStringList headers;
	headers << "Attribute" << "Value";


	cTable = new QTableWidget(12, 2, this);

	cTable->setHorizontalHeaderLabels(headers);

	cTable->verticalHeader()->setVisible(false);

	cTable->setGeometry(QApplication::desktop()->screenGeometry());
	setWindowTitle(tr("Character Data"));

	this->setFixedWidth(400);
	this->setFixedHeight(500);

	setTable();

	if (sub != NULL) {
		populateTable();
	}


}


characterMenu::~characterMenu()
{
}

void characterMenu::setTable()
{

	for (int i = 0; i < sizeof(attrList); i++) {
		cTable->setItem(i, 0, new QTableWidgetItem(attrList[i]));
		cTable->item(i, 0)->setFlags(cTable->item(i, 0)->flags() ^ Qt::ItemIsEditable);
		cTable->setItem(i, 1, new QTableWidgetItem(""));

	}

	QObject::connect(cTable, QTableWidget::itemChanged, onItemChanged);
}

void characterMenu::populateTable()
{
	for (int i = 0; i < sizeof(attrList); i++) {
		
		cTable->setItem(i, 1, new QTableWidgetItem(subject->getAttribute(attrList[i]).c_str()));
	}
}

void characterMenu::onItemChanged(QTableWidgetItem * item)
{
	string attribute = cTable->item(item->row, 0)->text().toStdString();
	string value = item->text().toStdString();

	subject->setAttribute(attribute, value);
}
