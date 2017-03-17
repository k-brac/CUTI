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
#include <string>


/**
 * Declare a test fixture
 */
#define IMPL_CUTI_TEST_CLASS(className) \
struct className; /*forward declaration*/ \
@interface C##className : XCTestCase {\
} \
@end \
static className * kInstance = nullptr; \
@implementation C##className \
struct className : public cuti::CutiBaseTestCase

/**
 * Defines a setup method to run before each test case
 */
#define IMPL_CUTI_SET_UP() virtual void setUp() override final

/**
 * Defines a tear down method to run after each test case
 */
#define IMPL_CUTI_TEAR_DOWN() virtual void tearDown() override final

#if defined(CUTI_PREPEND_TEST)
/**
 * Add testMethod to the test suite
 * prepend test_ to testMethof if CUTI_PREPEND_TEST is defined
 */
#define IMPL_CUTI_TEST(testMethod) \
- (void)test_##testMethod { \
    kInstance->testMethod(); \
}
#else
/**
 * Add testMethod to the test suite
 * prepend test_ to testMethof if CUTI_PREPEND_TEST is defined
 */
#define IMPL_CUTI_TEST(testMethod) \
- (void) testMethod { \
    kInstance->testMethod(); \
}
#endif

/**
 * Delimits the beginning of the tests registration
 */
#define IMPL_CUTI_BEGIN_TESTS_REGISTRATION(className) }; \
+ (void)setUp { \
    [super setUp]; \
    kInstance = new className(); \
} \
+ (void)tearDown { \
    delete kInstance; \
    [super tearDown]; \
} \
- (void)setUp { \
    [super setUp]; \
    self.continueAfterFailure = NO; \
    kInstance->self = self; \
    kInstance->setUp(); \
} \
- (void)tearDown { \
    kInstance->tearDown(); \
    [super tearDown]; \
}

/**
 * Mandatory last statement of a test class
 */
