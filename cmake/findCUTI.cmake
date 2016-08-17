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

cmake_minimum_required (VERSION 3.2)

option(USE_CUTI_INTEGRATION "Use IDE test integration (Cuti)" ON)

set(CUTI_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/..)
set(CUTI_INCLUDE_DIRS ${CUTI_ROOT_DIR}/include)

IF(USE_CUTI_INTEGRATION AND WIN32)
	find_package(VisualStudio REQUIRED)
	add_definitions(-DCUTI_USES_MSVC_UNIT_BACKEND)
    option(EXCLUDE_TEST_FROM_COVERAGE "Exclude tests from coverage (Cuti)" OFF)
    IF(EXCLUDE_TEST_FROM_COVERAGE)
	    add_definitions(-DCUTI_EXCLUDE_TEST_FROM_COVERAGE)
    ENDIF(EXCLUDE_TEST_FROM_COVERAGE)
	add_definitions(-DCUTI_WARNING_UNIMPLEMENTED)
  set(CUTI_LIBRARIES_DEBUG ${MSVC_UNIT_TEST_LIB})
	set(CUTI_LIBRARIES_RELEASE ${MSVC_UNIT_TEST_LIB})
ELSE()
	find_package(CppUnit REQUIRED)
	add_definitions(-DCUTI_USES_CPPUNIT_BACKEND)
	add_definitions(-DCPPUNIT_DLL)
  IF(USE_CUTI_INTEGRATION)
	  set(CUTI_LIBRARIES_DEBUG ${CPPUNIT_LIBRARIES_DEBUG})
	  set(CUTI_LIBRARIES_RELEASE ${CPPUNIT_LIBRARIES_RELEASE})
  ELSE()
    set(CUTI_LIBRARIES_DEBUG ${CPPUNIT_DYN_LIB_DEBUG})
	  set(CUTI_LIBRARIES_RELEASE ${CPPUNIT_DYN_LIB_RELEASE})
  ENDIF()
  include_directories(${CPPUNIT_INCLUDE_DIRS})
ENDIF(USE_CUTI_INTEGRATION AND WIN32)

include_directories(${CUTI_INCLUDE_DIRS})
get_filename_component(CUTI_INCLUDE ${CUTI_ROOT_DIR}/include/Cuti.h ABSOLUTE)
IF(USE_CUTI_INTEGRATION AND APPLE)
	get_filename_component(CUTI_SOURCE ${CUTI_ROOT_DIR}/src/Cuti.mm ABSOLUTE)
	set_source_files_properties(${CUTI_SOURCE} PROPERTIES COMPILE_FLAGS "-x objective-c++")
ENDIF(USE_CUTI_INTEGRATION AND APPLE)

function(cuti_xctest_add_bundle target testee)
  if(NOT XCTest_FOUND)
    message(FATAL_ERROR "XCTest is required to create a XCTest Bundle.")
  endif(NOT XCTest_FOUND)

  if(NOT CMAKE_OSX_SYSROOT)
    message(FATAL_ERROR "Adding XCTest bundles requires CMAKE_OSX_SYSROOT to be set.")
  endif()

  add_library(${target} MODULE ${ARGN})

  set_target_properties(${target} PROPERTIES
    BUNDLE TRUE
    XCTEST TRUE
    XCTEST_TESTEE ${testee})

  target_link_libraries(${target} PRIVATE "-framework Foundation")
  target_link_libraries(${target} PRIVATE ${XCTest_LIBRARIES})
  target_include_directories(${target} PRIVATE ${XCTest_INCLUDE_DIRS})

  # retrieve testee target type
  if(NOT TARGET ${testee})
    message(FATAL_ERROR "${testee} is not a target.")
  endif()
  get_property(_testee_type TARGET ${testee} PROPERTY TYPE)
  get_property(_testee_framework TARGET ${testee} PROPERTY FRAMEWORK)
  get_property(_testee_macosx_bundle TARGET ${testee} PROPERTY MACOSX_BUNDLE)

  if(_testee_type STREQUAL "SHARED_LIBRARY" OR _testee_type STREQUAL "STATIC_LIBRARY" AND _testee_framework)
    # testee is a Framework
    target_link_libraries(${target} PRIVATE ${testee})

  elseif(_testee_type STREQUAL "EXECUTABLE" AND _testee_macosx_bundle)
    # testee is an App Bundle
    add_dependencies(${target} ${testee})
    if(XCODE)
      set_target_properties(${target} PROPERTIES
        XCODE_ATTRIBUTE_BUNDLE_LOADER "$(TEST_HOST)"
        XCODE_ATTRIBUTE_TEST_HOST "$<TARGET_FILE:${testee}>")
    else(XCODE)
      target_link_libraries(${target}
        PRIVATE -bundle_loader $<TARGET_FILE:${testee}>)
    endif(XCODE)

  else()
    message(FATAL_ERROR "Testee ${testee} is of unsupported type.")
  endif()
endfunction(cuti_xctest_add_bundle)

function(cuti_creates_test_target target testee)
	IF(USE_CUTI_INTEGRATION AND APPLE)
		find_package(XCTest REQUIRED)
		set_target_properties(${testee} PROPERTIES
			FRAMEWORK TRUE
			VERSION "1.0.0"
			SOVERSION "1.0.0"
			FRAMEWORK_VERSION "A"
		)
		cuti_xctest_add_bundle(${target} ${testee} ${CUTI_SOURCE} ${ARGN} ${CUTI_INCLUDE})
    set(MACOSX_BUNDLE_GUI_IDENTIFIER ${target}.bundle.identifier)
	ELSE()
    add_library(${target} SHARED ${ARGN} ${CUTI_INCLUDE})
    target_compile_definitions(${target} PUBLIC "-DCPPUNIT_PLUGIN_EXPORT=__attribute__ ((visibility (\"default\")))" )
	ENDIF(USE_CUTI_INTEGRATION AND APPLE)

	target_link_libraries(${target} PRIVATE debug ${CUTI_LIBRARIES_DEBUG} ${testee})
	target_link_libraries(${target} PRIVATE optimized ${CUTI_LIBRARIES_RELEASE} ${testee})
endfunction(cuti_creates_test_target)
