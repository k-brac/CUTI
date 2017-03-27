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

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/../../cmake)

find_package(CUTI REQUIRED)

if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
elseif(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wshadow -Wall -Wextra -std=c++14")

endif(WIN32)

#define the resource path
set(TEST_TOP_DIR .)
set(TEST_SRC_DIR ${TEST_TOP_DIR}/src)
set(TEST_INCLUDE_DIR ${TEST_TOP_DIR}/include)
set(TEST_DIR ${TEST_TOP_DIR}/test)

#create the project we want to test
project (DynamicLib)
include_directories(${TEST_INCLUDE_DIR})
set(DYNAMIC_LIB_SRC
    ${TEST_SRC_DIR}/ComputeInt.cpp
    ${TEST_SRC_DIR}/ComputeDouble.cpp
    ${TEST_SRC_DIR}/ComputeFloat.cpp
)

set(DYNAMIC_LIB_INCLUDE ${TEST_INCLUDE_DIR}/ComputeInt.h ${TEST_INCLUDE_DIR}/ComputeDouble.h ${TEST_INCLUDE_DIR}/ComputeFloat.h ${TEST_INCLUDE_DIR}/DynamicLib.h)

add_library(DynamicLib SHARED ${DYNAMIC_LIB_SRC} ${DYNAMIC_LIB_INCLUDE})

#put all the test source files in a variable
set(TEST_LIB_SRC
    ${TEST_DIR}/TestLibInt.cpp
    ${TEST_DIR}/TestLibFloat.cpp
    ${TEST_DIR}/TestLibDouble.cpp
    ${TEST_TOP_DIR}/../TestTemplate.cpp
)

include_directories(${TEST_INCLUDE_DIR})

#creates the test target to be integrated in Visual Studio and XCode
cuti_creates_test_target(testDynamicLib DynamicLib ${TEST_LIB_SRC})

if(WIN32)
    target_compile_options(compute_lib PRIVATE "/W4" "/MP" "/analyze")
    target_compile_options(testDynamicLib PRIVATE "/W4" "/MP" "/analyze")
    #Definition for windows to enable the generation of a dll and its lib
    target_compile_definitions(DynamicLib PRIVATE -DCOMPUTE_EXPORT)
elseif(APPLE)
    target_compile_options(DynamicLib PRIVATE -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic)
    target_compile_options(testDynamicLib PRIVATE
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
