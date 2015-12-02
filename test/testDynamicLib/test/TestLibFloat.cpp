#include "Cuti.h"
#include "ComputeFloat.h"

CUTI_TEST_CLASS(TestLibFloat){
public:
	CPPUNIT_TEST_SUITE(TestLibFloat);
	CPPUNIT_TEST(floatAssertTest);
	CPPUNIT_TEST_SUITE_END();

public:

	void floatAssertTest() {
		ComputeFloat c(5.f);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(1.66f, c.divide(3.f), 0.01f);
		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("c.divide should have been equal to 1.6", 1.66f, c.divide(3.f), 0.01f);
	}
};
CPPUNIT_TEST_SUITE_REGISTRATION(TestLibFloat);
