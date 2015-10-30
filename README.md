# CUTI
CUTI stands for C++ Unit Test Integrated

## What?
CUTI is a wrapper on top of the CPPUNIT testing framework allowing you to integrate you C++ unit tests in your favorite IDE like Microsoft Visual Studio and XCode.

## How?
CUTI uses CMake to setup its include and library path.

### Visual Studio
CUTI override CPPUNIT macros, and adds a few, to use Visual Studio's cppunit test framework.

### XCode
Here it is tricky :
CUTI uses CPPUNIT test framework but implements an interface allowing to load your tests in XCode at runtime.
Unfortunately it needs some manual configuration...

### Others
CUTI uses CPPUNIT framework as backend.

## Why?
* You can run your tests from within your IDE
* You have visual feedback when running your tests
* It is easier to use your IDE tools with your tests like code coverage, profiling, ...
* It is easier to debug your code

## Prerequisite
* Use CPPUNIT as a shared library
* Use CPPUNIT plugin feature
* Use CPPUNIT macros

## Issues
* In Visual Studio, CUTI (by default) uses Visual Studio's cppunit test framework, which could have a different behavior than CPPUNIT.
* In XCode CUTI uses the objective-c runtime to find the tests at runtime, which could change the behavior of your tests. (Unverified)
* In XCode, you need to manually create a test target and setup its include and link path. These settings are overridden every-time CMake is run.

## TO DO
* Tutorial on how to use CPPUNIT
* Tutorial on how to use CUTI
* Automatic creation of XCode targets
