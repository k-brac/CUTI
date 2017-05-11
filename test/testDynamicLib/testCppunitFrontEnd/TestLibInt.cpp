/*The MIT License (MIT)

Copyright (c) 2015 k-brac

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#define CUTI_PREPEND_TEST
#include "Cuti.h"
#undef CUTI_PREPEND_TEST
#include "ComputeInt.h"

TEST_CLASS(TestLibInt){
public:

	void simpleAssertTest() {
		ComputeInt c(5);
		CPPUNIT_ASSERT(c.add(-2) != 0);
		CPPUNIT_ASSERT_MESSAGE("c.add should have returned a value != 0", c.add(-2) != 0);
	}

	void assertThrowTest() {
		ComputeInt c(1);
		CPPUNIT_ASSERT_THROW(c.divide(0), std::runtime_error);
		CPPUNIT_ASSERT_THROW_MESSAGE("Tried to divide by 0", c.divide(0), std::runtime_error);
	}
	
	void assertNoThrowTest() {
		ComputeInt c(1);
		CPPUNIT_ASSERT_NO_THROW(c.divide(1));
		CPPUNIT_ASSERT_NO_THROW_MESSAGE("Should not have thrown", c.divide(1));
	}

	void assertFailTest() {
			//CPPUNIT_ASSERT_ASSERTION_FAIL(CPPUNIT_FAIL("This test has failed"));
	}

	void assertLessTest() {
		ComputeInt c(5);
		CPPUNIT_ASSERT_LESS(10, c.add(1));
		CPPUNIT_ASSERT_LESSEQUAL(10, c.add(5));
		CPPUNIT_ASSERT_LESSEQUAL(10, c.add(1));
	}

	void assertGreaterTest() {
		ComputeInt c(5);
		CPPUNIT_ASSERT_GREATER(1, c.add(1));
		CPPUNIT_ASSERT_GREATEREQUAL(10, c.add(5));
		CPPUNIT_ASSERT_GREATEREQUAL(10, c.add(6));
	}

	void assertEqual() {
		ComputeInt c(5);
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Should be equal", 5, c.add(0));
		CPPUNIT_ASSERT_EQUAL(5, c.add(0));
	}

    CPPUNIT_TEST_SUITE(TestLibInt);
    CPPUNIT_TEST(simpleAssertTest);
    CPPUNIT_TEST(assertThrowTest);
    CPPUNIT_TEST(assertNoThrowTest);
    CPPUNIT_TEST(assertFailTest);
    CPPUNIT_TEST(assertLessTest);
    CPPUNIT_TEST(assertGreaterTest);
    CPPUNIT_TEST(assertEqual);
    CPPUNIT_TEST_SUITE_END();
};
