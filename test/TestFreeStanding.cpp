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
#define CUTI_FREE_STANDING
#include "Cuti.h"

#include <iostream>

class Truc {
public:
    void p() {
        std::cout << "p" << std::endl;
    }
};

CUTI_TEST_CLASS(TestFreeStanding) {
    //must be the first statement in the class
    CUTI_BEGIN_TEST_DECLARATION()
    CUTI_TEST(testhello)

    CUTI_SET_UP(TestFreeStanding) {
        std::cout << "setup" << std::endl;
    }

    CUTI_TEAR_DOWN(TestFreeStanding) {
        std::cout << "teardown" << std::endl;
    }
    //private field
    Truc t;
    //test implementation
    void testhello() {
        std::cout << "hello" << std::endl;
        t.p();
    }
//must be the last statement in the class
CUTI_END_TEST_DECLARATION()
};
