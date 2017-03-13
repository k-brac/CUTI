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

#ifdef CUTI_FREE_STANDING

#include "CutiFreeStanding.h"

#elif CUTI_USES_MSVC_UNIT_BACKEND
/**
* The specificities of visual studio's integration are in their own file for lisibility
*/
#include "CutiVisualStudio.h"

#else
#ifndef CUTI_USES_CPPUNIT_BACKEND
#define CUTI_USES_CPPUNIT_BACKEND
#endif
#ifndef CPPUNIT_DLL
#define CPPUNIT_DLL
#endif
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

#endif
