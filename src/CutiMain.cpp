#include "cppunit/extensions/TestFactoryRegistry.h"
#include "cppunit/CompilerOutputter.h"
#include "cppunit/TestResult.h"
#include "cppunit/TestResultCollector.h"
#include "cppunit/TestRunner.h"
#include "cppunit/BriefTestProgressListener.h"

#include "cppunit/plugin/PlugInManager.h"

bool runPlugin(const std::string &plugPath, const std::vector<std::string> &testPaths) {
	CppUnit::PlugInManager pluginManager;
	try {
		pluginManager.load(plugPath);
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return false;
	}

	// Create the event manager and test controller
	CppUnit::TestResult controller;

	// Add a listener that colllects test result
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
		for (size_t i = 1; i < argc; ++i) {
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