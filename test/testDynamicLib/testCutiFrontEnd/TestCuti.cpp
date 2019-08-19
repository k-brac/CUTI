/*The MIT License (MIT)

Copyright (c) 2019 k-brac

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

#include "Cuti.h"

/**
* A class that can be initialized only once
*/
class SingleInit {
    bool is_init = false;
public:
    bool initialize() {
        if (is_init) {
            throw std::runtime_error("Already initialized");
        }
        is_init = true;
        return true;
    }
};

TEST_CLASS(TestCuti) {
public:

    void testSingleEvaluateInMacro() {
        SingleInit si;
        SingleInit si_expected;
        ASSERT_EQUAL(si_expected.initialize(), si.initialize());
    }

    BEGIN_TESTS_REGISTRATION(TestCuti);
    TEST(testSingleEvaluateInMacro);
    END_TESTS_REGISTRATION();//must be the last statement in the class
};