#define IMPL_CUTI_END_TESTS_REGISTRATION() \
@end \
namespace {

/*****************
 * CUTI internals*
 *****************/

namespace cuti {
    struct CutiBaseTestCase {
        XCTestCase * self = NULL;
        virtual void setUp() {}
        virtual void tearDown() {}
        virtual ~CutiBaseTestCase() = default;
    };
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-function"
    static std::string CutiGetFormatMessage(std::string msg = std::string()) { return msg;}
#pragma clang diagnostic pop
};

#define INTERNAL_CUTI_FORMAT_MESSAGE() @"%@", @(cutiMsg_.c_str())

#define INTERNAL_CUTI_ASSERT_MESSAGE(expression, ...) do { const auto cutiMsg_ = cuti::CutiGetFormatMessage(__VA_ARGS__); expression; } while(false)

/******************************************
 * XCode CUTI assert macro implementations*
 ******************************************/

#define IMPL_CUTI_ASSERT(condition, ...) INTERNAL_CUTI_ASSERT_MESSAGE(XCTAssert(condition, INTERNAL_CUTI_FORMAT_MESSAGE()), __VA_ARGS__)

#define IMPL_CUTI_FAIL( ... ) INTERNAL_CUTI_ASSERT_MESSAGE(XCTFail(INTERNAL_CUTI_FORMAT_MESSAGE()), __VA_ARGS__)

#define IMPL_CUTI_ASSERT_EQUAL(expected,actual, ...) INTERNAL_CUTI_ASSERT_MESSAGE(XCTAssertEqual(actual, expected, INTERNAL_CUTI_FORMAT_MESSAGE()), __VA_ARGS__)

#define IMPL_CUTI_ASSERT_LESS(bound, actual, ...) INTERNAL_CUTI_ASSERT_MESSAGE(XCTAssertLessThan(actual, bound, INTERNAL_CUTI_FORMAT_MESSAGE()), __VA_ARGS__)

#define IMPL_CUTI_ASSERT_GREATER(bound, actual, ...) INTERNAL_CUTI_ASSERT_MESSAGE(XCTAssertGreaterThan(actual, bound, INTERNAL_CUTI_FORMAT_MESSAGE()), __VA_ARGS__)

#define IMPL_CUTI_ASSERT_LESSEQUAL(bound, actual, ...) INTERNAL_CUTI_ASSERT_MESSAGE(XCTAssertLessThanOrEqual(actual, bound, INTERNAL_CUTI_FORMAT_MESSAGE()), __VA_ARGS__)

#define IMPL_CUTI_ASSERT_GREATEREQUAL(bound, actual, ...)  INTERNAL_CUTI_ASSERT_MESSAGE(XCTAssertGreaterThanOrEqual(actual, bound, INTERNAL_CUTI_FORMAT_MESSAGE()), __VA_ARGS__)

#define IMPL_CUTI_ASSERT_DOUBLES_EQUAL(expected,actual,delta, ...) INTERNAL_CUTI_ASSERT_MESSAGE(XCTAssertEqualWithAccuracy(actual, expected, delta, INTERNAL_CUTI_FORMAT_MESSAGE()), __VA_ARGS__)

#define IMPL_CUTI_ASSERT_THROW( expression, ExceptionType, ... ) \
do { \
    bool cpputCorrectExceptionThrown_ = false; \
    std::string cutiMsgT_( "expected exception not thrown. " ); \
    cutiMsgT_ += "Expected: " #ExceptionType ". "; \
\
    try { \
        expression; \
    } catch ( const ExceptionType & ) { \
        cpputCorrectExceptionThrown_ = true; \
    } catch ( const std::exception &e) { \
        cutiMsgT_ += std::string("Actual  : ") + std::string(typeid(e).name());\
        cutiMsgT_ += std::string(". What()  : ") + e.what();\
    } catch ( ... ) { \
        cutiMsgT_ += ( "Actual  : unknown."); \
    } \
\
    if ( cpputCorrectExceptionThrown_ )\
    break; \
    cutiMsgT_ += std::string(". ") + cuti::CutiGetFormatMessage(__VA_ARGS__); \
    CUTI_FAIL( cutiMsgT_); \
} while ( false )



#endif

/*******************
 * Public interface*
 *******************/

/**
 * Declare a test fixture
 */
#define CUTI_TEST_CLASS(className) IMPL_CUTI_TEST_CLASS(className)

/**
 * Defines a setup method to run before each test case
 */
#define CUTI_SET_UP() IMPL_CUTI_SET_UP()

/**
 * Defines a tear down method to run after each test case
 */
#define CUTI_TEAR_DOWN() IMPL_CUTI_TEAR_DOWN()

/**
 * Add testMethod to the test suite
 * prepend test_ to testMethof if CUTI_PREPEND_TEST is defined
 */
#define CUTI_TEST(testMethod) IMPL_CUTI_TEST(testMethod)

/**
 * Delimits the beginning of the tests registration
 */
#define CUTI_BEGIN_TESTS_REGISTRATION(className) IMPL_CUTI_BEGIN_TESTS_REGISTRATION(className)

/**
 * Mandatory last statement of a test class
 */
#define CUTI_END_TESTS_REGISTRATION() IMPL_CUTI_END_TESTS_REGISTRATION()

/***********************
 * Public assert macros*
 ***********************/

#define CUTI_ASSERT(condition, ...) IMPL_CUTI_ASSERT(condition, __VA_ARGS__)

#define CUTI_FAIL( ... ) IMPL_CUTI_FAIL( __VA_ARGS__ )

#define CUTI_ASSERT_EQUAL(expected,actual, ...) IMPL_CUTI_ASSERT_EQUAL(expected,actual, __VA_ARGS__)

#define CUTI_ASSERT_LESS(bound, actual, ...) IMPL_CUTI_ASSERT_LESS(bound, actual, __VA_ARGS__)

#define CUTI_ASSERT_GREATER(bound, actual, ...) IMPL_CUTI_ASSERT_GREATER(bound, actual, __VA_ARGS__)

#define CUTI_ASSERT_LESSEQUAL(bound, actual, ...) IMPL_CUTI_ASSERT_LESSEQUAL(bound, actual, __VA_ARGS__)

#define CUTI_ASSERT_GREATEREQUAL(bound, actual, ...)  IMPL_CUTI_ASSERT_GREATEREQUAL(bound, actual, __VA_ARGS__)

#define CUTI_ASSERT_DOUBLES_EQUAL(expected,actual,delta, ...) IMPL_CUTI_ASSERT_DOUBLES_EQUAL(expected,actual,delta, __VA_ARGS__)

#define CUTI_ASSERT_THROW( expression, ExceptionType, ... ) IMPL_CUTI_ASSERT_THROW( expression, ExceptionType, __VA_ARGS__)

# define CUTI_ASSERT_NO_THROW( expression, ... ) \
do { \
    try {\
        expression;\
    } catch (std::exception &e) {\
        CUTI_FAIL( std::string("Caught: std::exception or derived. What() : ") + e.what() + std::string(". ") + cuti::CutiGetFormatMessage(__VA_ARGS__));\
    } catch (...) {\
        CUTI_FAIL(std::string("Unexpected exception caught. " + cuti::CutiGetFormatMessage(__VA_ARGS__)));\
    } \
} while(false)

#endif
