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

#CMake file to compile a cli test runner for CPPUNIT plugins
cmake_minimum_required (VERSION 3.2)

set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake/")

find_package(CUTI REQUIRED)

#In the case we don't want to use IDE integration, we can use a command line test runner for cppunit
if(NOT ${USE_CUTI_BACK_END})
	if(WIN32)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	elseif(APPLE)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wshadow -Wall -Wextra")
	endif(WIN32)

	set(TOP_DIR .)
	set(SRC_DIR ${TOP_DIR}/src)

	project (Cuti)
	find_package(CppUnit REQUIRED)
	include_directories(${CPPUNIT_INCLUDE_DIRS})
	add_executable(Cuti ${SRC_DIR}/CutiMain.cpp)

	cuti_init_cppunit_libraries(Cuti)

	target_link_libraries(Cuti debug ${CUTI_LIBRARIES_DEBUG})
	target_link_libraries(Cuti optimized ${CUTI_LIBRARIES_RELEASE})

	set(CUTI_COPY_LIB $<$<CONFIG:Debug>:${CPPUNIT_DYN_LIB_DEBUG}> $<$<NOT:$<CONFIG:Debug>>:${CPPUNIT_DYN_LIB_RELEASE}>)

	add_custom_command(TARGET Cuti POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy
						${CUTI_COPY_LIB} $<TARGET_FILE_DIR:Cuti>)
endif()
