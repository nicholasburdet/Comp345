/*

Author: Alexis Grondin
Id : 26639569
Course : COMP 345
Assignment 2 Part 2 : Character Observer

Character observer cpp file

The main driver will invoke the QT application and creates a
main window for the character stats to be displayed

A character is created, and a character observer is attached to it.

A character controller modifies values in the character, which will notify the observer, thus updating the display.

A QTimer is used to trigger the character controller. 

The QT framework was used for the GUI portion, because of its simplicity and flat learning curve.

See character.h for a description of the DnD rules used in the implementation, and more information on the design

*/

//#include "testqt.h"
#include "editscreen.h"
#include <windows.h>
#include "characterObserver.h"
#include "characterController.h"
#include "iostream"
#include "character.h"
#include <QtWidgets/QApplication>
#include <QTimer>
#include <QDebug>
#include <QInputDialog>
#include <QtWidgets/qmainwindow.h>
#include "cppunit/TestCase.h"
#include "cppunit/TestFixture.h"	
#include "cppunit/ui/text/TextTestRunner.h"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include "Q_DebugStream.h"

using namespace CppUnit;

int main(int argc, char *argv[])
{
	//First run unit tests


	QApplication a(argc, argv);


	Q_DebugStream cerr(std::cerr);

	CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

	CppUnit::TextUi::TestRunner runner;
	runner.addTest(suite);

	runner.setOutputter(new CppUnit::CompilerOutputter(&runner.result(),
		std::cerr));

	bool wasSuccessful = runner.run();
	
	character* goron = new character(1, "Goron", 5, "");

	characterObserver* charTable = new characterObserver(NULL, goron);

	characterController* driver = new  characterController(goron);

	QTimer::singleShot(10000, driver, SLOT(setCharacterName()));
	QTimer::singleShot(20000, driver, SLOT(levelUpCharacter()));

	charTable->show();

	return a.exec();
}
