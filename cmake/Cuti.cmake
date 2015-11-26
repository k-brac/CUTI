cmake_minimum_required (VERSION 3.2)

option(USE_CUTI_INTEGRATION "Use IDE test integration (Cuti)" ON)

set(CUTI_INCLUDE_DIRS ${CUTI_TOP_DIR}include)

IF(USE_CUTI_INTEGRATION AND WIN32)
	find_package(VisualStudio REQUIRED)
	add_definitions(-DCUTI_USES_MSVC_UNIT_BACKEND)
	add_definitions(-DCUTI_EXCLUDE_TEST_FROM_COVERAGE)
	add_definitions(-DCUTI_WARNING_UNIMPLEMENTED)
	set(CUTI_UNIT_TEST_LIBRARIES_DEBUG ${MSVC_UNIT_TEST_LIB})
	set(CUTI_UNIT_TEST_LIBRARIES_RELEASE ${MSVC_UNIT_TEST_LIB})
ELSE()
	find_package(CppUnit REQUIRED)
	add_definitions(-DCUTI_USES_CPPUNIT_BACKEND)
	add_definitions(-DCPPUNIT_DLL)
	set(CUTI_UNIT_TEST_LIBRARIES_DEBUG ${CPPUNIT_LIBRARIES_DEBUG})
	set(CUTI_UNIT_TEST_LIBRARIES_RELEASE ${CPPUNIT_LIBRARIES_RELEASE})
ENDIF(USE_CUTI_INTEGRATION AND WIN32)

include_directories(${CUTI_INCLUDE_DIRS})
get_filename_component(CUTI_INCLUDE ${CUTI_TOP_DIR}include/Cuti.h ABSOLUTE)
IF(USE_CUTI_INTEGRATION AND APPLE)
	get_filename_component(CUTI_SOURCE ${CUTI_TOP_DIR}src/Cuti.mm ABSOLUTE)
	set_source_files_properties(${CUTI_SOURCE} PROPERTIES COMPILE_FLAGS "-x objective-c++")
ENDIF(USE_CUTI_INTEGRATION AND APPLE)

function(cuti_creates_test_target target testee)
	IF(USE_CUTI_INTEGRATION AND APPLE)
		find_package(XCTest REQUIRED)
		set(MACOSX_BUNDLE_GUI_IDENTIFIER "cuti.bundle.identifier")
		set_target_properties(${testee} PROPERTIES
			FRAMEWORK TRUE
			VERSION "1.0.0"
			SOVERSION "1.0.0"
			FRAMEWORK_VERSION "A"
		)
		xctest_add_bundle(${target} ${testee} ${CUTI_SOURCE} ${ARGN} ${CUTI_INCLUDE})
	ELSE()
		add_library(${target} SHARED ${ARGN} ${CUTI_INCLUDE})
	ENDIF(USE_CUTI_INTEGRATION AND APPLE)

	target_link_libraries(${target} PRIVATE debug ${CUTI_UNIT_TEST_LIBRARIES_DEBUG} ${testee})
	target_link_libraries(${target} PRIVATE optimized ${CUTI_UNIT_TEST_LIBRARIES_RELEASE} ${testee})
endfunction(cuti_creates_test_target)
