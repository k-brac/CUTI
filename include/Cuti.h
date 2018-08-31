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

#ifndef CPP_UNIT_TEST_INTEGRATED
#define CPP_UNIT_TEST_INTEGRATED

/**
* Uses only cuti's macros
*/
#if defined(CUTI_FREE_STANDING) || defined(CUTI_CPPUNIT_COMPATABILITY) || defined(CUTI_UNKNOWN)

/*******************
* Public interface*
*******************/
#include <string>
#include <sstream>
#include <typeinfo>

#if defined(CUTI_USES_MSVC_UNIT_BACKEND)
#pragma warning(push)
#pragma warning(disable : 4505)
#define FEATURE_CORESYSTEM // if not defined, the test classes have a noexcept(false) destructor, which causes compile errors in some case
#include <CppUnitTest.h>
#undef FEATURE_CORESYSTEM
#undef TEST_CLASS
#pragma warning(pop)
#endif

#if defined(CUTI_USE_LONG_MACRO_NAME)

/**
* Declare a test fixture
*/
#if defined(CUTI_USES_XCTEST_BACKEND)
#define CUTI_TEST_CLASS(className)                                                                                                \
    \
class className;                                                                                                                 \
    \
static_assert(std::is_same<className, ::className>::value, "Test class " #className " must be declared in the global namespace"); \
    \
IMPL_CUTI_TEST_CLASS(className)
#else
#define CUTI_TEST_CLASS(className)                                                                                                \
    \
class className;                                                                                                                  \
    \
static_assert(std::is_same<className, ::className>::value, "Test class " #className " must be declared in the global namespace"); \
    \
IMPL_CUTI_TEST_CLASS(className)
#endif

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
* prepend test_ to testMethod if CUTI_PREPEND_TEST is defined
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

/**
* asserts that condition is true with optional message
*/
#define CUTI_ASSERT(condition, ...) IMPL_CUTI_ASSERT(condition, __VA_ARGS__)

/**
* unconditional fail with optional message
*/
#define CUTI_FAIL(...) IMPL_CUTI_FAIL(__VA_ARGS__)

/**
* asserts that actual is equal to expected with optional message
*/
#define CUTI_ASSERT_EQUAL(expected, actual, ...) IMPL_CUTI_ASSERT_EQUAL(expected, actual, __VA_ARGS__)

/**
* asserts that actual is less than bound with optional message
*/
#define CUTI_ASSERT_LESS(bound, actual, ...) IMPL_CUTI_ASSERT_LESS(bound, actual, __VA_ARGS__)

/**
* asserts that actual is greater than bound with optional message
*/
#define CUTI_ASSERT_GREATER(bound, actual, ...) IMPL_CUTI_ASSERT_GREATER(bound, actual, __VA_ARGS__)

/**
* asserts that actual is less than or equal to bound with optional message
*/
#define CUTI_ASSERT_LESSEQUAL(bound, actual, ...) IMPL_CUTI_ASSERT_LESSEQUAL(bound, actual, __VA_ARGS__)

/**
* asserts that actual is greater than or equal to bound with optional message
*/
#define CUTI_ASSERT_GREATEREQUAL(bound, actual, ...) IMPL_CUTI_ASSERT_GREATEREQUAL(bound, actual, __VA_ARGS__)

/**
* asserts that floating point actual is equal to actual with fabs(expected - actual) < delta with optional message
*/
#define CUTI_ASSERT_DOUBLES_EQUAL(expected, actual, delta, ...) IMPL_CUTI_ASSERT_DOUBLES_EQUAL(expected, actual, delta, __VA_ARGS__)

/**
* asserts that expression throws ExceptionType with optional message
*/
#define CUTI_ASSERT_THROW(expression, ExceptionType, ...) IMPL_CUTI_ASSERT_THROW(expression, ExceptionType, __VA_ARGS__)

/**
* asserts that expression doesn't throw with optional message
*/
#define CUTI_ASSERT_NO_THROW(expression, ...) IMPL_CUTI_ASSERT_NO_THROW(expression, __VA_ARGS__)

#else

/**
* Declare a test fixture
*/
#if defined(CUTI_USES_XCTEST_BACKEND)
#define TEST_CLASS(className)                                                                                                \
    \
class className;                                                                                                                 \
    \
static_assert(std::is_same<className, ::className>::value, "Test class " #className " must be declared in the global namespace"); \
    \
IMPL_CUTI_TEST_CLASS(className)
#else
#define TEST_CLASS(className)                                                                                                \
    \
class className;                                                                                                                  \
    \
static_assert(std::is_same<className, ::className>::value, "Test class " #className " must be declared in the global namespace"); \
    \
IMPL_CUTI_TEST_CLASS(className)
#endif

/**
* Defines a setup method to run before each test case
*/
#define SET_UP() IMPL_CUTI_SET_UP()

/**
* Defines a tear down method to run after each test case
*/
#define TEAR_DOWN() IMPL_CUTI_TEAR_DOWN()

/**
* Add testMethod to the test suite
* prepend test_ to testMethod if CUTI_PREPEND_TEST is defined
*/
#define TEST(testMethod) IMPL_CUTI_TEST(testMethod)

/**
* Delimits the beginning of the tests registration
*/
#define BEGIN_TESTS_REGISTRATION(className) IMPL_CUTI_BEGIN_TESTS_REGISTRATION(className)

/**
* Mandatory last statement of a test class
*/
#define END_TESTS_REGISTRATION() IMPL_CUTI_END_TESTS_REGISTRATION()

/***********************
* Public assert macros*
***********************/

/**
* asserts that condition is true with optional message
*/
#define ASSERT(condition, ...) IMPL_CUTI_ASSERT(condition, __VA_ARGS__)

/**
* unconditional fail with optional message
*/
#define FAIL(...) IMPL_CUTI_FAIL(__VA_ARGS__)

/**
* asserts that actual is equal to expected with optional message
*/
#define ASSERT_EQUAL(expected, actual, ...) IMPL_CUTI_ASSERT_EQUAL(expected, actual, __VA_ARGS__)

/**
* asserts that actual is less than bound with optional message
*/
#define ASSERT_LESS(bound, actual, ...) IMPL_CUTI_ASSERT_LESS(bound, actual, __VA_ARGS__)

/**
* asserts that actual is greater than bound with optional message
*/
#define ASSERT_GREATER(bound, actual, ...) IMPL_CUTI_ASSERT_GREATER(bound, actual, __VA_ARGS__)

/**
* asserts that actual is less than or equal to bound with optional message
*/
#define ASSERT_LESSEQUAL(bound, actual, ...) IMPL_CUTI_ASSERT_LESSEQUAL(bound, actual, __VA_ARGS__)

/**
* asserts that actual is greater than or equal to bound with optional message
*/
#define ASSERT_GREATEREQUAL(bound, actual, ...) IMPL_CUTI_ASSERT_GREATEREQUAL(bound, actual, __VA_ARGS__)

/**
* asserts that floating point actual is equal to actual with fabs(expected - actual) < delta with optional message
*/
#define ASSERT_DOUBLES_EQUAL(expected, actual, delta, ...) IMPL_CUTI_ASSERT_DOUBLES_EQUAL(expected, actual, delta, __VA_ARGS__)

/**
* asserts that expression throws ExceptionType with optional message
*/
#define ASSERT_THROW(expression, ExceptionType, ...) IMPL_CUTI_ASSERT_THROW(expression, ExceptionType, __VA_ARGS__)

/**
* asserts that expression doesn't throw with optional message
*/
#define ASSERT_NO_THROW(expression, ...) IMPL_CUTI_ASSERT_NO_THROW(expression, __VA_ARGS__)

#endif //defined(CUTI_USE_LONG_MACRO_NAME)

/*****************
* Public utility *
******************/

namespace cuti
{

#if defined(_MSC_VER) && _MSC_VER < 1900

#pragma push_macro("constexpr")
#define constexpr inline

#endif // defined(_MSC_VER) && _MSC_VER < 1900
    /**
     * constexpr recursive comparison of 2 strings where src_str is at least as long as ref_str
     * @param src_str The string to be compared
     * @param ref_str The reference string to look for in src_str
     * @param idx The index of the character to compare
     * @return True if src_str starts with ref_str, false otherwise
     */
    constexpr bool CompareStartWith(const char* src_str, const char* ref_str, unsigned idx) {
        return idx == static_cast<unsigned>(-1) ? true : src_str[idx] == ref_str[idx] && CompareStartWith(src_str, ref_str, static_cast<unsigned>(idx - 1));
    }
    
    /**
     * constexpr recursive comparison of 2 strings where src_str is at least as long as ref_str
     * @param src_str The string to be compared
     * @param ref_str The reference string to look for in src_str
     * @return True if src_str starts with ref_str, false otherwise. False for empty strings
     */
    template< unsigned N, unsigned M >
    constexpr bool StartWith(const char (&src_str)[N], const char (&ref_str)[M]) {
#if defined(_MSC_VER) && _MSC_VER < 1900
		return true;
#else
        return N >= M && M > static_cast<unsigned>(1) && CompareStartWith(src_str, ref_str, static_cast<unsigned>(M - 2));
#endif
    }

#if defined(_MSC_VER) && _MSC_VER < 1900

#undef constexpr
#pragma pop_macro("constexpr")

#define CUTI_START_WITH_TEST_CHECK(methodName) /**/
#else
#define CUTI_START_WITH_TEST_CHECK(methodName) static_assert(cuti::StartWith(#methodName, "test"), "Your test case name must start with 'test'");
#endif // defined(_MSC_VER) && _MSC_VER < 1900
    
    template <typename T, typename = typename std::enable_if<std::is_class<T>::value>::type>
    inline std::string ToString(const T &val)
    {
        std::ostringstream ost;
        ost << val;
        return ost.str();
    }
    
    inline std::string CutiGetMessage(std::string msg = std::string())
    {
        return msg;
    }
#if defined(CUTI_USES_MSVC_UNIT_BACKEND)
    /**
     * Converts string to wide string
     * @param s The string to be converted
     * @return s as a wide string
     */
    inline std::wstring CutiGetMessageW(const std::string &s = std::string())
    {
        RETURN_WIDE_STRING(s.c_str());
    }
#endif
    /**
     * converts fundamental and enum types to std::string
     */
    template <typename T, typename = typename std::enable_if<std::is_fundamental<T>::value || std::is_enum<T>::value>::type>
    inline std::string ToString(const T val)
    {
        return std::to_string(val);
    }
    
    /**
     * Special overload to avoid converting a std::string to std::string
     */
    template <>
    inline std::string ToString<std::string>(const std::string &val)
    {
        return val;
    }
}

/***********************************************************
* Private implementation common to visual studio and xcode *
************************************************************/
#if defined(CUTI_USES_MSVC_UNIT_BACKEND) || defined(CUTI_USES_XCTEST_BACKEND)

#define IMPL_CUTI_ASSERT_THROW(expression, ExceptionType, ...)                                         \
    \
do                                                                                              \
    {                                                                                                  \
        bool cpputCorrectExceptionThrown_ = false;                                                     \
        std::string cutiMsgT_("Expected exception not thrown. ");                                      \
        cutiMsgT_ += "Expected: " #ExceptionType ". ";                                                 \
                                                                                                       \
        try                                                                                            \
        {                                                                                              \
            expression;                                                                                \
            cutiMsgT_ += "But none was thrown. ";                                                      \
        }                                                                                              \
        catch (const ExceptionType &)                                                                  \
        {                                                                                              \
            cpputCorrectExceptionThrown_ = true;                                                       \
        }                                                                                              \
        catch (const std::exception &cuti_e)                                                                \
        {                                                                                              \
            cutiMsgT_ += std::string("Actual : ") + std::string(typeid(cuti_e).name()) + std::string(". "); \
            cutiMsgT_ += std::string("What() : ") + cuti_e.what() + std::string(". ");                      \
        }                                                                                              \
        catch (...)                                                                                    \
        {                                                                                              \
            cutiMsgT_ += ("Actual  : unknown. ");                                                      \
        }                                                                                              \
                                                                                                       \
        if (cpputCorrectExceptionThrown_)                                                              \
        {                                                                                              \
            break;                                                                                     \
        }                                                                                              \
        cutiMsgT_ += cuti::CutiGetMessage(__VA_ARGS__);                                                \
        IMPL_CUTI_FAIL(cutiMsgT_);                                                                          \
    \
}                                                                                               \
    while (false)

#define IMPL_CUTI_ASSERT_NO_THROW(expression, ...)                                                                                                     \
    \
do                                                                                                                                              \
    {                                                                                                                                                  \
        try                                                                                                                                            \
        {                                                                                                                                              \
            expression;                                                                                                                                \
        }                                                                                                                                              \
        catch (std::exception & cuti_e)                                                                                                                     \
        {                                                                                                                                              \
            IMPL_CUTI_FAIL(typeid(cuti_e).name() + std::string(" was caught. What() : ") + cuti_e.what() + std::string(". ") + cuti::CutiGetMessage(__VA_ARGS__)); \
        }                                                                                                                                              \
        catch (...)                                                                                                                                    \
        {                                                                                                                                              \
            IMPL_CUTI_FAIL(std::string("Unexpected exception caught. " + cuti::CutiGetMessage(__VA_ARGS__)));                                               \
        }                                                                                                                                              \
    \
}                                                                                                                                               \
    while (false)
#endif

/*******************************************************
* Private implementation for visual studio integration *
********************************************************/
#if defined(CUTI_USES_MSVC_UNIT_BACKEND)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define IMPL_CUTI_TEST_CLASS(className) ONLY_USED_AT_NAMESPACE_SCOPE class className : public ::Microsoft::VisualStudio::CppUnitTestFramework::TestClass<className>

#define IMPL_CUTI_SET_UP() TEST_METHOD_INITIALIZE(setUp)

#define IMPL_CUTI_TEAR_DOWN() TEST_METHOD_CLEANUP(tearDown)

#if defined(CUTI_PREPEND_TEST)
/**
* Add testMethod to the test suite
* prepend test_ to testMethod if CUTI_PREPEND_TEST is defined
*/
#define IMPL_CUTI_TEST(methodName)                                                                                                                                                                                                                           \
void test_##methodName() { methodName(); } \
static const EXPORT_METHOD::Microsoft::VisualStudio::CppUnitTestFramework::MemberMethodInfo *CALLING_CONVENTION CATNAME(__GetTestMethodInfo_, test_##methodName)()                                                                                                  \
    \
{                                                                                                                                                                                                                                                     \
        __GetTestClassInfo();                                                                                                                                                                                                                                \
        __GetTestVersion();                                                                                                                                                                                                                                  \
        ALLOCATE_TESTDATA_SECTION_METHOD                                                                                                                                                                                                                     \
        static const ::Microsoft::VisualStudio::CppUnitTestFramework::MethodMetadata s_Metadata = {L"TestMethodInfo", L"test_" WIDEN(#methodName), reinterpret_cast<const unsigned char *>(__FUNCTION__), reinterpret_cast<const unsigned char *>(__FUNCDNAME__), __WFILE__, __LINE__}; \
                                                                                                                                                                                                                                                             \
        static ::Microsoft::VisualStudio::CppUnitTestFramework::MemberMethodInfo s_Info = {::Microsoft::VisualStudio::CppUnitTestFramework::MemberMethodInfo::TestMethod, NULL, &s_Metadata};                                                                \
        s_Info.method.pVoidMethod = static_cast<::Microsoft::VisualStudio::CppUnitTestFramework::TestClassImpl::__voidFunc>(&test_##methodName);                                                                                                                    \
        return &s_Info;                                                                                                                                                                                                                                      \
    \
}
#else
/**
* Add testMethod to the test suite
*/
#define IMPL_CUTI_TEST(methodName)                                                                                                                                                                                                                           \
CUTI_START_WITH_TEST_CHECK(methodName);    \
static const EXPORT_METHOD::Microsoft::VisualStudio::CppUnitTestFramework::MemberMethodInfo *CALLING_CONVENTION CATNAME(__GetTestMethodInfo_, methodName)()                                                                                                  \
    \
{                                                                                                                                                                                                                                                     \
        __GetTestClassInfo();                                                                                                                                                                                                                                \
        __GetTestVersion();                                                                                                                                                                                                                                  \
        ALLOCATE_TESTDATA_SECTION_METHOD                                                                                                                                                                                                                     \
        static const ::Microsoft::VisualStudio::CppUnitTestFramework::MethodMetadata s_Metadata = {L"TestMethodInfo", L#methodName, reinterpret_cast<const unsigned char *>(__FUNCTION__), reinterpret_cast<const unsigned char *>(__FUNCDNAME__), __WFILE__, __LINE__}; \
                                                                                                                                                                                                                                                             \
        static ::Microsoft::VisualStudio::CppUnitTestFramework::MemberMethodInfo s_Info = {::Microsoft::VisualStudio::CppUnitTestFramework::MemberMethodInfo::TestMethod, NULL, &s_Metadata};                                                                \
        s_Info.method.pVoidMethod = static_cast<::Microsoft::VisualStudio::CppUnitTestFramework::TestClassImpl::__voidFunc>(&methodName);                                                                                                                    \
        return &s_Info;                                                                                                                                                                                                                                      \
    \
}
#endif

#define IMPL_CUTI_BEGIN_TESTS_REGISTRATION(className) /**/

#define IMPL_CUTI_END_TESTS_REGISTRATION() /**/

/****************************************************************
* Fix VisualStudio::CppUnitTestFramework missing specializations*
*****************************************************************/
#define INTERNAL_CUTI_SPECIALIZED_TO_STRING(type)                                                                               \
    template <>                                                                                                                 \
    inline std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<type>(const type &t) { RETURN_WIDE_STRING(t); } \
    \
template<> inline std::wstring                                                                                                  \
    Microsoft::VisualStudio::CppUnitTestFramework::ToString<type>(const type *t) { RETURN_WIDE_STRING(t); }                     \
    \
template<> inline std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<type>(type * t) { RETURN_WIDE_STRING(t); }

INTERNAL_CUTI_SPECIALIZED_TO_STRING(int64_t);
INTERNAL_CUTI_SPECIALIZED_TO_STRING(uint16_t);

/*****************
* CUTI internals*
*****************/

#define INTERNAL_CUTI_LINE_INFO() Microsoft::VisualStudio::CppUnitTestFramework::__LineInfo(__WFILE__, __FUNCTION__, __LINE__)

#define INTERNAL_CUTI_ASSERT_MESSAGE(expression, ...)             \
    do                                                            \
    {                                                             \
        auto li = INTERNAL_CUTI_LINE_INFO();                      \
        const auto cutiMsg_ = cuti::CutiGetMessageW(__VA_ARGS__); \
        expression;                                               \
    } while (false)

#define INTERNAL_CUTI_ASSERT_COMPARE(bound, operation, actual, msg, ...) IMPL_CUTI_ASSERT(bound operation actual, cuti::ToString(actual) + std::string(msg) + cuti::ToString(bound) + cuti::CutiGetMessage(__VA_ARGS__))

/*************************************************
* Visual studio CUTI assert macro implementations*
**************************************************/

#define IMPL_CUTI_ASSERT(condition, ...) INTERNAL_CUTI_ASSERT_MESSAGE(Assert::IsTrue(condition, cutiMsg_.c_str(), &li), __VA_ARGS__)

#define IMPL_CUTI_FAIL(...) INTERNAL_CUTI_ASSERT_MESSAGE(Assert::Fail(cutiMsg_.c_str(), &li), __VA_ARGS__)

#define IMPL_CUTI_ASSERT_EQUAL(expected, actual, ...) INTERNAL_CUTI_ASSERT_COMPARE(actual, ==, expected, " was expected but instead got ", __VA_ARGS__)

#define IMPL_CUTI_ASSERT_LESS(bound, actual, ...) INTERNAL_CUTI_ASSERT_COMPARE(bound, >, actual, " was expected to be less than ", __VA_ARGS__)

#define IMPL_CUTI_ASSERT_GREATER(bound, actual, ...) INTERNAL_CUTI_ASSERT_COMPARE(bound, <, actual, " was expected to be greater than ", __VA_ARGS__)

#define IMPL_CUTI_ASSERT_LESSEQUAL(bound, actual, ...) INTERNAL_CUTI_ASSERT_COMPARE(bound, >=, actual, " was expected to be less than or equal to ", __VA_ARGS__)

#define IMPL_CUTI_ASSERT_GREATEREQUAL(bound, actual, ...) INTERNAL_CUTI_ASSERT_COMPARE(bound, <=, actual, " was expected to be greater than or equal to ", __VA_ARGS__)

#define IMPL_CUTI_ASSERT_DOUBLES_EQUAL(expected, actual, delta, ...) INTERNAL_CUTI_ASSERT_MESSAGE(Assert::AreEqual(expected, actual, delta, cutiMsg_.c_str(), &li), __VA_ARGS__)

#elif defined(CUTI_USES_XCTEST_BACKEND)
/***********************************************
* Private implementation for XCode integration *
************************************************/

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#pragma clang diagnostic ignored "-Wreserved-id-macro"

#define __ASSERT_MACROS_DEFINE_VERSIONS_WITHOUT_UNDERSCORES 0
#import <Foundation/Foundation.h>
#import <XCTest/XCTest.h>
#import <objc/runtime.h>

#pragma clang diagnostic pop

#include <string>

/**
* Declare a test fixture
*/
#define IMPL_CUTI_TEST_CLASS(className)   \
    \
class className; /*forward declaration*/ \
    \
@interface C                              \
    ##className : XCTestCase {\
}        \
    \
+ (className*)instanceControl:(int)inCmd; \
- (className*)getInstance; \
@end                                      \
    \
@implementation C                         \
    ##className \
_Pragma("clang diagnostic push") \
_Pragma("clang diagnostic ignored \"-Wweak-vtables\"") \
class className : public cuti::CutiBaseTestCase

/**
* Defines a setup method to run before each test case
*/
#define IMPL_CUTI_SET_UP() void setUp() final

/**
* Defines a tear down method to run after each test case
*/
#define IMPL_CUTI_TEAR_DOWN() void tearDown() final

#if defined(CUTI_PREPEND_TEST)
/**
* Add testMethod to the test suite
* prepend test_ to testMethod if CUTI_PREPEND_TEST is defined
*/
#define IMPL_CUTI_TEST(testMethod) \
    \
-(void)test_##testMethod           \
    {                              \
        [self getInstance]->testMethod();   \
    \
}
#else
/**
* Add testMethod to the test suite
*/
#define IMPL_CUTI_TEST(testMethod) \
CUTI_START_WITH_TEST_CHECK(testMethod);    \
-(void)testMethod                  \
    {                              \
        [self getInstance]->testMethod();   \
    \
}
#endif

/**
* Delimits the beginning of the tests registration
*/
#define IMPL_CUTI_BEGIN_TESTS_REGISTRATION(className) \
    }                                                 \
    ;                                                 \
    \
_Pragma("clang diagnostic pop") \
+ (className*)instanceControl:(int)inCmd              \
{                                                     \
    static className* kInstance = nullptr;            \
    switch ( inCmd )                                  \
    {                                                 \
        case 10: kInstance = new className(); break;  \
        case 20: delete kInstance; break;             \
        default: break;                               \
    }                                                 \
    return kInstance;                                 \
}                                                     \
- (className*)getInstance                             \
{                                                     \
    return [C ## className instanceControl:0];        \
}                                                     \
+ (void)setUp                                         \
    {                                                 \
        [super setUp];                                \
       [self instanceControl:10];                     \
    \
}                                              \
    \
+(void)tearDown                                       \
    {                                                 \
        [self instanceControl:20];                    \
        [super tearDown];                             \
    \
}                                              \
    \
-(void)setUp                                          \
    {                                                 \
        [super setUp];                                \
        self.continueAfterFailure = NO;               \
        [self getInstance]->self = self;              \
        [self getInstance]->setUp();                  \
    \
}                                              \
    \
-(void)tearDown                                       \
    {                                                 \
        [self getInstance]->tearDown();               \
        [super tearDown];                             \
    \
}

/**
* Mandatory last statement of a test class
*/
#define IMPL_CUTI_END_TESTS_REGISTRATION() \
    \
@end \
namespace                          \
    {

/*****************
* CUTI internals*
*****************/

namespace cuti
{
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
struct CutiBaseTestCase
{
    XCTestCase *self = nullptr;
    virtual void setUp() {}
    virtual void tearDown() {}
    virtual ~CutiBaseTestCase() = default;
};
#pragma clang diagnostic pop
};

#define INTERNAL_CUTI_FORMAT_MESSAGE() @"%@", @(cutiMsg_.c_str())

#define INTERNAL_CUTI_ASSERT_MESSAGE(expression, ...)    \
    do                                                   \
    {                                                    \
        \
_Pragma("clang diagnostic push") \
_Pragma("clang diagnostic ignored \"-Wformat-nonliteral\"") \
const auto cutiMsg_ = cuti::CutiGetMessage(__VA_ARGS__); \
        expression;                                      \
    } while (false) \
_Pragma("clang diagnostic push")

/******************************************
* XCode CUTI assert macro implementations*
******************************************/

#define IMPL_CUTI_ASSERT(condition, ...) INTERNAL_CUTI_ASSERT_MESSAGE(XCTAssert(condition, INTERNAL_CUTI_FORMAT_MESSAGE()), __VA_ARGS__)

#define IMPL_CUTI_FAIL(...) INTERNAL_CUTI_ASSERT_MESSAGE(XCTFail(INTERNAL_CUTI_FORMAT_MESSAGE()), __VA_ARGS__)

/**
* not using XCTAssertEqual because the value displayed for object comparison is not nice
*/
#define IMPL_CUTI_ASSERT_EQUAL(expected, actual, ...) INTERNAL_CUTI_ASSERT_MESSAGE(XCTAssert(expected == actual, INTERNAL_CUTI_FORMAT_MESSAGE()), __VA_ARGS__)

#define IMPL_CUTI_ASSERT_LESS(bound, actual, ...) INTERNAL_CUTI_ASSERT_MESSAGE(XCTAssertLessThan(actual, bound, INTERNAL_CUTI_FORMAT_MESSAGE()), __VA_ARGS__)

#define IMPL_CUTI_ASSERT_GREATER(bound, actual, ...) INTERNAL_CUTI_ASSERT_MESSAGE(XCTAssertGreaterThan(actual, bound, INTERNAL_CUTI_FORMAT_MESSAGE()), __VA_ARGS__)

#define IMPL_CUTI_ASSERT_LESSEQUAL(bound, actual, ...) INTERNAL_CUTI_ASSERT_MESSAGE(XCTAssertLessThanOrEqual(actual, bound, INTERNAL_CUTI_FORMAT_MESSAGE()), __VA_ARGS__)

#define IMPL_CUTI_ASSERT_GREATEREQUAL(bound, actual, ...) INTERNAL_CUTI_ASSERT_MESSAGE(XCTAssertGreaterThanOrEqual(actual, bound, INTERNAL_CUTI_FORMAT_MESSAGE()), __VA_ARGS__)

#define IMPL_CUTI_ASSERT_DOUBLES_EQUAL(expected, actual, delta, ...) INTERNAL_CUTI_ASSERT_MESSAGE(XCTAssertEqualWithAccuracy(actual, expected, delta, INTERNAL_CUTI_FORMAT_MESSAGE()), __VA_ARGS__)

#elif defined(CUTI_UNKNOWN)
/***************************************************************************
* Private implementation when using cuti's front end and cppunit's backend *
****************************************************************************/

#ifdef _MSC_VER
#include <Windows.h>
#pragma warning(push)
#pragma warning(disable : 4251)
#pragma warning(disable : 4512)
#pragma warning(disable : 4275)
#endif

#ifndef CPPUNIT_UNIQUE_COUNTER
#define CPPUNIT_UNIQUE_COUNTER __COUNTER__
#endif

#if __MACH__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wweak-vtables"
#pragma clang diagnostic ignored "-Wextra-semi"
#pragma clang diagnostic ignored "-Wdocumentation"
#pragma clang diagnostic ignored "-Wreserved-id-macro"
#pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#pragma clang diagnostic ignored "-Wold-style-cast"
#pragma clang diagnostic ignored "-Wdeprecated"
#define CPPUNIT_STD_NEED_ALLOCATOR 0
#endif

#include "cppunit/plugin/TestPlugIn.h"
#include <cppunit/extensions/HelperMacros.h>

#if __MACH__
#pragma clang diagnostic pop
#endif

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#define IMPL_CUTI_TEST_CLASS(className)                   \
    \
class className;                                          \
    \
static CPPUNIT_NS::AutoRegisterSuite<className>           \
        CPPUNIT_MAKE_UNIQUE_NAME(autoRegisterRegistry__); \
    \
class className : public CppUnit::TestFixture

#define IMPL_CUTI_SET_UP() void setUp() final

#define IMPL_CUTI_TEAR_DOWN() void tearDown() final

#define IMPL_CUTI_TEST(methodName) CUTI_START_WITH_TEST_CHECK(methodName); CPPUNIT_TEST(methodName)

#define IMPL_CUTI_BEGIN_TESTS_REGISTRATION(className) CPPUNIT_TEST_SUITE(className)

#define IMPL_CUTI_END_TESTS_REGISTRATION() CPPUNIT_TEST_SUITE_END()

#define IMPL_CUTI_ASSERT(condition, ...) CPPUNIT_ASSERT_MESSAGE(cuti::CutiGetMessage(__VA_ARGS__), condition)

#define IMPL_CUTI_FAIL(...) CPPUNIT_FAIL(cuti::CutiGetMessage(__VA_ARGS__))

/**
* not using CPPUNIT_ASSERT_EQUAL because CppUnit::assertion_traits<T> is annoying
*/
#define IMPL_CUTI_ASSERT_EQUAL(expected, actual, ...) CPPUNIT_ASSERT_MESSAGE(cuti::CutiGetMessage(__VA_ARGS__), expected == actual)

#define IMPL_CUTI_ASSERT_LESS(bound, actual, ...) CPPUNIT_ASSERT_LESS(bound, actual)

#define IMPL_CUTI_ASSERT_GREATER(bound, actual, ...) CPPUNIT_ASSERT_GREATER(bound, actual)

#define IMPL_CUTI_ASSERT_LESSEQUAL(bound, actual, ...) CPPUNIT_ASSERT_LESSEQUAL(bound, actual)

#define IMPL_CUTI_ASSERT_GREATEREQUAL(bound, actual, ...) CPPUNIT_ASSERT_GREATEREQUAL(bound, actual)

#define IMPL_CUTI_ASSERT_DOUBLES_EQUAL(expected, actual, delta, ...) CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE(cuti::CutiGetMessage(__VA_ARGS__), expected, actual, delta)

#define IMPL_CUTI_ASSERT_THROW(expression, ExceptionType, ...) CPPUNIT_ASSERT_THROW_MESSAGE(cuti::CutiGetMessage(__VA_ARGS__), expression, ExceptionType)

#define IMPL_CUTI_ASSERT_NO_THROW(expression, ...) CPPUNIT_ASSERT_NO_THROW_MESSAGE(cuti::CutiGetMessage(__VA_ARGS__), expression)

#else

#error "You are trying to use cuti with an unknown configuration"

#endif

#endif

/**
* Compatibility mode to allow the use of cuti as backend and cppunit as frontend
*/
/***************************************************************************
* Private implementation when using cuti's backend and cppunit's front end *
****************************************************************************/
#if defined(CUTI_CPPUNIT_COMPATABILITY)

#define CPPUNIT_TEST_SUITE(className) IMPL_CUTI_BEGIN_TESTS_REGISTRATION(className)

#define CPPUNIT_TEST(testMethod) IMPL_CUTI_TEST(testMethod)

#define CPPUNIT_TEST_SUITE_END() IMPL_CUTI_END_TESTS_REGISTRATION()

#define CPPUNIT_FAIL(message) IMPL_CUTI_FAIL(message)

#define CPPUNIT_ASSERT_MESSAGE(message, condition) IMPL_CUTI_ASSERT(condition, message)

#define CPPUNIT_ASSERT(condition) IMPL_CUTI_ASSERT(condition)

#define CPPUNIT_ASSERT_THROW_MESSAGE(message, expression, ExceptionType) IMPL_CUTI_ASSERT_THROW(expression, ExceptionType, message)

#define CPPUNIT_ASSERT_THROW(expression, ExceptionType) IMPL_CUTI_ASSERT_THROW(expression, ExceptionType)

#define CPPUNIT_ASSERT_NO_THROW_MESSAGE(message, expression) IMPL_CUTI_ASSERT_NO_THROW(expression, message)

#define CPPUNIT_ASSERT_NO_THROW(expression) IMPL_CUTI_ASSERT_NO_THROW(expression)

#define CPPUNIT_ASSERT_LESS(expected, actual) IMPL_CUTI_ASSERT_LESS(expected, actual)

#define CPPUNIT_ASSERT_LESSEQUAL(expected, actual) IMPL_CUTI_ASSERT_LESSEQUAL(expected, actual)

#define CPPUNIT_ASSERT_GREATER(expected, actual) IMPL_CUTI_ASSERT_GREATER(expected, actual)

#define CPPUNIT_ASSERT_GREATEREQUAL(expected, actual) IMPL_CUTI_ASSERT_GREATEREQUAL(expected, actual)

#define CPPUNIT_ASSERT_EQUAL_MESSAGE(message, expected, actual) IMPL_CUTI_ASSERT_EQUAL(expected, actual, message)

#define CPPUNIT_ASSERT_EQUAL(expected, actual) IMPL_CUTI_ASSERT_EQUAL(expected, actual)

#define CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE(message, expected, actual, delta) IMPL_CUTI_ASSERT_DOUBLES_EQUAL(expected, actual, delta, message)

#define CPPUNIT_ASSERT_DOUBLES_EQUAL(expected, actual, delta) IMPL_CUTI_ASSERT_DOUBLES_EQUAL(expected, actual, delta)

#define CPPUNIT_ASSERT_ASSERTION_FAIL(expression) expression

#if defined(CUTI_EXCLUDE_TEST_FROM_COVERAGE) && defined(_WIN32)
#include <CodeCoverage/CodeCoverage.h>
/**
* Compatibility for cppunit test suite registration
* Can exclude test suite from code coverage
*/
#define CPPUNIT_TEST_SUITE_REGISTRATION(className)          \
    ExcludeFromCodeCoverage(className, L#className L"::*"); \
    \
static_assert(std::is_same<className, ::className>::value, "CPPUNIT_TEST_SUITE_REGISTRATION(" #className ") must be declared in the global namespace")
#else
#define CPPUNIT_TEST_SUITE_REGISTRATION(className) static_assert(std::is_same<className, ::className>::value, "CPPUNIT_TEST_SUITE_REGISTRATION(" #className ") must be declared in the global namespace")
#endif

#elif defined(CUTI_NO_INTEGRATION)
/********************************************************************
* Private implementation when using cppunit's front end and backend *
*********************************************************************/

#ifdef _MSC_VER
#include <Windows.h>
#pragma warning(push)
#pragma warning(disable : 4251)
#pragma warning(disable : 4512)
#pragma warning(disable : 4275)
#endif

#ifndef CPPUNIT_UNIQUE_COUNTER
#define CPPUNIT_UNIQUE_COUNTER __COUNTER__
#endif

#include "cppunit/plugin/TestPlugIn.h"
#include <cppunit/extensions/HelperMacros.h>

/**
* Replace CPPUNIT_TEST_SUITE_REGISTRATION with an empty definition
*/
#undef CPPUNIT_TEST_SUITE_REGISTRATION
#define CPPUNIT_TEST_SUITE_REGISTRATION(className) /**/

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#if defined(CUTI_USE_LONG_MACRO_NAME)
/**
* Declare a test fixture
*/
#define CUTI_TEST_CLASS(className)                                                                                                \
    \
class className;                                                                                                                  \
    \
static_assert(std::is_same<className, ::className>::value, "Test class " #className " must be declared in the global namespace"); \
    \
static CPPUNIT_NS::AutoRegisterSuite<className>                                                                                   \
        CPPUNIT_MAKE_UNIQUE_NAME(autoRegisterRegistry__);                                                                         \
    \
class className : public CppUnit::TestFixture
/**
* Function initializing a test case
*/
#define CUTI_SET_UP() void setUp() final
/**
* Function cleaning up a test case
*/
#define CUTI_TEAR_DOWN() void tearDown() final

#else
/**
* Declare a test fixture
*/
#define TEST_CLASS(className)                                                                                                \
    \
class className;                                                                                                                  \
    \
static_assert(std::is_same<className, ::className>::value, "Test class " #className " must be declared in the global namespace"); \
    \
static CPPUNIT_NS::AutoRegisterSuite<className>                                                                                   \
        CPPUNIT_MAKE_UNIQUE_NAME(autoRegisterRegistry__);                                                                         \
    \
class className : public CppUnit::TestFixture

/**
* Function initializing a test case
*/
#define SET_UP() void setUp() final
/**
* Function cleaning up a test case
*/
#define TEAR_DOWN() void tearDown() final
#endif

#endif

#if defined(CUTI_CONFIG_ERROR)
#error "Cuti's configuration is wrong'"
#endif

#endif //CPP_UNIT_TEST_INTEGRATED
