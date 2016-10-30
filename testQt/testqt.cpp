/*
Author: Nicholas Burdet
Id: 29613773
Course: COMP 345
Assignment 1 Part 2: Map

Test File

This file was used for testing originally, but for some reason the program doesn't run without it. Professionally, this would be changed.
But for the purpose of this project/asssignment, it will stay for now. Ignore the contents.
*/

#include "testqt.h"
#include <QPixmap>
#include <QGraphicsScene>
#include "GridScene.cpp"


testQt::testQt(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);	
}

testQt::~testQt()
{

}

void testQt::exit()
{
	QApplication::exit();
}

void testQt::openWindow()
{
	GridScene scene(0, 0, 500, 500);
	QGraphicsView view(&scene);
	view.show();
}