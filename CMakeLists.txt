cmake_minimum_required (VERSION 3.2)

set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(CppUnit REQUIRED)

if(WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
elseif(APPLE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wshadow -Wall -Wextra")
endif(WIN32)

set(TOP_DIR ./)
set(SRC_DIR ${TOP_DIR}src/)
set(TEST_DIR ${TOP_DIR}test/)

include(./CMakeLists_test.txt)

project (Cuti)
include_directories(${CPPUNIT_INCLUDE_DIR})
add_executable(Cuti ${SRC_DIR}CutiMain.cpp)

target_link_libraries(Cuti debug ${CPPUNIT_LIBRARIES_DEBUG})
target_link_libraries(Cuti optimized ${CPPUNIT_LIBRARIES_RELEASE})
