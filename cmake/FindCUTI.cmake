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

IF(WIN32 OR APPLE)
  #Defaulted to ON for windows and mac
  option(USE_CUTI_INTEGRATION "Use IDE test integration (Cuti)" ON)
ELSE()
  #Defaulted to OFF for the rest because there is no integration
  option(USE_CUTI_INTEGRATION "Use IDE test integration (Cuti)" OFF)
ENDIF(WIN32 OR APPLE)

set(CUTI_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/..)
set(CUTI_INCLUDE_DIRS ${CUTI_ROOT_DIR}/include)

IF(USE_CUTI_INTEGRATION AND WIN32)
  find_package(VisualStudio REQUIRED)
  #Code coverage is only available in the enterprise edition so we default to false
  option(EXCLUDE_TEST_FROM_COVERAGE "Exclude tests from coverage (Cuti)" OFF)
  set(CUTI_LIBRARIES_DEBUG ${MSVC_UNIT_TEST_LIB})
  set(CUTI_LIBRARIES_RELEASE ${MSVC_UNIT_TEST_LIB})
ELSE()
  find_package(CppUnit REQUIRED)
  IF(USE_CUTI_INTEGRATION OR WIN32)
    set(CUTI_LIBRARIES_DEBUG ${CPPUNIT_LIBRARIES_DEBUG})
    set(CUTI_LIBRARIES_RELEASE ${CPPUNIT_LIBRARIES_RELEASE})
  ELSE()
    set(CUTI_LIBRARIES_DEBUG ${CPPUNIT_DYN_LIB_DEBUG})
    set(CUTI_LIBRARIES_RELEASE ${CPPUNIT_DYN_LIB_RELEASE})
  ENDIF()
ENDIF(USE_CUTI_INTEGRATION AND WIN32)

get_filename_component(CUTI_INCLUDE ${CUTI_ROOT_DIR}/include/Cuti.h ABSOLUTE)

IF(USE_CUTI_INTEGRATION AND APPLE)
  set(MACOSX_BUNDLE_GUI_IDENTIFIER "$(PRODUCT_BUNDLE_IDENTIFIER)")
ENDIF(USE_CUTI_INTEGRATION AND APPLE)

function(cuti_init_target_flags target)
#Set all the flags needed by cuti to the test target
  IF(USE_CUTI_INTEGRATION AND WIN32)
    target_compile_definitions(${target} PUBLIC -DCUTI_USES_MSVC_UNIT_BACKEND)
      IF(EXCLUDE_TEST_FROM_COVERAGE)
        target_compile_definitions(${target} PUBLIC -DCUTI_EXCLUDE_TEST_FROM_COVERAGE)
      ENDIF(EXCLUDE_TEST_FROM_COVERAGE)
    target_compile_definitions(${target} PUBLIC -DCUTI_WARNING_UNIMPLEMENTED)
  ELSE()
    target_compile_definitions(${target} PUBLIC -DCUTI_USES_CPPUNIT_BACKEND)
    target_compile_definitions(${target} PUBLIC -DCPPUNIT_DLL)
    target_include_directories(${target} PUBLIC ${CPPUNIT_INCLUDE_DIRS})
  ENDIF(USE_CUTI_INTEGRATION AND WIN32)
  target_include_directories(${target} PUBLIC ${CUTI_INCLUDE_DIRS})
  #Enable debug information for xcode
  set_target_properties (${target} PROPERTIES XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT[variant=Debug] "dwarf")
  set_target_properties (${target} PROPERTIES XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT "dwarf-with-dsym")
endfunction(cuti_init_target_flags)

function(cuti_xctest_add_bundle target testee)
  #creates a test bundle ${target} for the testee target
  #uses ${ARGN} as list of source files for the test target
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

  if(_testee_type STREQUAL "SHARED_LIBRARY" OR _testee_type STREQUAL "STATIC_LIBRARY" )
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
  #creates a test target for the testee target
  #uses ${ARGN} as list of source files for the test target
	if(USE_CUTI_INTEGRATION AND APPLE)
    #integrate tests to XCode
		find_package(XCTest REQUIRED)
		cuti_xctest_add_bundle(${target} ${testee} ${CUTI_SOURCE} ${ARGN} ${CUTI_INCLUDE})
    target_compile_definitions(${target} PUBLIC -DCUTI_USES_XCTEST_BACKEND)
    set_source_files_properties(${ARGN} PROPERTIES COMPILE_FLAGS "-x objective-c++")
	else()
    if(NOT USE_CUTI_INTEGRATION)
      #code to automatically declare a cpp unit test plugin
      get_filename_component(CUTI_PLUGIN_SRC ${CUTI_ROOT_DIR}/src/UnitTestPlugin.cpp ABSOLUTE)      
    endif(NOT USE_CUTI_INTEGRATION)
    add_library(${target} SHARED ${ARGN} ${CUTI_INCLUDE} ${CUTI_PLUGIN_SRC})
    target_compile_definitions(${target} PUBLIC "-DCPPUNIT_PLUGIN_EXPORT=__attribute__ ((visibility (\"default\")))" )
	endif(USE_CUTI_INTEGRATION AND APPLE)

	target_link_libraries(${target} PRIVATE debug ${CUTI_LIBRARIES_DEBUG} ${testee})
	target_link_libraries(${target} PRIVATE optimized ${CUTI_LIBRARIES_RELEASE} ${testee})
  cuti_init_target_flags(${target})
endfunction(cuti_creates_test_target)
