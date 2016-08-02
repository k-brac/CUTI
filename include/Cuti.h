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

#ifdef CUTI_USES_MSVC_UNIT_BACKEND
#ifdef WIN32
#include <CppUnitTest.h>
#include <codecvt>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#ifdef CUTI_EXCLUDE_TEST_FROM_COVERAGE
#include <CodeCoverage/CodeCoverage.h>
/**
* Compatibility for cppunit test suite registration
* Can exclude test suite from code coverage
*/
#define CPPUNIT_TEST_SUITE_REGISTRATION(className) ExcludeFromCodeCoverage(className, L#className L"::*")
#else
#define CPPUNIT_TEST_SUITE_REGISTRATION(className)
#endif

namespace cuti {
    /**
    * Contains cuti's helper functions
    */
    class CutiTestHelper {
    public:
        /**
        * Converts string to wide string
        * @param s The string to be converted
        * @return s as a wide string
        */
        static std::wstring toWideString(const std::string &s) {
            static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
            return converter.from_bytes(s);
        }

        /**
        * converts fundamental and enum types to std::string
        */
        template <typename T>
        static std::string toString(const T & val, typename std::enable_if<std::is_fundamental<T>::value || std::is_enum<T>::value>::type* = 0) {
            return std::to_string(val);
        }

        /**
        * converts object types (class and struct) to std::string
        */
        template <typename T>
        static std::string toString(const T & val, typename std::enable_if<std::is_class<T>::value>::type* = 0) {
            return T::to_string(val);
        }

        /**
        * Special overload to avoid converting a std::string to std::string
        */
        static const std::string & toString(const std::string & val) {
            return val;
        }
    };
}

#define CUTI_TEST_METHOD(methodName)\
	static const EXPORT_METHOD ::Microsoft::VisualStudio::CppUnitTestFramework::MemberMethodInfo* CALLING_CONVENTION CATNAME(__GetTestMethodInfo_, methodName)()\
	{\
		__GetTestClassInfo();\
		__GetTestVersion();\
		ALLOCATE_TESTDATA_SECTION_METHOD\
		static const ::Microsoft::VisualStudio::CppUnitTestFramework::MethodMetadata s_Metadata = {L"TestMethodInfo", L#methodName, reinterpret_cast<unsigned char*>(__FUNCTION__), reinterpret_cast<unsigned char*>(__FUNCDNAME__), __WFILE__, __LINE__};\
\
		static ::Microsoft::VisualStudio::CppUnitTestFramework::MemberMethodInfo s_Info = {::Microsoft::VisualStudio::CppUnitTestFramework::MemberMethodInfo::TestMethod, nullptr, &s_Metadata};\
		s_Info.method.pVoidMethod = static_cast<::Microsoft::VisualStudio::CppUnitTestFramework::TestClassImpl::__voidFunc>(&methodName);\
		return &s_Info;\
	}
/**
* Function initializing a test method
*/
#define CUTI_SET_UP() TEST_METHOD_INITIALIZE(setUp)
/**
* Function cleaning up a test method
*/
#define CUTI_TEAR_DOWN() TEST_METHOD_CLEANUP(tearDown)
/**
* Declare a test class
*/
#define CUTI_TEST_CLASS(className) TEST_CLASS(className)
/**
* Compatibility for cppunit test suite registration
*/
#define CPPUNIT_TEST_SUITE(suiteName)
/**
* Declare a test method
*/
#define CPPUNIT_TEST(testFunc) CUTI_TEST_METHOD(testFunc)
/**
* Compatibility for cppunit test suite registration
*/
#define CPPUNIT_TEST_SUITE_END() 
/**
* Fails the test and print the error message
*/
#define CPPUNIT_FAIL(message) Assert::Fail(cuti::CutiTestHelper::toWideString(message).c_str(), LINE_INFO())
/**
* Checks for condition and print message on error
*/
#define CPPUNIT_ASSERT_MESSAGE(message,condition) Assert::IsTrue(condition, cuti::CutiTestHelper::toWideString(message).c_str(), LINE_INFO())
/**
* Checks for condition
*/
#define CPPUNIT_ASSERT(condition) CPPUNIT_ASSERT_MESSAGE("", condition)
/**
* Checks that expression throws ExceptionType.
* Fails if the wrong exception is catched or none
* Prints message on failure
*/
#define CPPUNIT_ASSERT_THROW_MESSAGE(message, expression, ExceptionType) Assert::ExpectException<ExceptionType>([&](){expression;}, cuti::CutiTestHelper::toWideString(message).c_str(), LINE_INFO())
/**
* Checks that expression throws ExceptionType.
* Fails if the wrong exception is catched or none
*/
#define CPPUNIT_ASSERT_THROW(expression, ExceptionType) CPPUNIT_ASSERT_THROW_MESSAGE("", expression, ExceptionType)
/**
* Checks that expression does NOT throw
* Fails if an exception is catched
* Prints message on failure
*/
#define CPPUNIT_ASSERT_NO_THROW_MESSAGE(message, expression) try {\
																expression;\
															} catch (std::exception &e) {\
																CPPUNIT_FAIL(message + std::string("\nCaught: std::exception or derived ") + e.what());\
															} catch (...) {\
																CPPUNIT_FAIL(message + std::string("\nunexpected exception caught"));\
															}
