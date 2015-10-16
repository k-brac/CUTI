#ifdef CUTI_USES_MSVC_UNIT_BACKEND
#ifdef WIN32
#pragma warning( push )
#pragma warning( disable : 4505 )
#include <CppUnitTest.h>
#pragma warning( pop )
#include <CodeCoverage\CodeCoverage.h>
#include <codecvt>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#ifdef CUTI_EXCLUDE_TEST_FROM_COVERAGE
/**
* Excludes test code from code coverage
*/
#define CUTI_EXCLUDE_FROM_COVERAGE(className, pattern) ExcludeFromCodeCoverage(className, pattern);
#else
#define CUTI_EXCLUDE_FROM_COVERAGE(className, pattern)
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
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
			return converter.from_bytes(s);
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
		static ::Microsoft::VisualStudio::CppUnitTestFramework::MemberMethodInfo s_Info = {::Microsoft::VisualStudio::CppUnitTestFramework::MemberMethodInfo::TestMethod, NULL, &s_Metadata};\
		s_Info.method.pVoidMethod = static_cast<::Microsoft::VisualStudio::CppUnitTestFramework::TestClassImpl::__voidFunc>(&methodName);\
		return &s_Info;\
	}
/**
* Set up a test case
*/
#define CUTI_SET_UP() TEST_METHOD_INITIALIZE(setUp)
/**
* Tear down a test case
*/
#define CUTI_TEAR_DOWN() TEST_METHOD_CLEANUP(tearDown)
/**
* Declare a test class
*/
#define CUTI_TEST_CLASS(className) TEST_CLASS(className)
/**
* Compatibility for cppunit test suite registration
*/
#define CPPUNIT_TEST_SUITE_REGISTRATION(className)
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
#define CUTI_ASSERT_COMPARE(expected, actual, operation, message) if (expected operation actual) {CPPUNIT_FAIL(std::to_string(expected) + message + std::to_string(actual));}
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
#pragma message("Warning : CPPUNIT_ASSERT_ASSERTION_FAIL Not implemented")
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
#pragma warning( push )
#pragma warning( disable : 4251 )
#pragma warning( disable : 4512 )
#endif
#include "cppunit/plugin/TestPlugIn.h"
#include <cppunit/extensions/HelperMacros.h>

#ifdef _MSC_VER
#pragma warning( pop )
#endif
#define CUTI_TEST_CLASS(className) class className : public CppUnit::TestFixture
#define CUTI_SET_UP() virtual void setUp() override
#define CUTI_TEAR_DOWN() virtual void tearDown() override
#define CUTI_EXCLUDE_FROM_COVERAGE(className, pattern)
#endif
