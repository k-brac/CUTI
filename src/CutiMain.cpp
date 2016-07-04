/*The MIT License (MIT)

Copyright (c) 2015 k-brac

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "cppunit/extensions/TestFactoryRegistry.h"
#ifdef WIN32
#pragma warning( push )
#pragma warning( disable : 4251 )
#endif
#include "cppunit/CompilerOutputter.h"
#ifdef WIN32
#pragma warning( pop )
#endif
#include "cppunit/TestResult.h"
#include "cppunit/TestResultCollector.h"
#include "cppunit/TestRunner.h"
#include "cppunit/BriefTestProgressListener.h"

#include "cppunit/plugin/PlugInManager.h"

bool runPlugin(const std::string &plugPath, const std::vector<std::string> &testPaths) {
	CppUnit::PlugInManager pluginManager;
	pluginManager.load(plugPath);

	// Create the event manager and test controller
	CppUnit::TestResult controller;

	// Add a listener that collects test result
	CppUnit::TestResultCollector result;
	controller.addListener(&result);

	// Add a listener
	CppUnit::BriefTestProgressListener progress;
	controller.addListener(&progress);

	pluginManager.addListener(&controller);

	// Add the top suite to the test runner
	CppUnit::TestRunner runner;
	runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
	try
	{
		if (testPaths.empty()) {
			std::cout << "Running ";
			runner.run(controller);
		}
		else {
			for (const auto & p : testPaths) {
				std::cout << "Running " << p;
				runner.run(controller, p);
			}
		}
		std::cerr << std::endl;

		// Print test in a compiler compatible format.
		CppUnit::CompilerOutputter outputter(&result, std::cerr);
		outputter.write();
	}
	catch (std::invalid_argument &e)  // Test path not resolved
	{
		std::cerr << std::endl
			<< "ERROR: " << e.what()
			<< std::endl;
		return false;
	}
	return result.wasSuccessful();
}

int main(int argc, char* argv[])
{
	std::cout << "usage : " << argv[0] << " {-t | -test test_path} test_plugin_path" << std::endl << std::endl;
	if (argc < 2)
		return 1;
	std::vector<std::string> args;
	args.reserve(argc - 1);
	std::vector<std::string> testPaths;
	bool result = false;
	try {
		for (int i = 1; i < argc; ++i) {
			args.push_back(argv[i]);
		}
		size_t maxSize = args.size() > 2 ? args.size() - 2 : 0;
		for (size_t j = 0; j < maxSize; ++j) {
			if ((args[j] == "-t" || args[j] == "-test"))
				testPaths.push_back(args[j + 1]);
		}
		result = runPlugin(args.at(args.size() - 1), testPaths) ? 0 : 1;
	}
	catch (std::exception &e) {
		std::cerr << std::endl
			<< "ERROR: " << e.what()
			<< std::endl;
	}
	return result ? 0 : 1;
}
