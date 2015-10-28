cmake_minimum_required(VERSION 2.8)

set(CPPUNIT_ROOT_DIR ./cppunit/)

get_filename_component(CPPUNIT_INCLUDE_DIR ${CPPUNIT_ROOT_DIR}include ABSOLUTE)
include_directories(${CPPUNIT_INCLUDE_DIR})
if(WIN32)
	get_filename_component(CPPUNIT_LIBRARIES_DEBUG ${CPPUNIT_ROOT_DIR}lib/cppunitd_dll.lib ABSOLUTE)
	get_filename_component(CPPUNIT_LIBRARIES_RELEASE ${CPPUNIT_ROOT_DIR}lib/cppunit_dll.lib ABSOLUTE)
else(WIN32)
	get_filename_component(CPPUNIT_LIBRARIES_DEBUG ${CPPUNIT_ROOT_DIR}lib/libcppunit.a ABSOLUTE)
	get_filename_component(CPPUNIT_LIBRARIES_RELEASE ${CPPUNIT_ROOT_DIR}lib/libcppunit.a ABSOLUTE)
endif(WIN32)
