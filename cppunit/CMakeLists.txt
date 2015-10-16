cmake_minimum_required (VERSION 3.2)

if(WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif(WIN32)

set(TOP_DIR ./)
set(CPPUNIT_TOP_DIR ${TOP_DIR}/)

project (cppunit)
	include_directories(${CPPUNIT_TOP_DIR}include)
	set(CPPUNIT_INCLUDES ${CPPUNIT_TOP_DIR}include/*)
	set(CPPUNIT_SRCS
    ${CPPUNIT_TOP_DIR}/src/cppunit/AdditionalMessage.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/Asserter.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/BeOsDynamicLibraryManager.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/BriefTestProgressListener.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/CompilerOutputter.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/DefaultProtector.h
    ${CPPUNIT_TOP_DIR}/src/cppunit/DefaultProtector.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/DynamicLibraryManager.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/DynamicLibraryManagerException.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/Exception.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/Message.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/RepeatedTest.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/PlugInManager.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/PlugInParameters.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/Protector.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/ProtectorChain.h
    ${CPPUNIT_TOP_DIR}/src/cppunit/ProtectorContext.h
    ${CPPUNIT_TOP_DIR}/src/cppunit/ProtectorChain.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/SourceLine.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/StringTools.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/SynchronizedObject.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/Test.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/TestAssert.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/TestCase.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/TestCaseDecorator.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/TestComposite.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/TestDecorator.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/TestFactoryRegistry.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/TestFailure.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/TestLeaf.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/TestNamer.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/TestPath.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/TestPlugInDefaultImpl.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/TestResult.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/TestResultCollector.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/TestRunner.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/TestSetUp.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/TestSuccessListener.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/TestSuite.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/TestSuiteBuilderContext.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/TextOutputter.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/TextTestRunner.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/TextTestProgressListener.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/TextTestResult.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/TypeInfoHelper.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/UnixDynamicLibraryManager.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/ShlDynamicLibraryManager.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/XmlDocument.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/XmlElement.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/XmlOutputter.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/XmlOutputterHook.cpp
    ${CPPUNIT_TOP_DIR}/src/cppunit/Win32DynamicLibraryManager.cpp
)
#add_library(cppunitO OBJECT ${CPPUNIT_SRCS})
add_library(cppunit_static STATIC ${CPPUNIT_SRCS})
add_library(cppunit SHARED ${CPPUNIT_SRCS})
set_target_properties(cppunit_static PROPERTIES OUTPUT_NAME cppunit)
