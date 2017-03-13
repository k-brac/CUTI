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

#ifndef CPP_UNIT_TEST_INTEGRATED_FREE_STANDING
#define CPP_UNIT_TEST_INTEGRATED_FREE_STANDING

#ifdef _MSC_VER
//Visual studio's backend is already free standing
/**
* The specificities of visual studio's integration are in their own file for lisibility
*/
#include "CutiVisualStudio.h"

#else
//XCode specific backend
#import <Foundation/Foundation.h>
#import <XCTest/XCTest.h>
#import <objc/runtime.h>

/**
 * Declare a test fixture
 */
#define CUTI_TEST_CLASS(className) \
@interface C##className : XCTestCase \
@end \
@implementation C##className \

/**
 * Defines a setup method to run before each test case
 */
#define CUTI_SET_UP(className) void setUp##className(); \
- (void)setUp { \
[super setUp]; \
setUp##className(); \
} \
void setUp##className()

/**
 * Defines a tear down method to run after each test case
 */
#define CUTI_TEAR_DOWN(className) void tearDown##className(); \
- (void)tearDown { \
[super tearDown]; \
tearDown##className(); \
} \
void tearDown##className()


#if defined(CUTI_PREPEND_TEST)
/**
 * Add testMethod to the test suite
 * prepend test_ to testMethof if CUTI_PREPEND_TEST is defined
 */
#define CUTI_TEST(testMethod) \
- (void)test_##testMethod { \
testMethod(); \
}
#else
/**
 * Add testMethod to the test suite
 * prepend test_ to testMethof if CUTI_PREPEND_TEST is defined
 */
#define CUTI_TEST(testMethod) \
- (void) testMethod { \
testMethod(); \
}
#endif


/**
 * Mandatory first statement of a test class
 */
#define CUTI_BEGIN_TEST_DECLARATION() }

/**
 * Mandatory last statement of a test class
 */
#define CUTI_END_TEST_DECLARATION() \
@end \
namespace {

#endif

#endif
