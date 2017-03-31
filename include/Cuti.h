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
#include <codecvt>

/**
* Declare a test fixture
*/
#if defined(CUTI_USES_XCTEST_BACKEND)
#define CUTI_TEST_CLASS(className)                                                                                                \
    \
struct className;                                                                                                                 \
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

/*****************
* Public utility *
******************/

namespace cuti
{
#if /*!defined(_MSC_VER) ||*/ _MSC_VER == 1900
//http://stackoverflow.com/questions/87372/check-if-a-class-has-a-member-function-of-a-given-signature
template <typename, typename T>
struct has_serialize
{
    static_assert(std::integral_constant<T, false>::value, "Second template parameter needs to be of function type.");
};
template <typename C, typename Ret, typename... Args>
struct has_serialize<C, Ret(Args...)>
{
  private:
    template <typename T>
    static constexpr auto check(T *)
        -> typename std::is_same<
            decltype(std::declval<T>().operator<<(std::declval<Args>()...)),
            Ret>::type;

    template <typename>
    static constexpr std::false_type check(...);

    typedef decltype(check<C>(0)) type;

  public:
    static constexpr bool value = type::value;
};

template <typename, typename T>
struct has_static_serialize
{
    static_assert(std::integral_constant<T, false>::value, "Second template parameter needs to be of function type.");
};
template <typename C, typename Ret, typename... Args>
struct has_static_serialize<C, Ret(Args...)>
{
  private:
    template <typename T>
    static constexpr auto check(T *)
        -> typename std::is_same<
            decltype(operator<<(std::declval<Args>()...)),
            Ret>::type;

    template <typename>
    static constexpr std::false_type check(...);

    typedef decltype(check<C>(0)) type;

