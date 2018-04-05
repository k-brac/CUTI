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

cmake_minimum_required(VERSION 2.8)

#Looks for the install directory of the currently used visual studio

string(COMPARE EQUAL ${CMAKE_GENERATOR} "Ninja" CUTI_USES_NINJA_GENERATOR)
if (${CUTI_USES_NINJA_GENERATOR})
    #When using the Ninja generator we default to the latest version of visual studio (currently 15)
    set(VS_VER 15)
else()
    string(SUBSTRING ${CMAKE_GENERATOR} 14 2 VS_VER)
endif()
set(CUTI_PROGRAM_FILES_X86 "PROGRAMFILES(X86)")
string(REPLACE "\\" "/" CUTI_VS_PROGRAM_FILES_ENV $ENV{${CUTI_PROGRAM_FILES_X86}})

if(VS_VER LESS 15)
    #Visual Studio 14 (2015) or less
    set(CUTI_VS_PATH_PREFIX "${CUTI_VS_PROGRAM_FILES_ENV}/Microsoft Visual Studio ")
    set(CUTI_VS_PATH_SUFIX "VC/UnitTest")

    set(MSVC_UNIT_TEST_DIR ${CUTI_VS_PATH_PREFIX}${VS_VER}.0/${CUTI_VS_PATH_SUFIX})
else()
    #Visual Studio 15 (2017) or more
    if(VS_VER EQUAL 15)
        set(VS_YEAR 2017)
    else()
        message(FATAL_ERROR "Visual Studio version unknown. Please edit FindVisualStudio.cmake.")
    endif()
    set(CUTI_VS_PATH_PREFIX "${CUTI_VS_PROGRAM_FILES_ENV}/Microsoft Visual Studio/${VS_YEAR}")
    set(CUTI_VS_PATH_SUFIX "VC/Auxiliary/VS/UnitTest")

    if(EXISTS ${CUTI_VS_PATH_PREFIX}/Professional)
        set(VS_TYPE "Professional")
    elseif(EXISTS ${CUTI_VS_PATH_PREFIX}/Enterprise)
        set(VS_TYPE "Enterprise")
    elseif(EXISTS ${CUTI_VS_PATH_PREFIX}/Community)
        set(VS_TYPE "Community")
    else()
        message(FATAL_ERROR "Couldn't find Visual Studio installation. Tried in ${CUTI_VS_PATH_PREFIX}")
    endif()

    set(MSVC_UNIT_TEST_DIR ${CUTI_VS_PATH_PREFIX}/${VS_TYPE}/${CUTI_VS_PATH_SUFIX})
endif()
link_directories(${MSVC_UNIT_TEST_DIR}/lib/ ${MSVC_UNIT_TEST_DIR}/lib/)
