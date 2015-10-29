cmake_minimum_required(VERSION 2.8)

set(CUTI_VS_PATH_PREFIX "C:/Program Files (x86)/Microsoft Visual Studio ")
set(CUTI_VS_PATH_SUFIX "/VC/UnitTest/")

if(EXISTS ${CUTI_VS_PATH_PREFIX}14.0${CUTI_VS_PATH_SUFIX})
	set(CUTI_VS_VERSION 14.0)
elseif(EXISTS ${CUTI_VS_PATH_PREFIX}12.0${CUTI_VS_PATH_SUFIX})
	set(CUTI_VS_VERSION 12.0)
elseif(EXISTS ${CUTI_VS_PATH_PREFIX}11.0${CUTI_VS_PATH_SUFIX})
	set(CUTI_VS_VERSION 11.0)
else()
	message(FATAL_ERROR "CUTI : Visual studio install directory not found or unsupported version")
endif()

set(MSVC_UNIT_TEST_DIR ${CUTI_VS_PATH_PREFIX}${CUTI_VS_VERSION}${CUTI_VS_PATH_SUFIX})

include_directories(${MSVC_UNIT_TEST_DIR}/include)
link_directories(${MSVC_UNIT_TEST_DIR}lib/)
set(MSVC_UNIT_TEST_LIB Microsoft.VisualStudio.TestTools.CppUnitTestFramework.lib)
