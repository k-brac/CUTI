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
#define CUTI_USE_LONG_MACRO_NAME
#include "Cuti.h"
#undef CUTI_USE_LONG_MACRO_NAME
#include "ComputeDouble.h"

CUTI_TEST_CLASS(TestLibDouble) {
public:
	void testDoubleAssert() {
		ComputeDouble c(5.);
		CUTI_ASSERT_DOUBLES_EQUAL(1.66, c.divide(3.), 0.01);
		CUTI_ASSERT_DOUBLES_EQUAL(1.66, c.divide(3), 0.01, "c.divide should have been equal to 1.6");
	}

    CUTI_BEGIN_TESTS_REGISTRATION(TestLibDouble);
    CUTI_TEST(testDoubleAssert);
    CUTI_END_TESTS_REGISTRATION();//must be the last statement in the class
};
