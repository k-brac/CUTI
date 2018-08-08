[![Build status](https://ci.appveyor.com/api/projects/status/g8h805xifcsauo9x/branch/master?svg=true)](https://ci.appveyor.com/project/k-brac/cuti/branch/master)
[![Build Status](https://travis-ci.org/k-brac/CUTI.svg?branch=master)](https://travis-ci.org/k-brac/CUTI)

# CUTI
CUTI stands for C++ Unit Test Integrated

## What?
CUTI allows you to easily integrate your C++ unit tests into Visual Studio and Xcode. It is also possible to use cppunit's macros and test runner through compatibility configuration.

Visual Studio | Xcode
------------- | ------
2013 | 6.4
2015 | 7.3
2017 | 8.3
_ | 9.4
![Visual Studio Tests Results](https://cloud.githubusercontent.com/assets/7798247/24714946/40390d92-1a2a-11e7-8f8f-8787e2aa6498.jpg) | ![Xcode Tests Results](https://cloud.githubusercontent.com/assets/7798247/24714947/429acb5c-1a2a-11e7-9a32-95194205f046.jpg)

## Why?
* You can run your tests from within your IDE
* You have visual feedback when running your tests
* It is easier to use your IDE tools with your tests like code coverage, profiling,...
* It is easier to debug your code
* You are more likely to run your tests

## Prerequisite
* Use CMake >= 3.2
* The code to test must be compiled as a library (static or shared)

## How?
* Add CUTI's root directory to your CMakeLists.txt
```cmake  
add_subdirectory(${PATH_TO_CUTI_ROOT_DIR} ${CMAKE_BINARY_DIR}/cuti)
```
* Create a test target
```cmake
cuti_creates_test_target(test_project_name project_to_test list_of_test_files_cpp)
```
* That's it! Take a look at [./test/testDynamicLib/CMakeLists.txt](./test/testDynamicLib/CMakeLists.txt) for an example

## Example
[There is a toy project in the test directory to show how to use Cuti.](./test/testDynamicLib/)

### CMakeLists.txt
```cmake
add_subdirectory(${PATH_TO_CUTI_ROOT_DIR} ${CMAKE_BINARY_DIR}/cuti)
#create your library (SHARED or STATIC)
add_library(MyLib SHARED ${MyLib_source_files})
#Create 'MyLibTest' test target to test MyLib
cuti_creates_test_target(MyLibTest MyLib ${MyLibTest_source_files})
```

### TestClass.cpp
```cpp
#include "Cuti.h"

TEST_CLASS(TestClass) {
public:
    /**
    * Optional. Executed before every test case
    */
    SET_UP() {
      //...
    }

    /**
    * Optional. Executed after every test case
    */
    TEAR_DOWN() {
        //...
    }

    void testSimpleAssert() {
        ASSERT(true);
    }
    /**
     * Test suit declaration and test case registration
     */
    BEGIN_TESTS_REGISTRATION(TestClass);
    TEST(testSimpleAssert);
    END_TESTS_REGISTRATION();//must be the last statement in the class
};

```

### CMake arguments
By default, CUTI's creates a test target for its front end and Xcode or Visual Studio unit test framework. This behavior can be customized for compatibility.
* CUTI_FRONT_END can be set to CUTI or CPPUNIT
  * CUTI: use macros starting by CUTI_
  * CPPUNIT: allow to use macros starting by CPPUNIT_. Useful if your codebase was using cppunit and you don't want to re-write everything.
* CUTI_BACK_END can be set to CUTI or CPPUNIT
  * CUTI: use Xcode or Visual Studio unit test framework as test runner
  * CPPUNIT: use cppunit as test runner. Useful if you want to run your unit tests on a platform not supported by Xcode and Visual Studio.

### Templates
Templates are available in the test directory
* [TemplateFreeStanding.cpp](./test/TemplateFreeStanding.cpp) : Shows how to write a test class when using CUTI_FRONT_END=CUTI
* [TestTemplate.cpp](./test/TestTemplate.cpp) : Shows how to write a test class when using CUTI_FRONT_END=CPPUNIT

## Contributing
Issues and merge requests are welcome !

## FAQ:

### Visual Studio

* "Message: A 64-bit test cannot run in a 32-bit process. Specify platform as X64 to force test run in X64 mode on X64 machine."
  * By default Visual Studio tries to run the unit tests target with a 32 bits test runner. But if you are compiling in 64 bits this will fail. To fix this go to: `Test -> Test Settings -> Default Processor Architecture -> X64`

### Xcode
* No test case in my test suite
  * Xcode only show test cases starting by "test". To fix either rename your test case or define CUTI_PREPEND_TEST. Take a look at [TestLibInt.cpp](./test/testDynamicLib/testCutiFrontEnd/TestLibInt.cpp) for an example.
