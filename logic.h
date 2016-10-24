/*
Author: Nicholas Burdet
Id: 29613773
Course: COMP 345
Assignment 1 Part 2: Map

Logic header file
*/

#ifndef LOGIC_H
#define LOGIC_H

#include <QPoint>
#include <QWidget>
#include "MapScreen.h"
#include <string>

using namespace std;

class logic : public QWidget
{
	Q_OBJECT;
	public:
		logic(QWidget *parent = 0);
		void initialize(int w, int h);
		void setResolution(int res);
		void loadMap();
		int getWidth();
		int getHeight();
	protected:
		void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
		void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
		void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
		void leaveEvent(QEvent * event) Q_DECL_OVERRIDE;
	private:
		QPoint lastPoint = QPoint(0,0);
		QImage image;

		//flag to invoke fullscreen painter and initialization (also incase contents of screen disappear)
		bool start = true;

		MapScreen ms;
		int resolution = 50;

		//flag each time users clicks on screen to invoke mouse event
		bool clicked = false;

		int currentX;
		int currentY;
		QPixmap currentTile = QPixmap("C:/Users/Nick/Desktop/Images/grass.png");
		
		//This will be the mode checking for tiles
		int mode = 1; 
		
		//flags to indicate the user is drawing entrance or exit
		bool drawStart = false; 
		bool drawEnd = false;

		//flag to check path status
		bool checkStatus = true;

		//stores if path exists here, default map path exists
		bool path = true;

		//values to hold previous entrance or exit when painting new ones to fill in old spaces
		int oldStartX;
		int oldStartY;
		int oldEndX;
		int oldEndY;

		
		int wid;
		int hei;
};

#endif
