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

set(CUTI_VS_PATH_PREFIX "C:/Program Files (x86)/Microsoft Visual Studio ")
set(CUTI_VS_PATH_SUFIX "VC/UnitTest")

string(SUBSTRING ${CMAKE_GENERATOR} 14 2 VS_VER)
set(MSVC_UNIT_TEST_DIR ${CUTI_VS_PATH_PREFIX}${VS_VER}.0/${CUTI_VS_PATH_SUFIX})

include_directories(${MSVC_UNIT_TEST_DIR}/include)
link_directories(${MSVC_UNIT_TEST_DIR}/lib/)
