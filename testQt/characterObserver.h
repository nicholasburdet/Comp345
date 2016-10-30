#pragma once
#include "observer.h"
#include "character.h"
#include <QWidget>
#include <QGraphicsScene>
#include <QMainWindow>
#include <string>
#include <QMessageBox>
#include <qtablewidget.h>

class characterObserver:public observer, QTableWidget
{
public:
	characterObserver(character& sub);
	~characterObserver();
	void notify();
	void initialize();


private:
	character* subject;

};

