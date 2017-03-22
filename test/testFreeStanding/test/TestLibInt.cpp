/*The MIT License (MIT)

Copyright (c) 2017 k-brac

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
/**
* Switch betwenn member and static operator<< for serializing.
* Usefull if both are defined
*/
//#define CUTI_USE_MEMBER_SERIALIZE

/**
* Prepend test_ to all function declared using CUTI_TEST in XCode.
* Indeed XCode needs the prefix "test" to automatically detect test methods
*/
#define CUTI_PREPEND_TEST
#include "Cuti.h"
#undef CUTI_PREPEND_TEST
#include "ComputeInt.h"

inline std::ostringstream& operator<<(std::ostringstream& os, const ComputeInt&) {
    os << "ComputeInt val";
    return os;
}

CUTI_DEFAULT_TO_STRING(ComputeInt);

CUTI_TEST_CLASS(TestLibInt){
public:
	void simpleAssertTest() {
		ComputeInt c(5);
		CUTI_ASSERT(c.add(-2) != 0);
		CUTI_ASSERT(c.add(-2) != 0, "c.add should have returned a value != 0");
	}

	void assertThrowTest() {
		ComputeInt c(1);
		CUTI_ASSERT_THROW(c.divide(0), std::runtime_error);
		CUTI_ASSERT_THROW(c.divide(0), std::runtime_error, "Tried to divide by 0");
		//CUTI_ASSERT_ASSERTION_FAIL(CUTI_ASSERT_THROW(c.divide(0), std::logic_error));
	}
	
	void assertNoThrowTest() {
		ComputeInt c(1);
		CUTI_ASSERT_NO_THROW(c.divide(1));
		CUTI_ASSERT_NO_THROW(c.divide(1), "Should not have thrown");
		//CUTI_ASSERT_ASSERTION_FAIL(CUTI_ASSERT_NO_THROW(c.divide(0)));
	}

	void assertFailTest() {
			//CUTI_ASSERT_ASSERTION_FAIL(CUTI_FAIL("This test has failed"));
	}

    
	void assertLessTest() {
		ComputeInt c(5);
		//CUTI_ASSERT_ASSERTION_FAIL(CUTI_ASSERT_LESS(10, c.add(5)));
		CUTI_ASSERT_LESS(10, c.add(1));
		CUTI_ASSERT_LESSEQUAL(10, c.add(5));
		CUTI_ASSERT_LESSEQUAL(10, c.add(1));
		//CUTI_ASSERT_ASSERTION_FAIL(CUTI_ASSERT_LESSEQUAL(10, c.add(6)));
	}

	void assertGreaterTest() {
		ComputeInt c(5);
		//CUTI_ASSERT_ASSERTION_FAIL(CUTI_ASSERT_GREATER(11, c.add(5)));
		CUTI_ASSERT_GREATER(1, c.add(1));
		CUTI_ASSERT_GREATEREQUAL(1, c.add(5));
		CUTI_ASSERT_GREATEREQUAL(10, c.add(6));
		//CUTI_ASSERT_ASSERTION_FAIL(CUTI_ASSERT_GREATEREQUAL(10, c.add(1)));
	}

	void assertEqual() {
		ComputeInt c(5);
        ComputeInt c2(6);
		CUTI_ASSERT_EQUAL(5, c.add(0), "Should be equal");
		CUTI_ASSERT_EQUAL(5, c.add(0));
		//CUTI_ASSERT_ASSERTION_FAIL(CUTI_ASSERT_EQUAL(10, c.add(1)));
        CUTI_ASSERT_EQUAL(c, c2);
	}

    CUTI_BEGIN_TESTS_REGISTRATION(TestLibInt);
    CUTI_TEST(simpleAssertTest);
    CUTI_TEST(assertThrowTest);
    CUTI_TEST(assertNoThrowTest);
    CUTI_TEST(assertFailTest);
    CUTI_TEST(assertLessTest);
    CUTI_TEST(assertGreaterTest);
    CUTI_TEST(assertEqual);
    CUTI_END_TESTS_REGISTRATION();//must be the last statement in the class
};
