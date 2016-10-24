/*
Author: Nicholas Burdet
Id: 29613773
Course: COMP 345
Assignment 1 Part 2: Map

Logic cpp file

Using QT libraries, the map grid is painted to screen and the user mouse clicks
and its coordinates are mapped and the system interprets those coordinates to determine
what element they clicked.

Mouse click event determines the space clicked in and sets the appropriate flag to true and
invokes an update method to invoke the painter method. The painter method checks the flags
to determine what steps it needs to take. Flags are reset upon handling for next event.

NOTE: Mouse click and painter methods could be broken down into smaller methods to reduce code
complexity.
*/


#include <QtWidgets>
#include <QDebug>
#include <QPainter>
#include <QPixmap>
#include "logic.h"
#include <QMessageBox>


logic::logic(QWidget *parent) : QWidget(parent)
{
	
}
void logic::initialize(int w, int h)
{
	//Builds empty default map of size w and h
	start = true;
	ms.initMap(w, h);
	wid = ms.getMaxX();
	hei = ms.getMaxY();
	update();
}

void logic::setResolution(int res)
{
	//Sets resolution for calculations based on size of map. Default is currently 50
	resolution = res;
}

void logic::loadMap()
{
	//Loads map from txt file
	ms.loadFromFile();
	wid = ms.getMaxX();
	hei = ms.getMaxY();
}

int logic::getWidth()
{
	return wid;
}

int logic::getHeight()
{
	return hei;
}

void logic::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		//Calculates where user clicked on screen (factoring in the resolution)
		//For the sake of simplicity, the coordinates stored are the top corner of the cell that the user clicked.
		//Calculation done by subtracting coordinate remainder from mod resolution from itself
		lastPoint = event->pos();
		currentX = lastPoint.x() - (lastPoint.x() % resolution);
		currentY = lastPoint.y() - (lastPoint.y() % resolution);
		QRect rect(currentX, currentY, resolution+1, resolution+1);
		
		if (currentX < 0 || currentY < 0 || (currentX)/resolution > ms.getMaxX() - 1 || (currentY)/resolution > ms.getMaxY() - 1)
		{
			//This is just a catch to see if the user clicked within the tile grid for editing or not.
			//Goes into the else if its in the grid.
		}
		else
		{
			if (currentX/resolution == ms.getStartX() && currentY / resolution == ms.getStartY())
			{
				//Do nothing if you click on start
			}
			else if (currentX/resolution == ms.getEndX() && currentY / resolution == ms.getEndY())
			{
				//Do nothing if you click on end
			}
			else
			{
				//Currently, modes establish the brush the user is currently using
				//Functionality for later should be to highlight which box user has clicked
				//But for the moment this highlight is scoped out
				if (mode == 1) {
					//Mode 1 is grass
					ms.setPassable(currentX / resolution, currentY / resolution, true);
				}
				if (mode == 2) {
					//Mode 2 is dirt (wall)
					ms.setPassable(currentX / resolution, currentY / resolution, false);
				}
				if (mode == 3) {
					//Mode 3 is start/entrance
					//Only one entrance can exist for now, so it when it applied, a grass/default
					//tile replaces to original space
					drawStart = true;
					rect = QRect(ms.getStartX()*resolution, ms.getStartY()*resolution, resolution+1, resolution+1);
					oldStartX = ms.getStartX()*resolution;
					oldStartY = ms.getStartY()*resolution;
					update(rect);
					ms.setPassable(currentX / resolution, currentY / resolution, true);
					ms.setStartX(currentX / resolution);
					ms.setStartY(currentY / resolution);
				}
				if (mode == 4) {
					//Mode 4 is end/exit
					//Only one exit can exist for now, so it when it applied, a grass/default
					//tile replaces to original space
					drawEnd = true;
					rect = QRect(ms.getEndX()*resolution, ms.getEndY()*resolution, resolution+1, resolution+1);
					oldEndX = ms.getEndX()*resolution;
					oldEndY = ms.getEndY()*resolution;
					update(rect);
					ms.setPassable(currentX / resolution, currentY / resolution, true);
					ms.setEndX(currentX / resolution);
					ms.setEndY(currentY / resolution);
				}
				//This is to update just the tile clicked, not everything else
				rect = QRect(currentX, currentY, resolution+1, resolution+1);
				clicked = true;
				update(rect);
			}
		}

		//The following (currently 6) buttons are the options at the bottom
		if (currentX == 0 && currentY == (ms.getMaxY() * resolution) + resolution)
		{
			//Changes current tile to grass
			currentTile = QPixmap("Images/grass.png");
			mode = 1;
		}
		else if (currentX == resolution && currentY == (ms.getMaxY() * resolution) + resolution)
		{
			//Changes current tile to dirt
			currentTile = QPixmap("Images/dirt.jpg");
			mode = 2;
		}
		else if (currentX == resolution*2 && currentY == (ms.getMaxY() * resolution) + resolution)
		{
			//Changes current tile to entrance
			currentTile = QPixmap("Images/start.png");
			mode = 3;
		}
		else if (currentX == resolution*3 && currentY == (ms.getMaxY() * resolution) + resolution)
		{
			//Changes current tile to exit
			currentTile = QPixmap("Images/end.png");
			mode = 4;
		}
		else if (currentX == resolution*5 && currentY == (ms.getMaxY() * resolution) + resolution)
		{
			//Invokes call to check if path exists from start to finish (paint event will check status)
			checkStatus = true;
			rect = QRect(currentX, currentY, resolution+1, resolution+1);
			update(rect);
		}
		else if (currentX == resolution * 6 && currentY == (ms.getMaxY() * resolution) + resolution)
		{
			//Saves current map to file (currently overwrites current file, 1 file limit at this time)
			ms.saveToFile();
		}
	}
}

