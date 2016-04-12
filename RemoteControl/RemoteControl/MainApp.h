#pragma once
#include <boost/thread.hpp>
#include <boost/program_options.hpp>

namespace remote{
 

class MainApp
{
public:
	MainApp();
	~MainApp();
	boost::program_options::options_description buildOptions();

};

}