#include "MainApp.h"
#include <iostream>
#include "ConcreteServer.h"
#define STDPORT 5070 

namespace remote {

	MainApp::MainApp()
	{

	}


	MainApp::~MainApp()
	{
	}

	boost::program_options::options_description MainApp::buildOptions()
	{	
		namespace po = boost::program_options;
		auto options = boost::program_options::options_description{"Help"};
		options.add_options()("help","See all available commands")
			("port",po::value<unsigned short>(),"The port that should be used as listening port")
			;

		return options;
	}
}

int main(int argc,  char** argv) {
	using namespace remote;
	namespace po = boost::program_options;
	MainApp app{};
	const auto options = app.buildOptions();
	auto variableMap = po::variables_map{};
	auto parsedLine = po::parse_command_line(argc, argv, options);
	po::store(parsedLine, variableMap);
	po::notify(variableMap);

	if (variableMap.count("help")) {
		std::cout << options << std::endl;
		return 1;
	}

	const unsigned short port = (variableMap.count("port")) ? variableMap["port"].as<unsigned short>() : STDPORT;

	ConcreteServer server{ port };

	char command;
	std::cin >> command;


}