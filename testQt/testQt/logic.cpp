/*
Author: Nicholas Burdet
Id: 29613773
Course: COMP 345
Assignment 2 Part 3: Map

Logic cpp file

Using QT libraries, the map grid is painted to screen and the user mouse clicks
and its coordinates are mapped and the system interprets those coordinates to determine
what element they clicked.

Mouse click event determines the space clicked in and sets the appropriate flag to true and
invokes an update method to invoke the painter method. The painter method checks the flags
to determine what steps it needs to take. Flags are reset upon handling for next event.

NOTE: Mouse click and painter methods could be broken down into smaller methods to reduce code
complexity.

Second update now handles campaign functionality
*/

#include <QtWidgets>
#include <QDebug>
#include <QPainter>
#include <QPixmap>
#include "logic.h"


//Constructor loads Distinct NPCs into memory for use by editor and maps
logic::logic(QWidget *parent, QMainWindow *mw) : QWidget(parent)
{
	mainWindow = mw;
	ms.loadNPCs();
	setFocusPolicy(Qt::ClickFocus);
	message.setFocusPolicy(Qt::NoFocus);
	combatLog = player_Log();
}

//Initializes a map object and loads the appropriate campaign
void logic::initialize(int w, int h, string n)
{
	start = true;
	ms.initMap(w, h, n);
	ms.setId(Campaign.getNumberOfMaps());
	Campaign.setCurrentMapId(Campaign.getNumberOfMaps());
	ms.setCampaignId(Campaign.getId());
	ms.setCampaignName(Campaign.getName());
	ms.saveToFile();
	Campaign.addMap(ms.getFilename());
	Campaign.saveCampaign();
	wid = ms.getMaxX();
	hei = ms.getMaxY();
	update();
}

//Enters campaign name and id#
void logic::newCampaign(string cName, int cId)
{
	Campaign.setId(cId);
	Campaign.setName(cName);
}

//Loads campaign and last map in the campaign
void logic::loadCampaign(string filename)
{
	Campaign.loadCampaign(filename);
	
	string extension = "Maps/";

	loadMap(extension.append(Campaign.getMapFilename(0)));
	Campaign.setCurrentMapId(0);

	//This loads last map of campaign
	//loadMap(extension.append(Campaign.getMapFilename(Campaign.getNumberOfMaps() - 1)));
	//Campaign.setCurrentMapId(Campaign.getNumberOfMaps() - 1);
}

//This method is for loading the campaign after a map has been loaded. The previous method
//will automatically load the last map from the campaign, and does so after the campaign has been loaded.
void logic::loadJustCampaign()
{
	string extension = "Campaigns/";
	string f = extension;
	f.append(ms.getCampaignName());
	f.append(to_string(ms.getCampaignId()));
	f.append(".txt");
	Campaign.loadCampaign(f);
	Campaign.setCurrentMapId(ms.getId());
}

void logic::loadPlayerCharacter(string filename)
{
	ms.loadPlayerCharacter(filename);
}

//Sets resolution for calculations based on size of map. Default is currently 50
void logic::setResolution(int res)
{
	resolution = res;
}

//Loads map from txt file
void logic::loadMap(string filename)
{
	ms.loadFromFile(filename);
	wid = ms.getMaxX();
	hei = ms.getMaxY();
	ms.setCurrentX(ms.getStartX());
	ms.setCurrentY(ms.getStartY());
}

void logic::newMap()
{
	MapScreen newMap;
	ms = newMap;
	ms.loadNPCs();
}

//Resets the map object but retains its position and campaign
void logic::resetMap(int w, int h)
{
	string holdName = ms.getName();
	MapScreen newMap;
	ms = newMap;
	ms.loadNPCs();
	ms.initMap(w, h, holdName);
	ms.setId(Campaign.getCurrentMapId());
	ms.setCampaignId(Campaign.getId());
	ms.setCampaignName(Campaign.getName());
	ms.saveToFile();
	wid = ms.getMaxX();
	hei = ms.getMaxY();
}

//Navigates to previous map, passes false if it cannot
bool logic::previousMap()
{
	if (Campaign.getCurrentMapId() > 0)
	{
		Campaign.setCurrentMapId(Campaign.getCurrentMapId() - 1);
		MapScreen newMap;
		ms = newMap;
		ms.loadNPCs();
		return true;
	}
	else
	{
		return false;
	}
}

//Navigates to next map, passes false if it cannot
bool logic::nextMap()
{
	if (Campaign.getCurrentMapId() < Campaign.getNumberOfMaps()-1)
	{
		Campaign.setCurrentMapId(Campaign.getCurrentMapId() + 1);
		MapScreen newMap;
		ms = newMap;
		ms.loadNPCs();
		return true;
	}
	else
	{
		return false;
	}
}

string logic::getFilename()
{
	return Campaign.getMapFilename(Campaign.getCurrentMapId());
}

void logic::closeWindow()
{
	close();
}

int logic::getWidth()
{
	return wid;
}

int logic::getHeight()
{
	return hei;
}

