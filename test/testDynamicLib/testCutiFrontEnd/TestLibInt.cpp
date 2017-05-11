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
* Prepend test_ to all function declared using CUTI_TEST in XCode.
* Indeed XCode needs the prefix "test" to automatically detect test methods
*/
#define CUTI_PREPEND_TEST
#include "Cuti.h"
#undef CUTI_PREPEND_TEST
#include "ComputeInt.h"

TEST_CLASS(TestLibInt) {
public:
    void simpleAssertTest() {
        ComputeInt c(5);
        ASSERT(c.add(-2) != 0);
        ASSERT(c.add(-2) != 0, "c.add should have returned a value != 0");
    }

    void assertThrowTest() {
        ComputeInt c(1);
        ASSERT_THROW(c.divide(0), std::runtime_error);
        ASSERT_THROW(c.divide(0), std::runtime_error, "Tried to divide by 0");
    }

    void assertNoThrowTest() {
        ComputeInt c(1);
        ASSERT_NO_THROW(c.divide(1));
        ASSERT_NO_THROW(c.divide(1), "Should not have thrown");
    }

    void assertFailTest() {
        uint16_t a = 0, b = 0;
        ASSERT_EQUAL(a, b);
    }

    void assertLessTest() {
        ComputeInt c(5);
        ASSERT_LESS(10, c.add(1));
        ASSERT_LESSEQUAL(10, c.add(5));
        ASSERT_LESSEQUAL(10, c.add(1));
    }

    void assertGreaterTest() {
        ComputeInt c(5);
        ASSERT_GREATER(1, c.add(1));
        ASSERT_GREATEREQUAL(1, c.add(5));
        ASSERT_GREATEREQUAL(10, c.add(6));
    }

    void assertEqual() {
        ComputeInt c(5);
        ComputeInt c2(5);
        ASSERT_EQUAL(5, c.add(0), "Should be equal");
        ASSERT_EQUAL(5, c.add(0));
        //ASSERT_EQUAL(c, c2);
    }

    BEGIN_TESTS_REGISTRATION(TestLibInt);
    TEST(simpleAssertTest);
    TEST(assertThrowTest);
    TEST(assertNoThrowTest);
    TEST(assertFailTest);
    TEST(assertLessTest);
    TEST(assertGreaterTest);
    TEST(assertEqual);
    END_TESTS_REGISTRATION();//must be the last statement in the class
};
