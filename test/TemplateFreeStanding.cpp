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
* Mandatory include. Should always be on top
*/
#include "Cuti.h"

/**
* Declare a test class allowing for standalone or integrated test runner
*/
TEST_CLASS(TemplateFreeStanding) {
private:
    bool val = false;
public:
    /**
    * Optional. Executed before every test case
    */
    SET_UP() {
        val = true;
    }

    /**
    * Optional. Executed after every test case
    */
    TEAR_DOWN() {
        val = false;
    }

    void testSimpleAssert() {
        ASSERT(val);
    }
    /**
     * Test suit declaration and test case registration
     */
    BEGIN_TESTS_REGISTRATION(TemplateFreeStanding);
    TEST(testSimpleAssert);
    END_TESTS_REGISTRATION();//must be the last statement in the class
};

