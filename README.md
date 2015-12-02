# CUTI
CUTI stands for C++ Unit Test Integrated

## What?
CUTI is a wrapper on top of the CPPUNIT testing framework allowing you to integrate you C++ unit tests in your favorite IDE like Microsoft Visual Studio and XCode.

## How?
CUTI uses CMake to setup its include and library path.

### Visual Studio
CUTI override CPPUNIT macros, and adds a few, to use Visual Studio's cppunit test framework instead of CPPUNIT.

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

## TO DO
* Tutorial on how to use CPPUNIT
* Tutorial on how to use CUTI
