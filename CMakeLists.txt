#The MIT License (MIT)
#
#Copyright (c) 2018 k-brac
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

if(CUTI_INCLUDE_GUARD)
	return()
endif()
set(CUTI_INCLUDE_GUARD ON)

#Options to configure cuti's back end and front end
if(WIN32 OR APPLE)
	#Defaulted to cuti front and back end for windows and mac
	set(CUTI_FRONT_END "CUTI" CACHE STRING "Select cuti's front end")
	set(CUTI_BACK_END "CUTI" CACHE STRING "Select cuti's back end")
else()
	#Defaulted to cppunit front and back end other platforms
	set(CUTI_FRONT_END "CPPUNIT" CACHE STRING "Select cuti's front end")
	set(CUTI_BACK_END "CPPUNIT" CACHE STRING "Select cuti's back end")
endif(WIN32 OR APPLE)

set(CUTI_PATH_TO_CPPUNIT_ROOT "" CACHE STRING "Provide a path to cppunit root directory (optional)")
set(CUTI_PATH_TO_CPPUNIT_BIN "" CACHE STRING "Provide a path to cppunit binary directory (optional)")

option(CUTI_USE_LONG_MACRO_NAME "Select wether you want to use long macro names" OFF)

set_property(CACHE CUTI_FRONT_END PROPERTY STRINGS "CUTI" "CPPUNIT")
set_property(CACHE CUTI_BACK_END PROPERTY STRINGS "CUTI" "CPPUNIT")

string(COMPARE EQUAL "${CUTI_FRONT_END}" "CUTI" USE_CUTI_FRONT_END)
string(COMPARE EQUAL "${CUTI_BACK_END}" "CUTI" USE_CUTI_BACK_END)

if(TARGET cuti)
	return()
endif()

function(cuti_target_properties target testee)
#set some custom properties to target
	if(APPLE)
		if(${USE_CUTI_BACK_END})
			set_target_properties(${target} PROPERTIES
				BUNDLE TRUE
				XCTEST TRUE
				XCTEST_TESTEE ${testee}
			)
		endif()
		set_target_properties(${target} PROPERTIES
			XCODE_ATTRIBUTE_STRIP_STYLE "non-global"
		)
	endif()
endfunction(cuti_target_properties)

function(cuti_init_devenv_path)
	if (NOT CUTI_VS_DEVENV_COMMAND)
		if (CMAKE_VS_DEVENV_COMMAND)
			get_filename_component(CUTI_VS_DEVENV_COMMAND ${CMAKE_VS_DEVENV_COMMAND} DIRECTORY CACHE)
		elseif(MSVC_VERSION)
			get_filename_component(CUTI_VS_DEVENV_COMMAND ${CMAKE_CXX_COMPILER} DIRECTORY)
			set(CUTI_VS_DEVENV_COMMAND ${CUTI_VS_DEVENV_COMMAND}/../../../../.. PARENT_SCOPE)
		endif()
	endif()
endfunction(cuti_init_devenv_path)

function(cuti_add_test_target target testee)
#creates a test target for the testee target
#uses ${ARGN} as list of source files for the test target

	if(WIN32)
		cuti_init_devenv_path()
		if (MSVC_VERSION LESS 1910)
			link_directories("${CUTI_VS_DEVENV_COMMAND}/../../VC/UnitTest/lib")
		else()
			link_directories("${CUTI_VS_DEVENV_COMMAND}/../../VC/Auxiliary/VS/UnitTest/lib")
		endif()
	endif()

	add_library(${target} MODULE ${ARGN})
	target_link_libraries(${target} PRIVATE ${testee} cuti)

	cuti_target_properties(${target} ${testee})

	if(TARGET Cuti)
		#create a dependency between test target and Cuti test runner
		add_dependencies(${target} Cuti)
	endif()
endfunction(cuti_add_test_target)

#this is mandatory. Otherwise XCode crashes
if(APPLE)
	set(MACOSX_BUNDLE_GUI_IDENTIFIER "$(PRODUCT_BUNDLE_IDENTIFIER)")
endif(APPLE)


add_library(cuti INTERFACE)
target_include_directories(cuti INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>)
target_sources(cuti INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/Cuti.h>)

if(WIN32 AND ${USE_CUTI_BACK_END})
	cuti_init_devenv_path()
	if(MSVC_VERSION LESS 1910)
		target_include_directories(cuti INTERFACE "${CUTI_VS_DEVENV_COMMAND}/../../VC/UnitTest/include")
	else()
		target_include_directories(cuti INTERFACE "${CUTI_VS_DEVENV_COMMAND}/../../VC/Auxiliary/VS/UnitTest/include")
	endif()
endif()

if(WIN32)
	target_compile_definitions(cuti INTERFACE
		$<IF:${USE_CUTI_BACK_END},
			CUTI_USES_MSVC_UNIT_BACKEND,
			"CPPUNIT_PLUGIN_EXPORT=__attribute__((visibility(\"default\")))"
			CUTI_USES_CPPUNIT_BACKEND
			CPPUNIT_DLL
		>
	)
