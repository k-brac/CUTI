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
#include "cppunit/XmlOutputter.h"
#ifdef WIN32
#pragma warning( pop )
#endif
#include "cppunit/TestResult.h"
#include "cppunit/TestResultCollector.h"
#include "cppunit/TestRunner.h"
#include "cppunit/BriefTestProgressListener.h"

#include "cppunit/plugin/PlugInManager.h"


struct CommandLineParser {
    std::string xmlOutputFile;
    std::string plugName;
    std::vector<std::string> testPaths;

    void parseArgs(int argc, char* argv[]) {
        for (int i = 1; i < argc; i++) {
            std::string arg = argv[i];
            if (arg.size() >= 2 && arg.front() == '-') {
                auto it = arg.find("=");
                if (it != std::string::npos) {
                    auto key = arg.substr(0, it);
                    auto val = arg.substr(it + 1, arg.size());
                    if (val.empty()) {
                        continue;
                    }
                    if (key == "-x" || key == "--xml") {
                        xmlOutputFile = val;
                    }
                    else if (key == "-t" || key == "--test") {
                        testPaths.emplace_back(val);
                    }
                    else {
                        std::cerr << "Unknow arguments " << key << " with value : " << val << std::endl;
                    }
                }
            }
            else {
                plugName = arg;
            }
        }

    }
};

bool runPlugin(const CommandLineParser &arguments) {
	CppUnit::PlugInManager pluginManager;
	pluginManager.load(arguments.plugName);

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
		if (arguments.testPaths.empty()) {
			std::cout << "Running ";
			runner.run(controller);
		}
		else {
			for (const auto & p : arguments.testPaths) {
				std::cout << "Running " << p;
				runner.run(controller, p);
			}
		}
		std::cerr << std::endl;

		// Print test in a compiler compatible format.
		CppUnit::CompilerOutputter outputter(&result, std::cerr);
		outputter.write();

        if (!arguments.xmlOutputFile.empty()) {
            std::ofstream file(arguments.xmlOutputFile);
            CppUnit::XmlOutputter xOutputter(&result, file);
            xOutputter.write();
        }
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
	std::cout << "usage : " << argv[0] << "{-x | -xml=file} {-t | --test=test_path} test_plugin_path" << std::endl << std::endl;
	if (argc < 2)
		return 1;

	bool result = false;
	try {
        CommandLineParser command;
        command.parseArgs(argc, argv);
		
		result = runPlugin(command);
	}
	catch (std::exception &e) {
		std::cerr << std::endl
			<< "ERROR: " << e.what()
			<< std::endl;
	}
	return result ? 0 : 1;
}