  public:
    static constexpr bool value = type::value;
};

/**
    * converts object types (class and struct) to std::string
    */
template <typename T, typename std::enable_if<
                          has_serialize<T, std::ostringstream &(std::ostringstream &)>::value
#if !defined(CUTI_USE_MEMBER_SERIALIZE)
                          && !has_static_serialize<T, std::ostringstream &(std::ostringstream &, const T &)>::value
#endif
                          >::type * = 0>
inline std::string ToString(const T &val)
{
    std::ostringstream ost;
    val.operator<<(ost);
    return ost.str();
}

template <typename T, typename std::enable_if<
                          has_static_serialize<T, std::ostringstream &(std::ostringstream &, const T &)>::value
#if defined(CUTI_USE_MEMBER_SERIALIZE)
                          && !has_serialize<T, std::ostringstream &(std::ostringstream &)>::value
#endif
                          >::type * = 0>
inline std::string ToString(const T &val)
{
    std::ostringstream ost;
    ost << val;
    return ost.str();
}

template <typename T,
          typename std::enable_if<
              std::is_class<T>::value &&
              !has_serialize<T, std::ostringstream &(std::ostringstream &)>::value &&
              !has_static_serialize<T, std::ostringstream &(std::ostringstream &, const T &)>::value>::type * = 0>
inline std::string ToString(const T & /*val*/)
{
    std::ostringstream ost;
    ost << typeid(T).name();
    return ost.str();
}
#else
template <typename T, typename std::enable_if<std::is_object<T>::value && !std::is_fundamental<T>::value>::type * = 0>
inline std::string ToString(const T &val)
{
    std::ostringstream ost;
    val.operator<<(ost);
    return ost.str();
}

#endif

inline std::string CutiGetMessage(std::string msg = std::string())
{
    return msg;
}
/**
    * Converts string to wide string
    * @param s The string to be converted
    * @return s as a wide string
    */
inline std::wstring CutiGetMessageW(const std::string &s = std::string())
{
    static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(s);
}
/**
    * converts fundamental and enum types to std::string
    */
template <typename T, typename std::enable_if<std::is_fundamental<T>::value || std::is_enum<T>::value>::type * = 0>
inline std::string ToString(const T val)
{
    return std::to_string(val);
}

/**
    * Special overload to avoid converting a std::string to std::string
    */
template <typename T, typename std::enable_if<std::is_same<T, std::string>::value>::type * = 0>
inline std::string ToString(const T &val)
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
        catch (const std::exception &e)                                                                \
        {                                                                                              \
            cutiMsgT_ += std::string("Actual : ") + std::string(typeid(e).name()) + std::string(". "); \
            cutiMsgT_ += std::string("What() : ") + e.what() + std::string(". ");                      \
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
        CUTI_FAIL(cutiMsgT_);                                                                          \
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
        catch (std::exception & e)                                                                                                                     \
        {                                                                                                                                              \
            CUTI_FAIL(std::string("Caught: std::exception or derived. What() : ") + e.what() + std::string(". ") + cuti::CutiGetMessage(__VA_ARGS__)); \
        }                                                                                                                                              \
        catch (...)                                                                                                                                    \
        {                                                                                                                                              \
            CUTI_FAIL(std::string("Unexpected exception caught. " + cuti::CutiGetMessage(__VA_ARGS__)));                                               \
        }                                                                                                                                              \
    \
}                                                                                                                                               \
    while (false)
#endif

#define CUTI_DEFAULT_TO_STRING(className) IMPL_CUTI_DEFAULT_TO_STRING(className)

/*******************************************************
* Private implementation for visual studio integration *
********************************************************/
#if defined(CUTI_USES_MSVC_UNIT_BACKEND)
#pragma warning(push)
#pragma warning(disable : 4505)
#include <CppUnitTest.h>
#pragma warning(pop)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define IMPL_CUTI_TEST_CLASS(className) TEST_CLASS(className)

#define IMPL_CUTI_SET_UP() TEST_METHOD_INITIALIZE(setUp)

#define IMPL_CUTI_TEAR_DOWN() TEST_METHOD_CLEANUP(tearDown)

#define IMPL_CUTI_TEST(methodName)                                                                                                                                                                                                                           \
    \
static const EXPORT_METHOD::Microsoft::VisualStudio::CppUnitTestFramework::MemberMethodInfo *CALLING_CONVENTION CATNAME(__GetTestMethodInfo_, methodName)()                                                                                                  \
    \
{                                                                                                                                                                                                                                                     \
        __GetTestClassInfo();                                                                                                                                                                                                                                \
        __GetTestVersion();                                                                                                                                                                                                                                  \
        ALLOCATE_TESTDATA_SECTION_METHOD                                                                                                                                                                                                                     \
        static const ::Microsoft::VisualStudio::CppUnitTestFramework::MethodMetadata s_Metadata = {L"TestMethodInfo", L#methodName, reinterpret_cast<unsigned char *>(__FUNCTION__), reinterpret_cast<unsigned char *>(__FUNCDNAME__), __WFILE__, __LINE__}; \
                                                                                                                                                                                                                                                             \
        static ::Microsoft::VisualStudio::CppUnitTestFramework::MemberMethodInfo s_Info = {::Microsoft::VisualStudio::CppUnitTestFramework::MemberMethodInfo::TestMethod, NULL, &s_Metadata};                                                                \
        s_Info.method.pVoidMethod = static_cast<::Microsoft::VisualStudio::CppUnitTestFramework::TestClassImpl::__voidFunc>(&methodName);                                                                                                                    \
        return &s_Info;                                                                                                                                                                                                                                      \
    \
}

#define IMPL_CUTI_BEGIN_TESTS_REGISTRATION(className) /**/

#define IMPL_CUTI_END_TESTS_REGISTRATION() /**/

#define IMPL_CUTI_DEFAULT_TO_STRING(className)               \
    \
inline std::wstringstream &                                  \
    operator<<(std::wstringstream &os, const className &obj) \
    \
{                                                     \
        os << cuti::CutiGetMessageW(cuti::ToString(obj));    \
        return os;                                           \
    \
}                                                     \
    \
INTERNAL_CUTI_SPECIALIZED_TO_STRING(className)

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

#define IMPL_CUTI_ASSERT_EQUAL(expected, actual, ...) INTERNAL_CUTI_ASSERT_MESSAGE(Assert::AreEqual(expected, actual, cutiMsg_.c_str(), &li), __VA_ARGS__)

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
struct className; /*forward declaration*/ \
    \
@interface C                              \
    ##className : XCTestCase {\
}        \
    \
@end                                      \
    \
static className *kInstance = nullptr;    \
    \
@implementation C                         \
    ##className \
_Pragma("clang diagnostic push") \
_Pragma("clang diagnostic ignored \"-Wweak-vtables\"") \
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
    \
-(void)test_##testMethod           \
    {                              \
        kInstance->testMethod();   \
    \
}
#else
/**
* Add testMethod to the test suite
* prepend test_ to testMethof if CUTI_PREPEND_TEST is defined
*/
#define IMPL_CUTI_TEST(testMethod) \
    \
-(void)testMethod                  \
    {                              \
        kInstance->testMethod();   \
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
+ (void)setUp                                         \
    {                                                 \
        [super setUp];                                \
        kInstance = new className();                  \
    \
}                                              \
    \
+(void)tearDown                                       \
    {                                                 \
        delete kInstance;                             \
        [super tearDown];                             \
    \
}                                              \
    \
-(void)setUp                                          \
    {                                                 \
        [super setUp];                                \
        self.continueAfterFailure = NO;               \
        kInstance->self = self;                       \
        kInstance->setUp();                           \
    \
}                                              \
    \
-(void)tearDown                                       \
    {                                                 \
        kInstance->tearDown();                        \
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
    XCTestCase *self = NULL;
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

#define IMPL_CUTI_DEFAULT_TO_STRING(className) /*\                                     \ \
 inline std::ostringstream& operator<<(std::ostringstream& os, const className& obj) \ \ \
 { \                                                                                   \ \
     os << cuti::CutiGetMessage(cuti::ToString(obj)); \                                \ \
     return os; \                                                                      \ \
 }*/

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

#define IMPL_CUTI_SET_UP() virtual void setUp() override final

#define IMPL_CUTI_TEAR_DOWN() virtual void tearDown() override final

#define IMPL_CUTI_TEST(methodName) CPPUNIT_TEST(methodName)

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

#define IMPL_CUTI_DEFAULT_TO_STRING(className) /*\                                    \ \
inline std::ostringstream& operator<<(std::ostringstream& os, const className& obj) \ \ \
{ \                                                                                   \ \
    os << cuti::CutiGetMessage(cuti::ToString(obj)); \                                \ \
    return os; \                                                                      \ \
}*/

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

#define CPPUNIT_TEST_SUITE(className) CUTI_BEGIN_TESTS_REGISTRATION(className)

#define CPPUNIT_TEST(testMethod) CUTI_TEST(testMethod)

#define CPPUNIT_TEST_SUITE_END() CUTI_END_TESTS_REGISTRATION()

#define CPPUNIT_FAIL(message) CUTI_FAIL(message)

#define CPPUNIT_ASSERT_MESSAGE(message, condition) CUTI_ASSERT(condition, message)

#define CPPUNIT_ASSERT(condition) CUTI_ASSERT(condition)

#define CPPUNIT_ASSERT_THROW_MESSAGE(message, expression, ExceptionType) CUTI_ASSERT_THROW(expression, ExceptionType, message)

#define CPPUNIT_ASSERT_THROW(expression, ExceptionType) CUTI_ASSERT_THROW(expression, ExceptionType)

#define CPPUNIT_ASSERT_NO_THROW_MESSAGE(message, expression) CUTI_ASSERT_NO_THROW(expression, message)

#define CPPUNIT_ASSERT_NO_THROW(expression) CUTI_ASSERT_NO_THROW(expression)

#define CPPUNIT_ASSERT_LESS(expected, actual) CUTI_ASSERT_LESS(expected, actual)

#define CPPUNIT_ASSERT_LESSEQUAL(expected, actual) CUTI_ASSERT_LESSEQUAL(expected, actual)

#define CPPUNIT_ASSERT_GREATER(expected, actual) CUTI_ASSERT_GREATER(expected, actual)

#define CPPUNIT_ASSERT_GREATEREQUAL(expected, actual) CUTI_ASSERT_GREATEREQUAL(expected, actual)

#define CPPUNIT_ASSERT_EQUAL_MESSAGE(message, expected, actual) CUTI_ASSERT_EQUAL(expected, actual, message)

#define CPPUNIT_ASSERT_EQUAL(expected, actual) CUTI_ASSERT_EQUAL(expected, actual)

#define CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE(message, expected, actual, delta) CUTI_ASSERT_DOUBLES_EQUAL(expected, actual, delta, message)

#define CPPUNIT_ASSERT_DOUBLES_EQUAL(expected, actual, delta) CUTI_ASSERT_DOUBLES_EQUAL(expected, actual, delta)

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
#define CUTI_SET_UP() virtual void setUp() override final
/**
* Function cleaning up a test case
*/
#define CUTI_TEAR_DOWN() virtual void tearDown() override final

#endif

#endif //CPP_UNIT_TEST_INTEGRATED