elseif(${APPLE})
	target_compile_definitions(cuti INTERFACE
		$<IF:${USE_CUTI_BACK_END},
			CUTI_USES_XCTEST_BACKEND,
			"CPPUNIT_PLUGIN_EXPORT=__attribute__((visibility(\"default\")))"
			CUTI_USES_CPPUNIT_BACKEND
			CPPUNIT_DLL
		>
	)
	if(${USE_CUTI_BACK_END})
		find_package(XCTest REQUIRED)
		if(NOT XCTest_FOUND)
			message(FATAL_ERROR "XCTest is required to create a XCTest Bundle.")
		endif()
		target_link_libraries(cuti INTERFACE "-framework Foundation")
		target_link_libraries(cuti INTERFACE ${XCTest_LIBRARIES})
		target_include_directories(cuti INTERFACE ${XCTest_INCLUDE_DIRS})
		target_compile_options(cuti BEFORE INTERFACE -x objective-c++)
	endif()
	target_compile_options(cuti INTERFACE -Wno-gnu-zero-variadic-macro-arguments -Wno-gnu-statement-expression)
else()
	target_compile_definitions(cuti INTERFACE
		"CPPUNIT_PLUGIN_EXPORT=__attribute__((visibility(\"default\")))"
		CUTI_USES_CPPUNIT_BACKEND
		CPPUNIT_DLL
	)
endif()

target_compile_definitions(cuti INTERFACE
	$<IF:${USE_CUTI_BACK_END},
		$<IF:${USE_CUTI_FRONT_END},
			CUTI_FREE_STANDING,
			CUTI_CPPUNIT_COMPATABILITY
		>,
		$<IF:${USE_CUTI_FRONT_END},
			CUTI_UNKNOWN,
			CUTI_NO_INTEGRATION
		>
	>
)

target_compile_definitions(cuti INTERFACE $<$<BOOL:${CUTI_USE_LONG_MACRO_NAME}>:CUTI_USE_LONG_MACRO_NAME>)

#Special case to use cppunit as backend
if(NOT ${USE_CUTI_BACK_END})
	if("${CUTI_PATH_TO_CPPUNIT_ROOT}" STREQUAL "")
		set(CUTI_PATH_TO_CPPUNIT_ROOT ${CMAKE_CURRENT_LIST_DIR}/../cppunit)
	endif()
	if("${CUTI_PATH_TO_CPPUNIT_BIN}" STREQUAL "")
		set(CUTI_PATH_TO_CPPUNIT_BIN ${CMAKE_CURRENT_LIST_DIR}/../cppunit/bin)
	endif()

	if(MSVC)
		string(SUBSTRING ${CMAKE_GENERATOR} 14 2 VS_VER)
		set(CUTI_COMPILER_NAME msvc${VS_VER})
	elseif(CMAKE_COMPILER_IS_GNUCXX)
		set(CUTI_COMPILER_NAME gcc)
	else()
		set(CUTI_COMPILER_NAME clang)
	endif()

	set(CPPUNIT_ARCH_DIR $<$<AND:$<NOT:$<BOOL:${APPLE}>>,$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>>:x64>)

	target_include_directories(cuti INTERFACE ${CUTI_PATH_TO_CPPUNIT_ROOT}/include)
	set(CPPUNIT_DYN_LIB_DEBUG ${CUTI_PATH_TO_CPPUNIT_BIN}/Debug/${CUTI_COMPILER_NAME}/${CPPUNIT_ARCH_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}cppunit$<$<BOOL:${WIN32}>:d_dll>${CMAKE_SHARED_LIBRARY_SUFFIX})
	set(CPPUNIT_DYN_LIB_RELEASE ${CUTI_PATH_TO_CPPUNIT_BIN}/Release/${CUTI_COMPILER_NAME}/${CPPUNIT_ARCH_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}cppunit$<$<BOOL:${WIN32}>:_dll>${CMAKE_SHARED_LIBRARY_SUFFIX})
	target_link_libraries(cuti INTERFACE
		debug ${CPPUNIT_DYN_LIB_DEBUG}
		optimized ${CPPUNIT_DYN_LIB_RELEASE}
	)

	target_sources(cuti INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src/UnitTestPlugin.cpp>)
	
	if(NOT TARGET Cuti)
		add_executable(Cuti ${CMAKE_CURRENT_LIST_DIR}/src/CutiMain.cpp)
		target_include_directories(Cuti PRIVATE ${CUTI_PATH_TO_CPPUNIT_ROOT}/include)
		target_link_libraries(Cuti PRIVATE
			debug ${CPPUNIT_DYN_LIB_DEBUG}
			optimized ${CPPUNIT_DYN_LIB_RELEASE}
		)
		set(CUTI_COPY_LIB $<$<CONFIG:Debug>:${CPPUNIT_DYN_LIB_DEBUG}> $<$<NOT:$<CONFIG:Debug>>:${CPPUNIT_DYN_LIB_RELEASE}>)
		#copy cppunit dll to current build dir
		add_custom_command(TARGET Cuti POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CUTI_COPY_LIB} $<TARGET_FILE_DIR:Cuti>)
	endif()
endif()
