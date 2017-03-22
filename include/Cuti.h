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

#ifndef CPP_UNIT_TEST_INTEGRATED
#define CPP_UNIT_TEST_INTEGRATED

/**
* Uses only cuti's macros
*/
#if defined(CUTI_FREE_STANDING)

#include "CutiFreeStanding.h"

/**
* Compatibility mode to allow the use of cuti as backend and cuppunit as frontend
*/
#elif defined(CUTI_CPPUNIT_COMPATABILITY)

#include "CutiFreeStanding.h"

#define CPPUNIT_TEST_SUITE(className) CUTI_BEGIN_TESTS_REGISTRATION(className)

#define CPPUNIT_TEST(testMethod) CUTI_TEST(testMethod)

#define CPPUNIT_TEST_SUITE_END() CUTI_END_TESTS_REGISTRATION()

#define CPPUNIT_FAIL(message) CUTI_FAIL(message)

#define CPPUNIT_ASSERT_MESSAGE(message,condition) CUTI_ASSERT(condition, message)

#define CPPUNIT_ASSERT(condition) CUTI_ASSERT(condition)

#define CPPUNIT_ASSERT_THROW_MESSAGE(message, expression, ExceptionType) CUTI_ASSERT_THROW(expression, ExceptionType, message)

#define CPPUNIT_ASSERT_THROW(expression, ExceptionType) CUTI_ASSERT_THROW(expression, ExceptionType)

#define CPPUNIT_ASSERT_NO_THROW_MESSAGE(message, expression) CUTI_ASSERT_NO_THROW(expression, message)

#define CPPUNIT_ASSERT_NO_THROW(expression) CUTI_ASSERT_NO_THROW(expression)

#define CPPUNIT_ASSERT_LESS(expected,actual) CUTI_ASSERT_LESS(expected, actual)

#define CPPUNIT_ASSERT_LESSEQUAL(expected, actual) CUTI_ASSERT_LESSEQUAL(expected, actual)

#define CPPUNIT_ASSERT_GREATER(expected,actual) CUTI_ASSERT_GREATER(expected, actual)

#define CPPUNIT_ASSERT_GREATEREQUAL(expected, actual) CUTI_ASSERT_GREATEREQUAL(expected, actual)

#define CPPUNIT_ASSERT_EQUAL_MESSAGE(message,expected,actual) CUTI_ASSERT_EQUAL(expected, actual, message)

#define CPPUNIT_ASSERT_EQUAL(expected,actual) CUTI_ASSERT_EQUAL(expected, actual)

#define CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE(message, expected, actual, delta) CUTI_ASSERT_DOUBLES_EQUAL(expected, actual, delta, message)

#define CPPUNIT_ASSERT_DOUBLES_EQUAL(expected, actual, delta) CUTI_ASSERT_DOUBLES_EQUAL(expected, actual, delta)

#if defined(CUTI_EXCLUDE_TEST_FROM_COVERAGE) && defined(_WIN32)
#include <CodeCoverage/CodeCoverage.h>
/**
* Compatibility for cppunit test suite registration
* Can exclude test suite from code coverage
*/
#define CPPUNIT_TEST_SUITE_REGISTRATION(className) ExcludeFromCodeCoverage(className, L#className L"::*"); \
static_assert(std::is_same<className, ::className>::value, "CPPUNIT_TEST_SUITE_REGISTRATION(" #className ") must be declared in the global namespace")
#else
#define CPPUNIT_TEST_SUITE_REGISTRATION(className) static_assert(std::is_same<className, ::className>::value, "CPPUNIT_TEST_SUITE_REGISTRATION(" #className ") must be declared in the global namespace")
#endif

#elif defined(CUTI_NO_INTEGRATION)

#ifdef _MSC_VER
#include <Windows.h>
#pragma warning( push )
#pragma warning( disable : 4251 )
#pragma warning( disable : 4512 )
#pragma warning( disable : 4275 )
#endif

#ifndef CPPUNIT_UNIQUE_COUNTER
# define CPPUNIT_UNIQUE_COUNTER __COUNTER__
#endif

#include "cppunit/plugin/TestPlugIn.h"
#include <cppunit/extensions/HelperMacros.h>

#ifdef _MSC_VER
#pragma warning( pop )
#endif
/**
* Declare a test fixture
*/
#define CUTI_TEST_CLASS(className) class className : public CppUnit::TestFixture
/**
* Function initializing a test case
*/
#define CUTI_SET_UP() virtual void setUp() override
/**
* Function cleaning up a test case
*/
#define CUTI_TEAR_DOWN() virtual void tearDown() override

#ifdef CUTI_USES_XCTEST_BACKEND
/**
* The specificities of XCode's integration are in their own file for lisibility
*/
#include "CutiXCode.h"

#endif

#endif

#endif //CPP_UNIT_TEST_INTEGRATED
