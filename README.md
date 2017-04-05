[![Build status](https://ci.appveyor.com/api/projects/status/g8h805xifcsauo9x/branch/master?svg=true)](https://ci.appveyor.com/project/k-brac/cuti/branch/master)
[![Build Status](https://travis-ci.org/k-brac/CUTI.svg?branch=master)](https://travis-ci.org/k-brac/CUTI)

# CUTI
CUTI stands for C++ Unit Test Integrated

## What?
CUTI allows you to easily integrate your C++ unit tests into Visual Studio and Xcode. It is also possible to use cppunit's macros and test runner through compatibility configuration.

## Why?
* You can run your tests from within your IDE
* You have visual feedback when running your tests
* It is easier to use your IDE tools with your tests like code coverage, profiling, ...
* It is easier to debug your code
* You are more likely to run your tests

## Prerequisite
* Use CMake >= 3.2
* The code to test must be compiled as a library (static or shared)

## How?
* Add CUTI's cmake directory to your CMAKE_MODULE_PATH
  * Example:
```cmake  
LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/../../cmake)
```
* Import CUTI in your CMakeLists.txt
```cmake
find_package(CUTI REQUIRED)
```
* Create a test target
```cmake
cuti_creates_test_target(test_project_name project_to_test list_of_test_files_cpp)
```
* That's it! Take a look at [./test/testDynamicLib/CMakeLists.txt](./test/testDynamicLib/CMakeLists.txt) for an example

### CMake arguments
By default, CUTI's creates atest target for its front end and Xcode or Visual Studio unit test framework. This behaviour can be customized for compatibility.
* CUTI_FRONT_END can be set to CUTI or CPPUNIT
  * CUTI: use macros starting by CUTI_
  * CPPUNIT: allow to use macros starting by CPPUNIT_. Usefull if your codebase was using cppunit and you don't want to re-write everything.
* CUTI_BACK_END can be set to CUTI or CPPUNIT
  * CUTI: use Xcode or Visual Studio unit test framework as test runner
  * CPPUNIT: use cppunit as test runner. Usefull if you want to run your unit tests on a platform not supported by Xcode and Visual Studio

## Example project
[There is a toy project in the test directory to show how to use Cuti.](./test/testDynamicLib/)

### Templates
Templates are available in the test directory
* [TemplateFreeStanding.cpp](./test/TemplateFreeStanding.cpp) : Shows how to write a test class when using CUTI_FRONT_END=CUTI
* [TestTemplate.cpp](./test/TestTemplate.cpp) : Shows how to write a test class when using CUTI_FRONT_END=CPPUNIT

## Contributing
Issues and merge requests are welcome !

## FAQ:

### Visual Studio

* "Message: A 64-bit test cannot run in a 32-bit process. Specify platform as X64 to force test run in X64 mode on X64 machine."
  * By default Visual Studio tries to run the unit tests target with a 32bit test runner. But if you are compiling in 64 bits this will fail. To fix this go to : `Test -> Test Settings -> Default Processor Architecture -> X64`

### Xcode
* No test case in my test suite
  * Xcode only show test cases starting by "test". To fix either rename you test case or define CUTI_PREPEND_TEST. Take a look at [TestLibInt.cpp](./test/testDynamicLib/testCutiFrontEnd/TestLibInt.cpp) for an example.
