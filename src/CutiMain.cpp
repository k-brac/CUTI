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

#include <string>
#include <vector>
#include <iostream>

#ifdef WIN32
#pragma warning( push )
#pragma warning( disable : 4251 )
#endif

#if __MACH__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wweak-vtables"
#pragma clang diagnostic ignored "-Wextra-semi"
#pragma clang diagnostic ignored "-Wdocumentation"
#pragma clang diagnostic ignored "-Wreserved-id-macro"
#pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#define CPPUNIT_STD_NEED_ALLOCATOR 0
#endif

#include "cppunit/extensions/TestFactoryRegistry.h"
#include "cppunit/CompilerOutputter.h"
#include "cppunit/XmlOutputter.h"
#include "cppunit/TestResult.h"
#include "cppunit/TestResultCollector.h"
#include "cppunit/TestRunner.h"
#include "cppunit/BriefTestProgressListener.h"
#include "cppunit/plugin/PlugInManager.h"
#include <chrono>


class TimedBriefTestProgressListener : public CppUnit::BriefTestProgressListener {
private:
    std::chrono::time_point<std::chrono::steady_clock> mTimer;
public:

    void startTest(CppUnit::Test *test)
    {
        CppUnit::BriefTestProgressListener::startTest(test);
        mTimer = std::chrono::high_resolution_clock::now();
    }

    void endTest(CppUnit::Test *test)
    {
        const std::chrono::duration<float, std::milli> elapsed = std::chrono::steady_clock::now() - mTimer;
        CppUnit::stdCOut() << " (" << std::to_string(elapsed.count()) << " ms elapsed)";
#if defined(WIN32)
        CppUnit::stdCOut().flush();
#endif
        CppUnit::BriefTestProgressListener::endTest(test);
    }
};

#if __MACH__
#pragma clang diagnostic pop
#endif

#ifdef WIN32
#pragma warning( pop )
#endif


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
    TimedBriefTestProgressListener progress;
	controller.addListener(&progress);

	pluginManager.addListener(&controller);

	// Add the top suite to the test runner
	CppUnit::TestRunner runner;
	runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
	try
	{
		if (arguments.testPaths.empty()) {
			std::cout << "Running " << std::endl;
			runner.run(controller);
		}
		else {
			for (const auto & p : arguments.testPaths) {
				std::cout << "Running " << p << std::endl;
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
	if (argc < 2) {
		std::cout << "usage : " << argv[0] << " {-x | -xml=file} {-t | --test=Namespace::ClassName::TestName} test_plugin_path" << std::endl << std::endl;
		return 1;
	}

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
