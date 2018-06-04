#The MIT License (MIT)
#
#Copyright (c) 2015 k-brac
#
#Permission is hereby granted, free of charge, to any person obtaining a copy
#of this software and associated documentation files (the "Software"), to deal
#in the Software without restriction, including without limitation the rights
#to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#copies of the Software, and to permit persons to whom the Software is
#furnished to do so, subject to the following conditions:
#
#The above copyright notice and this permission notice shall be included in all
#copies or substantial portions of the Software.
#
#THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#SOFTWARE.


#CMake example file to show how to setup a project and its test to use Cuti
cmake_minimum_required (VERSION 3.2)

#define the resource path
set(TEST_TOP_DIR .)
set(TEST_SRC_DIR ${TEST_TOP_DIR}/src)
set(TEST_INCLUDE_DIR ${TEST_TOP_DIR}/include)
set(TEST_CPPUNIT_DIR ${TEST_TOP_DIR}/testCppunitFrontEnd)
set(TEST_CUTI_DIR ${TEST_TOP_DIR}/testCutiFrontEnd)

#create the project we want to test
project (testDynamicLib)

#This add_subdirectory needs to be done after a call to projetc otherwise ${CMAKE_VS_DEVENV_COMMAND} is empty
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../../   ${CMAKE_BINARY_DIR}/cuti)
include_directories(${TEST_INCLUDE_DIR})
set(DYNAMIC_LIB_SRC
    ${TEST_SRC_DIR}/ComputeInt.cpp
    ${TEST_SRC_DIR}/ComputeDouble.cpp
    ${TEST_SRC_DIR}/ComputeFloat.cpp
)

set(DYNAMIC_LIB_INCLUDE
    ${TEST_INCLUDE_DIR}/ComputeInt.h
    ${TEST_INCLUDE_DIR}/ComputeDouble.h
    ${TEST_INCLUDE_DIR}/ComputeFloat.h
    ${TEST_INCLUDE_DIR}/DynamicLib.h
)

add_library(DynamicLib SHARED ${DYNAMIC_LIB_SRC} ${DYNAMIC_LIB_INCLUDE})

#put all the test source files in a variable
set(TEST_CPPUNIT_LIB_SRC
    ${TEST_CPPUNIT_DIR}/TestLibInt.cpp
    ${TEST_CPPUNIT_DIR}/TestLibFloat.cpp
    ${TEST_CPPUNIT_DIR}/TestLibDouble.cpp
    ${TEST_TOP_DIR}/../TestTemplate.cpp
)

set(TEST_CUTI_LIB_SRC 
    ${TEST_CUTI_DIR}/TestLibInt.cpp
    ${TEST_CUTI_DIR}/TestLibFloat.cpp
    ${TEST_CUTI_DIR}/TestLibDouble.cpp
    ${TEST_TOP_DIR}/../TemplateFreeStanding.cpp
)

include_directories(${TEST_INCLUDE_DIR})

#creates the test target to be integrated in Visual Studio and XCode
set(USE_CUTI_FRONT_END FALSE)#Hardcode our choice of frontend
cuti_creates_test_target(testCppunit DynamicLib ${TEST_CPPUNIT_LIB_SRC})
target_compile_definitions(testCppunit PRIVATE CUTI_CPPUNIT_COMPATABILITY)

set(USE_CUTI_FRONT_END TRUE)#Hardcode our choice of frontend
cuti_creates_test_target(testCuti DynamicLib ${TEST_CUTI_LIB_SRC})

#Various compilation configurations
if(WIN32)
    target_compile_options(DynamicLib PRIVATE "/W4" "/MP" "/analyze")
    target_compile_options(testCppunit PRIVATE "/W4" "/MP" "/analyze")
    target_compile_options(testCuti PRIVATE "/W4" "/MP" "/analyze")
    #Definition for windows to enable the generation of a dll and its lib
    target_compile_definitions(DynamicLib PRIVATE -DCOMPUTE_EXPORT)
    if(MSVC_VERSION GREATER 1900)
        target_compile_options(DynamicLib PRIVATE "/permissive-")
        target_compile_options(testCppunit PRIVATE "/permissive-")
        target_compile_options(testCuti PRIVATE "/permissive-")
    endif()
elseif(APPLE)
    target_compile_options(DynamicLib PRIVATE -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic)
    target_compile_options(testCppunit PRIVATE
        -Weverything
        -Wno-c++98-compat
        -std=c++14
        -Wno-c++98-compat-pedantic
        -Wno-gnu
    )
    target_compile_options(testCuti PRIVATE
        -Weverything
        -Wno-c++98-compat
        -std=c++14
        -Wno-c++98-compat-pedantic
        -Wno-gnu
    )
    set_target_properties (DynamicLib PROPERTIES XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT[variant=Debug] "dwarf")
    set_target_properties (DynamicLib PROPERTIES XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT "dwarf-with-dsym")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g")
endif(WIN32)
