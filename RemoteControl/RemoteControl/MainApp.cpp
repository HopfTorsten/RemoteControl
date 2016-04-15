/**
RemoteControl is a client server solution for remote control a PC. Copyright (C) 2016 Torsten Hopf

This program is free software: you can redistribute it and/or modify it under the terms of
the GNU General Public License as published by the Free Software Foundation, either version
3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. 
If not, see http://www.gnu.org/licenses/.
 * */
#include "MainApp.h"
#include <iostream>
#include "ConcreteServer.h"
#include "AudioMasterMind.h"
#include <boost/log/trivial.hpp>

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
	server.start();

	AudioMasterMind mind{};
	mind.start();
	server.setAudioMasterMind(&mind);
	
	BOOST_LOG_TRIVIAL(info) << "Volume is: " << mind.getMasterVolumeScalar();

	char command;
	std::cin >> command;
	server.terminate();

}
