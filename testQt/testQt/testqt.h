#ifndef TESTQT_H
#define TESTQT_H

#include <QtWidgets/QMainWindow>
#include "ui_testqt.h"

class testQt : public QMainWindow
{
	Q_OBJECT

public:
	testQt(QWidget *parent = 0);
	~testQt();

private:
	Ui::testQtClass ui;
	private slots:
	void exit();
	void openWindow();
};

#endif // TESTQT_H
