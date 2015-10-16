cmake_minimum_required (VERSION 3.2)

#set(CUTI_USES_MSVC_UNIT_BACKEND ON)
find_package(CUTI REQUIRED)

if(WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif(WIN32)

set(TOP_DIR ./)
set(SRC_DIR ${TOP_DIR}src/)
set(INCLUDE_DIR ${TOP_DIR}include/)
set(TEST_DIR ${TOP_DIR}test/)

project (compute_lib)
include_directories(${INCLUDE_DIR})
set(COMPUTE_LIB_SRC ${SRC_DIR}ComputeInt.cpp ${SRC_DIR}ComputeDouble.cpp ${SRC_DIR}ComputeFloat.cpp)
set(COMPUTE_LIB_INCLUDE ${INCLUDE_DIR}ComputeInt.h ${INCLUDE_DIR}ComputeDouble.h ${INCLUDE_DIR}ComputeFloat.h)
add_library(compute_lib STATIC ${COMPUTE_LIB_SRC} ${COMPUTE_LIB_INCLUDE})

project(test_compute_lib)

set(TEST_LIB_SRC ${TEST_DIR}TestLibInt.cpp ${TEST_DIR}TestLibFloat.cpp ${TEST_DIR}TestLibDouble.cpp ${CUTI_INCLUDE})

include_directories(${INCLUDE_DIR})

add_library(test_compute_lib SHARED ${TEST_LIB_SRC} ${TEST_DIR}TestLibPlugIn.cpp)

target_link_libraries(test_compute_lib debug ${CUTI_UNIT_TEST_LIBRARIES_DEBUG} compute_lib)
target_link_libraries(test_compute_lib optimized ${CUTI_UNIT_TEST_LIBRARIES_RELEASE} compute_lib)
