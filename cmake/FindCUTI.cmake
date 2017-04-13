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

#minimal version for an acceptable XCode integration
cmake_minimum_required (VERSION 3.2)

#Options to configure cuti's back end and front end
IF(WIN32 OR APPLE)
  #Defaulted to cuti front and back end for windows and mac
  set(CUTI_FRONT_END "CUTI" CACHE STRING "Select cuti's front end")
  set(CUTI_BACK_END "CUTI" CACHE STRING "Select cuti's back end")
ELSE()
  #Defaulted to cppunit front and back end other platforms
  set(CUTI_FRONT_END "CPPUNIT" CACHE STRING "Select cuti's front end")
  set(CUTI_BACK_END "CPPUNIT" CACHE STRING "Select cuti's back end")
ENDIF(WIN32 OR APPLE)

set_property(CACHE CUTI_FRONT_END PROPERTY STRINGS "CUTI" "CPPUNIT")
set_property(CACHE CUTI_BACK_END PROPERTY STRINGS "CUTI" "CPPUNIT")

string(COMPARE EQUAL "${CUTI_FRONT_END}" "CUTI" USE_CUTI_FRONT_END)
string(COMPARE EQUAL "${CUTI_BACK_END}" "CUTI" USE_CUTI_BACK_END)

set(CUTI_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/..)
set(CUTI_INCLUDE_DIRS ${CUTI_ROOT_DIR}/include)

get_filename_component(CUTI_INCLUDE ${CUTI_ROOT_DIR}/include/Cuti.h ABSOLUTE)

#this is mandatory. Otherwise XCode crashes
IF(APPLE)
  set(MACOSX_BUNDLE_GUI_IDENTIFIER "$(PRODUCT_BUNDLE_IDENTIFIER)")
ENDIF(APPLE)

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

  if(${USE_CUTI_BACK_END})
    if(MSVC)
      find_package(VisualStudio REQUIRED)
      add_library(${target} SHARED ${ARGN} ${CUTI_INCLUDE} ${CUTI_PLUGIN_SRC})
      target_include_directories(${target} PRIVATE ${MSVC_UNIT_TEST_DIR}/include)
    elseif(APPLE)
      #integrate tests to XCode
      find_package(XCTest REQUIRED)
      cuti_xctest_add_bundle(${target} ${testee} ${CUTI_SOURCE} ${ARGN} ${CUTI_INCLUDE})
      target_compile_definitions(${target} PUBLIC -DCUTI_USES_XCTEST_BACKEND)
      set_source_files_properties(${ARGN} PROPERTIES COMPILE_FLAGS "-x objective-c++")
    else()
      message(FATAL_ERROR "There is no cuti backend for the selected platform")
    endif()
  else()
    get_filename_component(CUTI_PLUGIN_SRC ${CUTI_ROOT_DIR}/src/UnitTestPlugin.cpp ABSOLUTE)
    add_library(${target} SHARED ${ARGN} ${CUTI_INCLUDE} ${CUTI_PLUGIN_SRC})
    #target_compile_definitions(${target} PUBLIC "-DCPPUNIT_PLUGIN_EXPORT=__attribute__ ((visibility (\"default\")))" )
    cuti_init_cppunit_libraries(${target})
  endif()

	target_link_libraries(${target} PRIVATE debug ${CUTI_LIBRARIES_DEBUG} ${testee})
	target_link_libraries(${target} PRIVATE optimized ${CUTI_LIBRARIES_RELEASE} ${testee})

  if(MSVC)
    target_compile_definitions(${target} PUBLIC -DCUTI_USES_MSVC_UNIT_BACKEND)
    target_compile_options(${target} PRIVATE "/Zi")
    if (MSVC_VERSION GREATER 1800)
      set_target_properties(${target} PROPERTIES LINK_FLAGS "/DEBUG:FASTLINK")
    else()
      set_target_properties(${target} PROPERTIES LINK_FLAGS "/DEBUG")
    endif()
  elseif(APPLE)
    #Enable debug information for xcode
    set_target_properties(${target} PROPERTIES XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT[variant=Debug] "dwarf")
    set_target_properties(${target} PROPERTIES XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT "dwarf-with-dsym")
    set_target_properties(${target}  PROPERTIES COMPILE_FLAGS "-g")
  endif()

  target_include_directories(${target} PUBLIC ${CUTI_INCLUDE_DIRS})

  if(${USE_CUTI_BACK_END})
    if(${USE_CUTI_FRONT_END})
      target_compile_definitions(${target} PUBLIC -DCUTI_FREE_STANDING)
    else()
      target_compile_definitions(${target} PUBLIC -DCUTI_CPPUNIT_COMPATABILITY)
    endif()
  else()
    if(${USE_CUTI_FRONT_END})
      target_compile_definitions(${target} PUBLIC -DCUTI_UNKNOWN)
    else()
      target_compile_definitions(${target} PUBLIC -DCUTI_NO_INTEGRATION)
    endif()
  endif()

endfunction(cuti_creates_test_target)

function(cuti_init_cppunit_libraries target)
    find_package(CppUnit REQUIRED)
    #code to automatically declare a cpp unit test plugin
    target_compile_definitions(${target} PUBLIC -DCUTI_USES_CPPUNIT_BACKEND)
    target_compile_definitions(${target} PUBLIC -DCPPUNIT_DLL)
    target_include_directories(${target} PUBLIC ${CPPUNIT_INCLUDE_DIRS})
    if(WIN32)
      set(CUTI_LIBRARIES_DEBUG ${CPPUNIT_LIBRARIES_DEBUG} PARENT_SCOPE)
      set(CUTI_LIBRARIES_RELEASE ${CPPUNIT_LIBRARIES_RELEASE} PARENT_SCOPE)
    else()
      set(CUTI_LIBRARIES_DEBUG ${CPPUNIT_DYN_LIB_DEBUG} PARENT_SCOPE)
      set(CUTI_LIBRARIES_RELEASE ${CPPUNIT_DYN_LIB_RELEASE} PARENT_SCOPE)
    endif()
endfunction(cuti_init_cppunit_libraries)
