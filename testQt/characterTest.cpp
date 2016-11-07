
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>
#include "character.h"
#include "characterObserver.h"

using namespace CppUnit;
using namespace std;


class characterTest : public CppUnit::TestFixture
{

	CPPUNIT_TEST_SUITE(characterTest);//declare the test suite
	CPPUNIT_TEST(testAttachObserver);//test the AddItem method
	CPPUNIT_TEST(testDetachObserver);//test the removeItem method
	CPPUNIT_TEST_SUITE_END();//end of test suite declaration

public:

	void setUp(void);
	void tearDown(void);

protected:
	void testAttachObserver(void);
	void testDetachObserver(void);
private:

	character *npc;
	characterObserver *observer;
};

//Register for running the test

CPPUNIT_TEST_SUITE_REGISTRATION(characterTest);

/*!
Tests if an observer, once attached to a character, is contained in his observer set.
 */
void characterTest::testAttachObserver(void)
{

	observer=new characterObserver(NULL, npc);

	CPPUNIT_ASSERT(npc->isAttached(observer));
}

/*!
Tests if an observers, once detached from a subject, is no longer contained in its observers
*/
void characterTest::testDetachObserver(void)
{
	npc->removeObserver(*observer);
	CPPUNIT_ASSERT(!npc->isAttached(observer));
}

void characterTest::setUp(void)
{

	npc = new character(2, "Garak", 4, "");
}

void characterTest::tearDown(void)
{


}
