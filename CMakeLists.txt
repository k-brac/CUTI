cmake_minimum_required (VERSION 3.2)

set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

if(WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif(WIN32)

set(TOP_DIR ./)
set(SRC_DIR ${TOP_DIR}src/)
set(INCLUDE_DIR ${TOP_DIR}include/)
set(TEST_DIR ${TOP_DIR}test/)

include_directories(${TOP_DIR}cppunit/include)
set(CPPUNIT_LIBRARIES_DEBUG .${TOP_DIR}cppunit/lib/cppunitd_dll)
set(CPPUNIT_LIBRARIES_RELEASE .${TOP_DIR}cppunit/lib/cppunit_dll)

project (Cuti)
include_directories(${CPPUNIT_TOP_DIR}include)

add_executable(Cuti ${SRC_DIR}CutiMain.cpp)

target_link_libraries(Cuti debug ${CPPUNIT_LIBRARIES_DEBUG})
target_link_libraries(Cuti optimized ${CPPUNIT_LIBRARIES_RELEASE})

add_subdirectory(${TEST_DIR}testStaticLib)
