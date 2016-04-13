#pragma once
#include <boost/thread.hpp>
#include <boost/program_options.hpp>

#define STDPORT 5070 
#define SERVER_VERSION 1.0

namespace remote{
 

class MainApp
{
public:
	MainApp();
	~MainApp();
	boost::program_options::options_description buildOptions();

};

}