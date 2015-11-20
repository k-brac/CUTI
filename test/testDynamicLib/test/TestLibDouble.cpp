#include "Cuti.h"
#include "ComputeDouble.h"

CUTI_TEST_CLASS(TestLibDouble) {
public:
	CPPUNIT_TEST_SUITE(TestLibDouble);
	CPPUNIT_TEST(doubleAssertTest);
	CPPUNIT_TEST_SUITE_END();

public:

	void doubleAssertTest() {
		ComputeDouble c(5.);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(1.66, c.divide(3.), 0.01);
		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("c.divide should have been equal to 1.6", 1.66, c.divide(3), 0.01);
	}

};
CPPUNIT_TEST_SUITE_REGISTRATION(TestLibDouble);
CUTI_EXCLUDE_FROM_COVERAGE(TestLibDouble, L"TestLibDouble::*");
