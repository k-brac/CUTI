cmake_minimum_required(VERSION 2.8)

set(MSVC_UNIT_TEST_DIR "C:/Program Files (x86)/Microsoft Visual Studio 12.0/VC/UnitTest/")#TODO make it discoverable

include_directories(${MSVC_UNIT_TEST_DIR}/include)
link_directories(${MSVC_UNIT_TEST_DIR}lib/)
set(MSVC_UNIT_TEST_LIB Microsoft.VisualStudio.TestTools.CppUnitTestFramework.lib)
