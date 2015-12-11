# CUTI
CUTI stands for C++ Unit Test Integrated

## What?
CUTI is a wrapper on top of the CPPUNIT testing framework allowing you to integrate your C++ unit tests in your favorite IDE like Microsoft Visual Studio and XCode.

## How?
CUTI uses CMake to setup its include and library path.

### Visual Studio
CUTI overrides CPPUNIT macros, and adds a few, to use Visual Studio's cppunit test framework instead of CPPUNIT.

### XCode
CUTI uses the CPPUNIT test framework with a special test runner to dynamically register your test in XCode.

### Others
CUTI uses CPPUNIT framework as backend.

## Why?
* You can run your tests from within your IDE
* You have visual feedback when running your tests
* It is easier to use your IDE tools with your tests like code coverage, profiling, ...
* It is easier to debug your code
* You are more likely to run your tests

## Prerequisite
* Use CPPUNIT as a shared library
* Use CPPUNIT plugin feature
* Use CPPUNIT macros
* Use CMake
* The code to test must be compiled as a library (static or shared)
* The test code must be compiled as a library (static or shared)

##Setup
There is a toy project in the test directory to show how to use Cuti.

###CMake
The minimum version of CMake compatible is 3.2
In your CMAKE_MODULE_PATH you can add a file named findCUTI.cmake that points to your local Cuti directory and includes Cuti.cmake frome the cmake directory.
Then in your test project you need to call :

cuti_creates_test_target(test_compute_lib compute_lib ${TEST_LIB_SRC})

* test_compute_lib : your test project declared this way : project(test_compute_lib)
* compute_lib : your project to test declared this way : project(compute_lib)
* ${TEST_LIB_SRC} : the list of your tests' source files

###Test source files
* Replace all the CPPUNIT includes by "Cuti.h"
* Declare your test class using CUTI_TEST_CLASS(TestClass) instead of TestClass : public CppUnit::TestFixture

###Compile and run your tests
There is nothing else !
