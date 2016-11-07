/*
Author: Alexis Grondin
Id : 26639569
Course : COMP 345
Assignment 2 Part 2 : Character Observer

Character controller cpp file
*/



#include "characterController.h"
#include <iostream>
#include <qdebug.h>



characterController::characterController(character* mod)
{
	toModify = mod;
}


characterController::~characterController()
{
}

void characterController::setCharacterName() {
	toModify->setName("Zaxaras");

	qDebug("Hello");
}

void characterController::levelUpCharacter()
{
	toModify->levelUp(1);


	qDebug("Hello");
}