/**
* Checks that expression does NOT throw
* Fails if an exception is catched
*/
#define CPPUNIT_ASSERT_NO_THROW(expression) CPPUNIT_ASSERT_NO_THROW_MESSAGE("", expression)

/**
* Compares expected to actual using operation.
* Prints message on failure
*/
#define CUTI_ASSERT_COMPARE(expected, actual, operation, message) if (expected operation actual) {CPPUNIT_FAIL(cuti::CutiTestHelper::toString(expected) + message + cuti::CutiTestHelper::toString(actual));}
/**
* Checks that actual is LESS than expected
*/
#define CPPUNIT_ASSERT_LESS(expected,actual) CUTI_ASSERT_COMPARE(expected,actual, <= ," was expected to be less than ")
/**
* Checks that actual is LESS or EQUAL than expected
*/
#define CPPUNIT_ASSERT_LESSEQUAL(expected, actual) CUTI_ASSERT_COMPARE(expected,actual, < ," was expected to be less or equal to ")

/**
* Checks that actual is GREATER than expected
*/
#define CPPUNIT_ASSERT_GREATER(expected,actual) CUTI_ASSERT_COMPARE(expected,actual, >= ," was expected to be greater than ")
/**
* Checks that actual is GREATER or EQUAL than expected
*/
#define CPPUNIT_ASSERT_GREATEREQUAL(expected, actual) CUTI_ASSERT_COMPARE(expected,actual, > ," was expected to be greater or equal to ")
/**
* Checks that expected and actual are equal
* Prints message on failure
*/
#define CPPUNIT_ASSERT_EQUAL_MESSAGE(message,expected,actual) CUTI_ASSERT_COMPARE(expected, actual, !=, message)
/**
* Checks that expected and actual are equal
*/
#define CPPUNIT_ASSERT_EQUAL(expected,actual) CPPUNIT_ASSERT_EQUAL_MESSAGE(" was expected but instead got " ,expected,actual)
/**
* Checks that expected and actual are equal using a delta
* Prints message on failure
*/
#define CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE(message, expected, actual, delta) Assert::AreEqual(expected, actual, delta, cuti::CutiTestHelper::toWideString(message).c_str(), LINE_INFO())
/**
* Checks that expected and actual are equal using a delta
* Prints message on failure
*/
#define CPPUNIT_ASSERT_DOUBLES_EQUAL(expected, actual, delta) CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("", expected, actual, delta)
/**
* Checks that assertion fails
* Not implemented!
*/
#ifdef CUTI_WARNING_UNIMPLEMENTED
//#pragma message("Warning : CPPUNIT_ASSERT_ASSERTION_FAIL Not implemented")
#endif
#define CPPUNIT_ASSERT_ASSERTION_FAIL(assertion) //assertion
#endif
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
#endif

#endif