void logic::setEditmode(bool editM)
{
	editMode = editM;
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
		
		//Edit mode is for map editor view
		if (editMode)
		{
			if (currentX < 0 || currentY < 0 || (currentX) / resolution > ms.getMaxX() - 1 || (currentY) / resolution > ms.getMaxY() - 1)
			{
				//This is just a catch to see if the user clicked within the tile grid for editing or not.
				//Goes into the else if its in the grid.
			}
			else
			{
				if (currentX / resolution == ms.getStartX() && currentY / resolution == ms.getStartY())
				{
					//Do nothing if you click on start
				}
				else if (currentX / resolution == ms.getEndX() && currentY / resolution == ms.getEndY())
				{
					//Do nothing if you click on end
				}
				else
				{
					rect = QRect(currentX, currentY, resolution + 1, resolution + 1);
					//Currently, modes establish the brush the user is currently using
					//Functionality for later should be to highlight which box user has clicked
					//But for the moment this highlight is scoped out
					if (mode == 1) {
						//Mode 1 is grass
						ms.setPassable(currentX / resolution, currentY / resolution, true);
						if (ms.isOccupied(currentX / resolution, currentY / resolution))
						{
							ms.removeNPC(currentX / resolution, currentY / resolution);
							ms.removeItem(currentX / resolution, currentY / resolution);
						}
						update(rect);
						clicked = true;
					}
					if (mode == 2) {
						//Mode 2 is dirt (wall)
						ms.setPassable(currentX / resolution, currentY / resolution, false);
						if (ms.isOccupied(currentX / resolution, currentY / resolution))
						{
							ms.removeNPC(currentX / resolution, currentY / resolution);
							ms.removeItem(currentX / resolution, currentY / resolution);
						}
						update(rect);
						clicked = true;
					}
					if (mode == 3) {
						//Mode 3 is start/entrance
						//Only one entrance can exist for now, so it when it applied, a grass/default
						//tile replaces to original space
						drawStart = true;
						if (ms.isOccupied(currentX / resolution, currentY / resolution))
						{
							ms.removeNPC(currentX / resolution, currentY / resolution);
							ms.removeItem(currentX / resolution, currentY / resolution);
						}
						rect = QRect(ms.getStartX()*resolution, ms.getStartY()*resolution, resolution + 1, resolution + 1);
						oldStartX = ms.getStartX()*resolution;
						oldStartY = ms.getStartY()*resolution;
						update(rect);
						ms.setPassable(currentX / resolution, currentY / resolution, true);
						ms.setStartX(currentX / resolution);
						ms.setStartY(currentY / resolution);

						rect = QRect(ms.getStartX()*resolution, ms.getStartY()*resolution, resolution + 1, resolution + 1);
						clicked = true;
						update(rect);
					}
					if (mode == 4) {
						//Mode 4 is end/exit
						//Only one exit can exist for now, so it when it applied, a grass/default
						//tile replaces to original space
						drawEnd = true;
						if (ms.isOccupied(currentX / resolution, currentY / resolution))
						{
							ms.removeNPC(currentX / resolution, currentY / resolution);
							ms.removeItem(currentX / resolution, currentY / resolution);
						}
						rect = QRect(ms.getEndX()*resolution, ms.getEndY()*resolution, resolution + 1, resolution + 1);
						oldEndX = ms.getEndX()*resolution;
						oldEndY = ms.getEndY()*resolution;
						update(rect);
						ms.setPassable(currentX / resolution, currentY / resolution, true);
						ms.setEndX(currentX / resolution);
						ms.setEndY(currentY / resolution);

						rect = QRect(ms.getEndX()*resolution, ms.getEndY()*resolution, resolution + 1, resolution + 1);
						clicked = true;
						update(rect);
					}
					if (mode == 5) {
						//Mode 5 is NPC generation
						if (ms.isPassable(currentX / resolution, currentY / resolution))
						{
							if (npcId < ms.getNumberOfDistinctNPCs())
							{
								if (ms.isOccupied(currentX / resolution, currentY / resolution))
								{
									ms.removeNPC(currentX / resolution, currentY / resolution);
									ms.removeItem(currentX / resolution, currentY / resolution);
								}
								ms.addNPC(npcId, currentX / resolution, currentY / resolution);
								drawNPC = true;
								update(rect);
							}
						}
					}
					if (mode == 6) {
						//Mode 6 is ITEM placement
						if (ms.isPassable(currentX / resolution, currentY / resolution))
						{
							if (ms.isOccupied(currentX / resolution, currentY / resolution))
							{
								ms.removeNPC(currentX / resolution, currentY / resolution);
								ms.removeItem(currentX / resolution, currentY / resolution);
							}
							string selectedItem = addItem();
							drawItem = true;
							update(rect);
							ms.addItem(currentX / resolution, currentY / resolution, selectedItem);
						}
					}
					if (mode == 7) {
						//Mode 7 is CHEST placement
						if (ms.isPassable(currentX / resolution, currentY / resolution))
						{
							//Disabled for now
							//drawChest = true;
							//update(rect);
						}
					}
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
			else if (currentX == resolution * 2 && currentY == (ms.getMaxY() * resolution) + resolution)
			{
				//Changes current tile to entrance
				currentTile = QPixmap("Images/start.png");
				mode = 3;
			}
			else if (currentX == resolution * 3 && currentY == (ms.getMaxY() * resolution) + resolution)
			{
				//Changes current tile to exit
				currentTile = QPixmap("Images/end.png");
				mode = 4;
			}
			else if (currentX == resolution * 5 && currentY == (ms.getMaxY() * resolution) + resolution)
			{
				//Invokes call to check if path exists from start to finish (paint event will check status)
				checkStatus = true;
				rect = QRect(currentX, currentY, resolution + 1, resolution + 1);
				update(rect);
			}
			else if (currentX == resolution * 6 && currentY == (ms.getMaxY() * resolution) + resolution)
			{
				//Saves current map to file (currently overwrites current file, 1 file limit at this time)
				if (ms.checkExit())
				{
					//Checks to see if path exists, will only save valid maps
					/*QString filename;
					bool ok;
					filename = QInputDialog::getText(this, "==Filename?==", tr("Save as:(.txt will auto add to end)"), QLineEdit::Normal, "", &ok);
					string fName = filename.toStdString();
					*/
					message.setText("Map has been successfully saved.");
					message.show();
					ms.saveToFile();
					start = true;
					update();
				}
				else
				{
					message.setText("Path to exit does not exist. Map was not saved.");
					message.exec();
					start = true;
					update();
				}
			}
			else if (currentY == (ms.getMaxY() * resolution) + resolution * 2)
			{
				//Changes current tile to enemy ADDED 27/10/16
				//This will check which Id is being used to grab the right image from the list
				npcId = currentX / resolution;
				string im = ms.characterTable[npcId].getImage();
				const char * c = im.c_str();
				currentTile = QPixmap(c);
				mode = 5;
			}
			else if ((currentY == (ms.getMaxY() * resolution) + resolution * 3) && currentX == 0)
			{
				//General item
				currentTile = item;
				mode = 6;
			}
			else if ((currentY == (ms.getMaxY() * resolution) + resolution * 3) && currentX == 1 * resolution)
			{
				//Item chest container
				currentTile = chest;
				mode = 7;
			}
		}
		else
		{
			start = true;
			update();
		}
	}
}

//Paint event is called upon update. If update is passed a rectangle object, that rectangle and its coordinates
//are the only part of the screen that will receive an update.
void logic::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);

	font = painter.font();
	
	font.setPointSize(8);
	font.setWeight(QFont::DemiBold);
	painter.setFont(font);
	painter.setPen(QPen(Qt::black));

	int xRes = ms.getMaxX() * resolution;
	int yRes = ms.getMaxY() * resolution;

	int minX;

	if (ms.getMaxX() < 12)
	{
		minX = 12;
	}
	else
	{
		minX = ms.getMaxX();
	}
	//Start section draws the grid on screen (based on resolution) as well as all tiles on screen based off
	//current map in the object. Start is set to true each time the screen needs a full update.
	if (start)
	{
		painter.drawPixmap(0, 0, minX*resolution, ((ms.getMaxY()*resolution)+(resolution * 4) + 20), background);
		//Draws log background if not in editmode (for gameplay)
		if (!editMode)
		{
			QString textWindow;
			painter.drawPixmap(0, yRes, minX*resolution, 150, logBackground);
			int logStart = combatLog.getLogLength() - 13;
			if (logStart < 0)
			{
				logStart = 0;
			}
			int count = 0;

			for (int i = combatLog.getLogLength(); i > logStart; i--)
			{
				textWindow = QString::fromStdString(combatLog.readLogEntry(i));
				painter.drawText(12, ms.getMaxY()*resolution + 20 + (10 * count), textWindow);
				count++;
			}
		}
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

		//Paints NPCs onto screen
		int max = ms.getNumberOfNPCs();
		int count = 0;
		int index = 0;
		while(count < max)
		{
			if (ms.characterEntities[index].getName() != "NULL")
			{
				string im = ms.characterEntities[index].getImage();
				const char * c = im.c_str();
				QPixmap npcTemp(c);
				int x, y;
				x = ms.characterEntities[index].getX();
				y = ms.characterEntities[index].getY();
				painter.drawPixmap(x*resolution, y*resolution, resolution, resolution, npcTemp);
				count++;
			}
			index++;
		}

		//Paints Items onto screen
		max = ms.getNumberOfItems();
		count = 0;
		index = 0;
		while (count < max)
		{
			if (ms.mapItems[index].itemName != "NULL")
			{
				int x, y;
				x = ms.mapItems[index].itemX;
				y = ms.mapItems[index].itemY;
				painter.drawPixmap(x*resolution, y*resolution, resolution, resolution, item);
				count++;
			}
			index++;
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


		if (editMode)
		{
			//This section draws the buttons at the bottom of the screen
			painter.drawPixmap(0, yRes + resolution, resolution, resolution, grass);
			painter.drawPixmap(resolution, yRes + resolution, resolution, resolution, dirt);
			painter.drawPixmap(resolution * 2, yRes + resolution, resolution, resolution, entranceDoor);
			painter.drawPixmap(resolution * 3, yRes + resolution, resolution, resolution, exitDoor);
			if (path)
			{
				painter.drawPixmap(resolution * 5, (ms.getMaxY() * resolution + resolution), resolution, resolution, checkButton);
			}
			else
			{
				painter.drawPixmap(resolution * 5, (ms.getMaxY() * resolution + resolution), resolution, resolution, errorButton);
			}
			painter.drawPixmap(resolution * 6, yRes + resolution, resolution, resolution, saveButton);
			//painter.drawPixmap(resolution * 7, yRes + resolution, resolution, resolution, menu);

			//Draw NPC buttons here (broaden this later) ADDED 27/10/16
			for (int i = 0; i < 10; i++)
			{
				if (ms.characterTable[i].getName() != "NULL")
				{
					//PROGRESS: Trying to figure out how to get string value into QPixmap
					string img = ms.characterTable[i].getImage();
					const char * c = img.c_str();
					QPixmap npc(c);
					painter.drawPixmap(resolution*i, yRes + resolution * 2, resolution, resolution, npc);
				}
			}
			//Item buttons drawn here
			painter.drawPixmap(0, yRes + resolution*3, resolution, resolution, item);
			painter.drawPixmap(resolution * 1, yRes + resolution*3, resolution, resolution, chest);
		}
		else
		{
			painter.drawPixmap(ms.getCurrentX()*resolution, ms.getCurrentY()*resolution, resolution, resolution, playerImage);
		}
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

	if (drawNPC)
	{
		//This draws a grass tile and then draws the NPC
		QRect rect(currentX, currentY, resolution, resolution);
		painter.drawPixmap(rect, grass);
		painter.drawRect(rect);
		painter.drawPixmap(rect, currentTile);
		painter.drawRect(rect);
		painter.drawLine(currentX, currentY + resolution, currentX + resolution, currentY + resolution);
		drawNPC = false;
	}

	if (drawItem) {
		//This draws a grass tile and then draws the ITEM
		QRect rect(currentX, currentY, resolution, resolution);
		painter.drawPixmap(rect, grass);
		painter.drawRect(rect);
		painter.drawPixmap(rect, currentTile);
		painter.drawRect(rect);
		painter.drawLine(currentX, currentY + resolution, currentX + resolution, currentY + resolution);
		drawItem = false;
	}

	if (drawChest) {
		//This draws a grass tile and then draws the CHEST
		QRect rect(currentX, currentY, resolution, resolution);
		painter.drawPixmap(rect, grass);
		painter.drawRect(rect);
		painter.drawPixmap(rect, currentTile);
		painter.drawRect(rect);
		painter.drawLine(currentX, currentY + resolution, currentX + resolution, currentY + resolution);
		drawChest = false;
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

	if (replacePlayer)
	{
		QRect rect(oldPlayerX*resolution, oldPlayerY*resolution, resolution, resolution);
		if (replace == "grass")
		{
			painter.drawPixmap(rect, grass);
			painter.drawRect(rect);
		}
		else if (replace == "start")
		{
			painter.drawPixmap(rect, entranceDoor);
			painter.drawRect(rect);
		}
		else if (replace == "end")
		{
			painter.drawPixmap(rect, exitDoor);
			painter.drawRect(rect);
		}
		replacePlayer = false;
	}

	if (movePlayer)
	{
		QRect rect(ms.getCurrentX()*resolution, ms.getCurrentY()*resolution, resolution, resolution);
		painter.drawPixmap(rect, grass);
		if (ms.getCurrentX() == ms.getStartX() && ms.getCurrentY() == ms.getStartY())
		{
			painter.drawPixmap(rect, entranceDoor);
		}
		if (ms.getCurrentX() == ms.getEndX() && ms.getCurrentY() == ms.getEndY())
		{
			painter.drawPixmap(rect, exitDoor);
		}
		painter.drawPixmap(rect, playerImage);
		painter.drawRect(rect);
		
		movePlayer = false;
		QRect recta(oldPlayerX*resolution, oldPlayerY*resolution, resolution, resolution);
		if (oldPlayerX == ms.getStartX() && oldPlayerY == ms.getStartY())
		{
			replace = "start";
		}
		else if (oldPlayerX == ms.getEndX() && oldPlayerY == ms.getEndY())
		{
			replace = "end";
		}
		else
		{
			replace = "grass";
		}
		replacePlayer = true;
		update(recta);
	}

	if(textChange)
	{
		QString textWindow;
		painter.drawPixmap(0, yRes, minX*resolution, 150, logBackground);
		int logStart = combatLog.getLogLength() - 13;
		if (logStart < 0)
		{
			logStart = 0;
		}
		int count = 0;
		
		for (int i = combatLog.getLogLength(); i > logStart; i--)
		{
			textWindow = QString::fromStdString(combatLog.readLogEntry(i));
			painter.drawText(12, ms.getMaxY()*resolution + 20 + (10 * count), textWindow);
			count++;
		}
		
		textChange = false;
	}
}

void logic::keyPressEvent(QKeyEvent *event)
{
	if (!editMode)
	{
		bool didPlayerMove = false;
		oldPlayerX = ms.getCurrentX();
		oldPlayerY = ms.getCurrentY();

		int minXReso = ms.getMaxX();
		if (ms.getMaxX() < 12)
		{
			minXReso = 12;
		}

		if (!mapStart)
		{
			//Up/Down/Left/Right Movement events
			if (event->key() == Qt::Key_Left && playerTurn && playerMove && playerAttacking == false) {
				if (ms.getCurrentX() > 0 && !(ms.isOccupied(ms.getCurrentX() - 1, ms.getCurrentY())) && ms.isPassable(ms.getCurrentX() - 1, ms.getCurrentY()))
				{
					ms.setCurrentX(ms.getCurrentX() - 1);
					movePlayer = true;
					QRect rect(ms.getCurrentX()*resolution, ms.getCurrentY()*resolution, resolution, resolution);
					update(rect);
					playerSteps++; //To keep track of the number of steps
					didPlayerMove = true;
				}
			}
			else if (event->key() == Qt::Key_Right && playerTurn && playerMove && playerAttacking == false) {
				if (ms.getCurrentX() < ms.getMaxX() - 1 && !(ms.isOccupied(ms.getCurrentX() + 1, ms.getCurrentY())) && ms.isPassable(ms.getCurrentX() + 1, ms.getCurrentY()))
				{
					ms.setCurrentX(ms.getCurrentX() + 1);
					movePlayer = true;
					QRect rect(ms.getCurrentX()*resolution, ms.getCurrentY()*resolution, resolution, resolution);
					update(rect);
					playerSteps++; //To keep track of the number of steps
					didPlayerMove = true;
				}
			}
			else if (event->key() == Qt::Key_Up && playerTurn && playerMove && playerAttacking == false) {
				if (ms.getCurrentY() > 0 && !(ms.isOccupied(ms.getCurrentX(), ms.getCurrentY() - 1)) && ms.isPassable(ms.getCurrentX(), ms.getCurrentY() - 1))
				{
					ms.setCurrentY(ms.getCurrentY() - 1);
					movePlayer = true;
					QRect rect(ms.getCurrentX()*resolution, ms.getCurrentY()*resolution, resolution, resolution);
					update(rect);
					playerSteps++; //To keep track of the number of steps
					didPlayerMove = true;
				}
			}
			else if (event->key() == Qt::Key_Down && playerTurn && playerMove && playerAttacking == false) {
				if (ms.getCurrentY() < ms.getMaxY() - 1 && !(ms.isOccupied(ms.getCurrentX(), ms.getCurrentY() + 1)) && ms.isPassable(ms.getCurrentX(), ms.getCurrentY() + 1))
				{
					ms.setCurrentY(ms.getCurrentY() + 1);
					movePlayer = true;
					QRect rect(ms.getCurrentX()*resolution, ms.getCurrentY()*resolution, resolution, resolution);
					update(rect);
					playerSteps++; //To keep track of the number of steps
					didPlayerMove = true;
				}
			}
			//Code for next event stuff goes here (player can advance the game when not his turn by pressing N)
			else if (event->key() == Qt::Key_N && playerTurn == false) {
				string chatText;
				QRect rect(0, ms.getMaxY()*resolution, minXReso * resolution, 50 * 3);
				bool moved = ms.npcMovement(turnOrder[npcTurn], ms.getCurrentX(), ms.getCurrentY());
				if(moved)
				{
					chatText = "NPC ";
					chatText.append(std::to_string(turnOrder[npcTurn]));
					chatText.append(" moves to X:");
					chatText.append(std::to_string(ms.characterEntities[turnOrder[npcTurn]].getX()));
					chatText.append(" Y:");
					chatText.append(std::to_string(ms.characterEntities[turnOrder[npcTurn]].getY()));
					combatLog.addToLog(chatText);
				}
				else
				{
					chatText = "NPC ";
					chatText.append(std::to_string(turnOrder[npcTurn]));
					chatText.append(" does not move.");
					combatLog.addToLog(chatText);
				}

				//NPC Attack goes here
				chatText = "Nothing";
				if (ms.characterEntities[turnOrder[npcTurn]].getType() == "hostile")
				{
					chatText = ms.npcAttack(turnOrder[npcTurn], moved);
				}
				if (chatText != "Nothing")
				{
					combatLog.addToLog(chatText);
				}

				textChange = true;
				update(rect);

				npcTurn++;
				if (npcTurn > ms.getNumberOfNPCs())
				{
					npcTurn = 0;
				}

				start = true;
				update();
				if (turnOrder[npcTurn] == -1 || ms.getNumberOfNPCs() == 0)
				{
					playerTurn = true;
					playerMove = true;
					playerSteps = 0;
					chatText = "Player turn start!";
					combatLog.addToLog(chatText);
					textChange = true;
					update(rect);
				}
			}
			//Code for stopping player movement during their turn (end movement)
			else if (event->key() == Qt::Key_S && playerMove == true && playerTurn == true && playerAttacking == false)
			{
				//Code for player stop goes here NOTE:Fix player movement end ending their turn
				//Note: Also potentially limit player movement dialog messages to destination ONLY?
				
				QRect rect(0, ms.getMaxY()*resolution, resolution * minXReso*resolution, 50 * 3);
				string chatText = "Movement for turn ended.";
				chatText.append(" Attack (A), Loot Item (L) or End Turn (E)");
				playerMove = false;
				
				combatLog.addToLog(chatText);
				textChange = true;
				update(rect);
			}
			//Code for attacking during player turn goes here
			else if (event->key() == Qt::Key_A && playerTurn == true && playerAttacking == false)
			{
				playerAttacking = true;
				//Checks to see if player will use 1 attack or full attack
				string chatText;
				if (playerSteps == 0)
				{
					fullAttack = true;
					chatText = "You prepare a full attack! Choose a direction to attack.";
				}
				else
				{
					fullAttack = false;
					chatText = "You declare an attack! Choose a direction to attack.";
				}
				QRect rect(0, ms.getMaxY()*resolution, resolution * minXReso*resolution, 50 * 3);
				
				combatLog.addToLog(chatText);
				textChange = true;
				update(rect);
			}

			//Code for each attack direction goes here!
			else if (event->key() == Qt::Key_Up && playerTurn == true && playerAttacking == true)
			{
				string attackMessage;
				int adjX = ms.getCurrentX();
				int adjY = ms.getCurrentY() - 1;
				string dir = "up";
				//Checks bounds
				if (adjY > 0)
				{
					attackMessage = ms.playerAttack(adjX, adjY, dir, fullAttack);
				}
				QRect rect(0, ms.getMaxY()*resolution, resolution * minXReso*resolution, 50 * 3);
				combatLog.addToLog(attackMessage);
				textChange = true;
				update(rect);

				string chatText = "Player turn has ended.";
				npcTurn++;
				if (npcTurn > ms.getNumberOfNPCs())
				{
					npcTurn = 0;
				}
				fullAttack = false;
				playerTurn = false;
				playerAttacking = false;
				combatLog.addToLog(chatText);
				textChange = true;
				update(rect);
			}
			else if (event->key() == Qt::Key_Down && playerTurn == true && playerAttacking == true)
			{
				string attackMessage;
				int adjX = ms.getCurrentX();
				int adjY = ms.getCurrentY() + 1;
				//Checks bounds
				string dir = "down";
				if (adjY < ms.getMaxY()-1)
				{
					attackMessage = ms.playerAttack(adjX, adjY, dir, fullAttack);
				}
				QRect rect(0, ms.getMaxY()*resolution, resolution * minXReso*resolution, 50 * 3);
				combatLog.addToLog(attackMessage);
				textChange = true;
				update(rect);

				string chatText = "Player turn has ended.";
				npcTurn++;
				if (npcTurn > ms.getNumberOfNPCs())
				{
					npcTurn = 0;
				}
				fullAttack = false;
				playerTurn = false;
				playerAttacking = false;
				combatLog.addToLog(chatText);
				textChange = true;
				update(rect);
			}
			else if (event->key() == Qt::Key_Left && playerTurn == true && playerAttacking == true)
			{
				string attackMessage;
				int adjX = ms.getCurrentX() - 1;
				int adjY = ms.getCurrentY();
				string dir = "left";
				//Checks bounds
				if (adjX > 0)
				{
					attackMessage = ms.playerAttack(adjX, adjY, dir, fullAttack);
				}
				QRect rect(0, ms.getMaxY()*resolution, resolution * minXReso*resolution, 50 * 3);
				combatLog.addToLog(attackMessage);
				textChange = true;
				update(rect);

				string chatText = "Player turn has ended.";
				npcTurn++;
				if (npcTurn > ms.getNumberOfNPCs())
				{
					npcTurn = 0;
				}
				fullAttack = false;
				playerTurn = false;
				playerAttacking = false;
				combatLog.addToLog(chatText);
				textChange = true;
				update(rect);
			}
			else if (event->key() == Qt::Key_Right && playerTurn == true && playerAttacking == true)
			{
				string attackMessage;
				int adjX = ms.getCurrentX() + 1;
				int adjY = ms.getCurrentY();
				string dir = "right";
				//Checks bounds
				if (adjX < ms.getMaxX() - 1)
				{
					attackMessage = ms.playerAttack(adjX, adjY, dir, fullAttack);
				}
				QRect rect(0, ms.getMaxY()*resolution, resolution * minXReso*resolution, 50 * 3);
				combatLog.addToLog(attackMessage);
				textChange = true;
				update(rect);

				string chatText = "Player turn has ended.";
				npcTurn++;
				if (npcTurn > ms.getNumberOfNPCs())
				{
					npcTurn = 0;
				}
				fullAttack = false;
				playerTurn = false;
				playerAttacking = false;
				combatLog.addToLog(chatText);
				textChange = true;
				update(rect);
			}
			//End of attack direction code above ^^^^^^

			//Code for looting during player turn goes here
			else if (event->key() == Qt::Key_L && playerTurn == true)
			{
				QRect rect(0, ms.getMaxY()*resolution, resolution * minXReso*resolution, 50 * 3);
				string chatText = "You looted around you!";
				combatLog.addToLog(chatText);
				//Loot all around you
				string itemUp = ms.lootItems(ms.getCurrentX(), ms.getCurrentY() - 1);
				string itemDown = ms.lootItems(ms.getCurrentX(), ms.getCurrentY() + 1);
				string itemLeft = ms.lootItems(ms.getCurrentX() - 1, ms.getCurrentY());
				string itemRight = ms.lootItems(ms.getCurrentX() + 1, ms.getCurrentY());

				/********************************************************************
				Add to appropriate BACKPACK here when its ready!!
				********************************************************************/

				//Prints this if nothing is returned
				if (itemUp == "NULL" && itemDown == "NULL" && itemLeft == "NULL" && itemRight == "NULL")
				{
					chatText.append("You found nothing!");
					combatLog.addToLog(chatText);
				}
				//Checks each item to display multiple found if at all
				if (itemUp != "NULL")
				{
					std::istringstream idS(itemUp);
					string sID;
					std::getline(idS, sID, '|');
					std::getline(idS, sID, '|');
					std::getline(idS, sID, '|');
					chatText = "You found ";
					chatText.append(sID);
					chatText.append(".");
					combatLog.addToLog(chatText);
				}
				if (itemDown != "NULL")
				{
					std::istringstream idS(itemDown);
					string sID;
					std::getline(idS, sID, '|');
					std::getline(idS, sID, '|');
					std::getline(idS, sID, '|');
					chatText = "You found ";
					chatText.append(sID);
					chatText.append(".");
					combatLog.addToLog(chatText);
				}
				if (itemLeft != "NULL")
				{
					std::istringstream idS(itemLeft);
					string sID;
					std::getline(idS, sID, '|');
					std::getline(idS, sID, '|');
					std::getline(idS, sID, '|');
					chatText = "You found ";
					chatText.append(sID);
					chatText.append(".");
					combatLog.addToLog(chatText);
				}
				if (itemRight != "NULL")
				{
					std::istringstream idS(itemRight);
					string sID;
					std::getline(idS, sID, '|');
					std::getline(idS, sID, '|');
					std::getline(idS, sID, '|');
					chatText = "You found ";
					chatText.append(sID);
					chatText.append(".");
					combatLog.addToLog(chatText);
				}

				chatText = "Player turn has ended.";
				npcTurn++;
				if (npcTurn > ms.getNumberOfNPCs())
				{
					npcTurn = 0;
				}
				playerTurn = false;
				playerAttacking = false;
				combatLog.addToLog(chatText);
				start = true;
				update();
			}
			else if (event->key() == Qt::Key_E && playerTurn == true)
			{
				//End player turn
				QRect rect(0, ms.getMaxY()*resolution, resolution * minXReso*resolution, 50 * 3);
				string chatText = "Player turn has ended.";
				npcTurn++;
				if (npcTurn > ms.getNumberOfNPCs())
				{
					npcTurn = 0;
				}
				fullAttack = false;
				playerTurn = false;
				playerAttacking = false;
				combatLog.addToLog(chatText);
				textChange = true;
				update(rect);
			}

			if (didPlayerMove)
			{
				if (playerSteps <= ms.playerCharacter.getMoveSpeed())
				{
					QRect rect(0, ms.getMaxY()*resolution, resolution * minXReso*resolution, 50 * 3);
					string chatText = "You have ";
					chatText.append(std::to_string(ms.playerCharacter.getMoveSpeed() - playerSteps));
					chatText.append(" steps remaining.");

					if (playerSteps == ms.playerCharacter.getMoveSpeed())
					{
						chatText.append(" Attack (A), Loot Item (L) or End Turn (E)");
						playerMove = false;
					}

					combatLog.addToLog(chatText);
					textChange = true;
					update(rect);

					//Code if player reaches exit
					if (ms.getCurrentX() == ms.getEndX() && ms.getCurrentY() == ms.getEndY())
					{
						character pc = ms.playerCharacter;
						if (nextMap())
						{
							string file = Campaign.getMapFilename(Campaign.getCurrentMapId());
							string extension = "Maps/";
							ms.loadFromFile(extension.append(file));
							ms.playerCharacter = pc;
							resolution = checkResolution(ms.getMaxX(), ms.getMaxY());
							int windowResX = ms.getMaxX()*resolution;

							int windowDisplayHeightAdd = 3 * 50;
							int windowDisplayWidthMinimum = 12 * resolution;

							if (windowResX < windowDisplayWidthMinimum)
							{
								windowResX = windowDisplayWidthMinimum;
							}
							mainWindow->setFixedWidth(windowResX);
							mainWindow->setFixedHeight((ms.getMaxY()*resolution) + 20 + windowDisplayHeightAdd);

							start = true;
							update();
							mapStart = true;
						}
						else
						{
							message.setText("Congratulations! You have reached the end of the campaign!");
							message.exec();
						}
					}
				}
			}
		}
		//This handles the code if player enters a map for the first time
		else
		{
			npcTurn = 0;
			int pcInit = ms.playerCharacter.getInitiative();
			int roll = Dice::roll(1, 20, 0);

			QRect rect(0, ms.getMaxY()*resolution, resolution * minXReso*resolution, 50 * 3);
			string chatText = "You roll a d20. Result: ";
			chatText.append(std::to_string(roll));
			chatText.append(". Your initiative is ");
			chatText.append(std::to_string(roll+pcInit));
			chatText.append(" for this map.");

			combatLog.addToLog(chatText);
			textChange = true;
			update(rect);

			//Handling initiative order
			turnOrder.clear();
			int npcQuantity = ms.getNumberOfNPCs();

			vector<int> npcOrder;

			for (int i = 0; i < npcQuantity; i++)
			{
				ms.characterEntities[i].setCurrentInitiativeRoll(Dice::roll(1, 20, 0) + ms.characterEntities[i].getInitiative());
				npcOrder.push_back(ms.characterEntities[i].getCurrentInitiativeRoll());
			}

			int highestInit = -100;
			int highestCharacter;
			bool pcHighest = false;
			bool pcOrdered = false; //boolean to keep track if pc has been sorted
			int pcPosition;

			for (int index = 0; index < (npcQuantity + 1); index++)
			{
				highestInit = -100;
				highestCharacter = -1; //reset
				if (!pcOrdered)
				{
					highestInit = pcInit + roll;
					pcHighest = true;
				}
				for (int i = 0; i < npcQuantity; i++)
				{
					if (npcOrder[i] > highestInit)
					{
						highestInit = npcOrder[i];
						highestCharacter = i;
						pcHighest = false;
					}
				}
				if (pcHighest)
				{
					turnOrder.push_back(-1); //-1 signifies the player
					pcOrdered = true;
					pcPosition = index;
				}
				else
				{
					turnOrder.push_back(highestCharacter);
					npcOrder[highestCharacter] = -1;
				}
			}

			chatText = "You turn order: ";
			chatText.append(std::to_string(pcPosition+1));

			combatLog.addToLog(chatText);
			textChange = true;
			update(rect);

			if (pcPosition == 0)
			{
				playerTurn = true;
				playerMove = true;
			}
			else
			{
				playerTurn = false;
				playerMove = false;
			}
			playerSteps = 0;
			mapStart = false;
		}
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

void logic::changeEvent(QEvent * event)
{
	start = true;
	update();
}

void logic::focusOutEvent(QFocusEvent * event)
{
	start = true;
	update();
}

void logic::enterEvent(QEvent * event)
{
	start = true;
	update();
}

//This section is so that the user can see any size of map on screen (roughly) 100x100 max
//Reuse of method in editscreen
int logic::checkResolution(int w, int h)
{
	if (h > 80)
	{
		return 8;
	}
	if (h > 70)
	{
		return 10;
	}
	if (h > 50)
	{
		return 12;
	}
	if (w > 80 || h > 35)
	{
		return 15;
	}
	if (w > 70 || h > 30)
	{
		return 20;
	}
	if (w > 60 || h > 25)
	{
		return 25;
	}
	if (w > 50 || h > 20)
	{
		return 30;
	}
	if (w > 40 || h > 15)
	{
		return 35;
	}
	if (w > 30 || h > 12)
	{
		return 40;
	}
	return 50;
}

string logic::addItem() {
	//Add Interface to view backpack

	QDialog * d = new QDialog();
	d->setWindowTitle("Add Which Item?");
	QLabel *spaceLabel = new QLabel("");

	QVBoxLayout * vbox = new QVBoxLayout();

	QFile myTextFile("Resources/items.txt");
	QStringList myStringList;

	if (!myTextFile.open(QIODevice::ReadOnly))
	{
		QMessageBox::information(0, "Error opening file", myTextFile.errorString());
	}
	else
	{
		while (!myTextFile.atEnd())
		{
			myStringList.append(myTextFile.readLine());
		}
		myTextFile.close();
	}

	QListWidget * itemList = new QListWidget();

	itemList->addItems(myStringList);

	QDialogButtonBox * buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);
	buttonBox->button(QDialogButtonBox::Ok)->setText("Add");

	QObject::connect(buttonBox, SIGNAL(accepted()), d, SLOT(accept()));

	vbox->addWidget(itemList);

	vbox->addWidget(spaceLabel);
	vbox->addWidget(buttonBox);

	d->setLayout(vbox);

	int result = d->exec();
	if (result == QDialog::Accepted)
	{
		//Return to Game
		return itemList->currentItem()->text().toStdString();
	}
	return "";
}

void logic::viewItems()
{
	message.setText(QString::fromStdString(ms.viewItems()));
	message.exec();
}