//Paint event is called upon update. If update is passed a rectangle object, that rectangle and its coordinates
//are the only part of the screen that will receive an update.
void logic::paintEvent(QPaintEvent *event)
{
	//Images are loaded into QPixmap, this should probably be done in the header, to be done at a later date
	QPixmap grass("Images/grass.png");
	QPixmap dirt("Images/dirt.jpg");
	QPixmap entranceDoor("Images/start.png");
	QPixmap exitDoor("Images/end.png");
	QPixmap checkButton("Images/button.png");
	QPixmap errorButton("Images/redbutton.jpg");
	QPixmap saveButton("Images/save.png");
	//QPixmap loadButton("C:/Users/Nick/Desktop/Images/load.png");

	QPainter painter(this);
	//Start section draws the grid on screen (based on resolution) as well as all tiles on screen based off
	//current map in the object. Start is set to true each time the screen needs a full update.
	if (start)
	{
		int xRes = ms.getMaxX() * resolution;
		int yRes = ms.getMaxY() * resolution;
		
		//Builds the tiles onto the screen from the map object. As of right now, there are only 4 tiles that exist
		//for the map. Grass->passable, Dirt->not passable, Entrance and Exit.
		//Will have to be reworked to incorporate larger sprite sets and the addition of items and enemies on the map
		for (int x = 0; x < ms.getMaxX(); x++)
		{
			for (int y = 0; y < ms.getMaxY(); y++)
			{
				if (ms.isPassable(x, y))
				{
					if (ms.getStartX() == x && ms.getStartY() == y)
					{
						painter.drawPixmap(x*resolution, y*resolution, resolution, resolution, entranceDoor);
					}
					else if (ms.getEndX() == x && ms.getEndY() == y)
					{
						painter.drawPixmap(x*resolution, y*resolution, resolution, resolution, exitDoor);
					}
					else
					{				
						painter.drawPixmap(x*resolution, y*resolution, resolution, resolution, grass);
					}
				}
				else
				{
					painter.drawPixmap(x*resolution, y*resolution, resolution, resolution, dirt);
				}
			}
		}

		//This section draws all vertical and horizontal lines
		for (int y = 0; y <= yRes; y += resolution)
		{
			painter.drawLine(0, y, xRes, y);
		}

		for (int x = 0; x <= xRes; x += resolution)
		{
			painter.drawLine(x, 0, x, yRes);
		}

		//This section draws the buttons at the bottom of the screen
		painter.drawPixmap(0, yRes+ resolution, resolution, resolution, grass);
		painter.drawPixmap(resolution, yRes+ resolution, resolution, resolution, dirt);
		painter.drawPixmap(resolution*2, yRes + resolution, resolution, resolution, entranceDoor);
		painter.drawPixmap(resolution*3, yRes + resolution, resolution, resolution, exitDoor);
		if (path)
		{
			painter.drawPixmap(resolution*5, (ms.getMaxY() * resolution + resolution), resolution, resolution, checkButton);
		}
		else
		{
			painter.drawPixmap(resolution*5, (ms.getMaxY() * resolution + resolution), resolution, resolution, errorButton);
		}
		painter.drawPixmap(resolution * 6, yRes + resolution, resolution, resolution, saveButton);
		//painter.drawPixmap(resolution * 7, yRes + resolution, resolution, resolution, loadButton);
		start = false;
	}

	if (clicked)
	{
		//When click is turned true with an update() call, this draws the current tile and the lines around it
		QRect rect(currentX, currentY, resolution, resolution);
		painter.drawPixmap(rect,currentTile);
		painter.drawRect(rect);
		painter.drawLine(currentX, currentY + resolution, currentX + resolution, currentY + resolution);
		clicked = false;
	}

	if (drawStart)
	{
		//This draws a grass tile on where the old entrance was after a new one has been placed
		QRect rect(oldStartX, oldStartY, resolution, resolution);
		painter.drawPixmap(rect, grass);
		painter.drawRect(rect);
		drawStart = false;
	}

	if (drawEnd)
	{
		//This draws a grass tile on where the old exit was after a new one has been placed
		QRect rect(oldEndX, oldEndY, resolution, resolution);
		painter.drawPixmap(rect, grass);
		painter.drawRect(rect);
		drawEnd = false;
	}

	if (checkStatus)
	{
		//This method invokes the algorithm to check if a path from start to finish exists, and displays green (exists) or red (doesnt exist)
		if (ms.checkExit())
		{
			path = true;
			painter.drawPixmap(resolution*5, (ms.getMaxY() * resolution + resolution), resolution, resolution, checkButton);
		}
		else
		{
			path = false;
			painter.drawPixmap(resolution*5, (ms.getMaxY() * resolution + resolution), resolution, resolution, errorButton);
		}
		checkStatus = false;
	}
}

void logic::resizeEvent(QResizeEvent * event)
{
	//updates window on resize
	start = true;
	update();
}

void logic::leaveEvent(QEvent * event)
{
	//updates window on leaving screen
	start = true;
	update();
}

//Minor issue with contents of screen disappearing after size selection at launch, until user mouses out of window
//Will look into fixing this issue, but it isn't a glaring issue at this time