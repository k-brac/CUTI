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

cmake_minimum_required(VERSION 2.8)

set(CPPUNIT_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/../../cppunit")
set(CPPUNIT_DEBUG_DIR ${CPPUNIT_ROOT_DIR}/bin/Debug)
set(CPPUNIT_RELEASE_DIR ${CPPUNIT_ROOT_DIR}/bin/Release)

set(CPPUNIT_INCLUDE_DIRS ${CPPUNIT_ROOT_DIR}/include)

if(MSVC)
	string(SUBSTRING ${CMAKE_GENERATOR} 14 2 VS_VER)
	if (CMAKE_GENERATOR MATCHES Win64)
		set(VS_VER ${VS_VER}/x64)
	endif()
	set(COMPILER_NAME msvc${VS_VER})
	set(CPPUNIT_SUFFIX_DEBUG d_dll)
	set(CPPUNIT_SUFFIX_RELEASE _dll)
elseif(CMAKE_COMPILER_IS_GNUCXX)
	set(COMPILER_NAME gcc)
else()
	set(COMPILER_NAME clang)
endif()
#Release lib
get_filename_component(CPPUNIT_LIBRARIES_RELEASE ${CPPUNIT_RELEASE_DIR}/${COMPILER_NAME}/${CMAKE_SHARED_LIBRARY_PREFIX}cppunit${CPPUNIT_SUFFIX_RELEASE}${CMAKE_STATIC_LIBRARY_SUFFIX} ABSOLUTE)
get_filename_component(CPPUNIT_DYN_LIB_RELEASE ${CPPUNIT_RELEASE_DIR}/${COMPILER_NAME}/${CMAKE_SHARED_LIBRARY_PREFIX}cppunit${CPPUNIT_SUFFIX_RELEASE}${CMAKE_SHARED_LIBRARY_SUFFIX} ABSOLUTE)
#Debug lib
get_filename_component(CPPUNIT_LIBRARIES_DEBUG ${CPPUNIT_DEBUG_DIR}/${COMPILER_NAME}/${CMAKE_SHARED_LIBRARY_PREFIX}cppunit${CPPUNIT_SUFFIX_DEBUG}${CMAKE_STATIC_LIBRARY_SUFFIX} ABSOLUTE)
get_filename_component(CPPUNIT_DYN_LIB_DEBUG ${CPPUNIT_DEBUG_DIR}/${COMPILER_NAME}/${CMAKE_SHARED_LIBRARY_PREFIX}cppunit${CPPUNIT_SUFFIX_DEBUG}${CMAKE_SHARED_LIBRARY_SUFFIX} ABSOLUTE)