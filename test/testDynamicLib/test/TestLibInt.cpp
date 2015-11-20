#include "Cuti.h"
#include "ComputeInt.h"

CUTI_TEST_CLASS(TestLibInt){
public:
	CPPUNIT_TEST_SUITE(TestLibInt);
	CPPUNIT_TEST(simpleAssertTest);
	CPPUNIT_TEST(assertThrowTest);
	CPPUNIT_TEST(assertNoThrowTest);
	CPPUNIT_TEST(assertFailTest);
	CPPUNIT_TEST(assertLessTest);
	CPPUNIT_TEST(assertGreaterTest);
	CPPUNIT_TEST(assertEqual);
	CPPUNIT_TEST_SUITE_END();

public:
	CUTI_SET_UP(){
	}

	CUTI_TEAR_DOWN() {
	}

	void simpleAssertTest() {
		ComputeInt c(5);
		CPPUNIT_ASSERT(c.add(-2) != 0);
		CPPUNIT_ASSERT_MESSAGE("c.add should have returned a value != 0", c.add(-2) != 0);
	}

	void assertThrowTest() {
		ComputeInt c(1);
		CPPUNIT_ASSERT_THROW(c.divide(0), std::runtime_error);
		CPPUNIT_ASSERT_THROW_MESSAGE("Tried to divide by 0", c.divide(0), std::runtime_error);
		CPPUNIT_ASSERT_ASSERTION_FAIL(CPPUNIT_ASSERT_THROW(c.divide(0), std::logic_error));
	}
	
	void assertNoThrowTest() {
		ComputeInt c(1);
		CPPUNIT_ASSERT_NO_THROW(c.divide(1));
		CPPUNIT_ASSERT_NO_THROW_MESSAGE("Should not have thrown", c.divide(1));
		CPPUNIT_ASSERT_ASSERTION_FAIL(CPPUNIT_ASSERT_NO_THROW(c.divide(0)));
	}

	void assertFailTest() {
			CPPUNIT_ASSERT_ASSERTION_FAIL(CPPUNIT_FAIL("This test has failed"));
	}

	void assertLessTest() {
		ComputeInt c(5);
		CPPUNIT_ASSERT_ASSERTION_FAIL(CPPUNIT_ASSERT_LESS(10, c.add(5)));
		CPPUNIT_ASSERT_LESS(10, c.add(1));
		CPPUNIT_ASSERT_LESSEQUAL(10, c.add(5));
		CPPUNIT_ASSERT_LESSEQUAL(10, c.add(1));
		CPPUNIT_ASSERT_ASSERTION_FAIL(CPPUNIT_ASSERT_LESSEQUAL(10, c.add(6)));
	}

	void assertGreaterTest() {
		ComputeInt c(5);
		CPPUNIT_ASSERT_ASSERTION_FAIL(CPPUNIT_ASSERT_GREATER(11, c.add(5)));
		CPPUNIT_ASSERT_GREATER(1, c.add(1));
		CPPUNIT_ASSERT_GREATEREQUAL(10, c.add(5));
		CPPUNIT_ASSERT_GREATEREQUAL(10, c.add(6));
		CPPUNIT_ASSERT_ASSERTION_FAIL(CPPUNIT_ASSERT_GREATEREQUAL(10, c.add(1)));
	}

	void assertEqual() {
		ComputeInt c(5);
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Should be equal", 5, c.add(0));
		CPPUNIT_ASSERT_EQUAL(5, c.add(0));
		CPPUNIT_ASSERT_ASSERTION_FAIL(CPPUNIT_ASSERT_EQUAL(10, c.add(1)));
	}
};
CPPUNIT_TEST_SUITE_REGISTRATION(TestLibInt);

CUTI_EXCLUDE_FROM_COVERAGE(TestLibInt, L"TestLibInt::*");
