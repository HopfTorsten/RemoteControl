#include "ConcreteServer.h"
#include "boost\log\trivial.hpp"
namespace remote {

	ConcreteServer::ConcreteServer(unsigned short pPort)
		:port{ pPort }, endpoint{ tcp::v4(),port }, ioServicePtr{ new ioService{} },
		acceptor{ *ioServicePtr }
	{
		BOOST_LOG_TRIVIAL(info) << "Starting Remote Control Server on port " << port;

		acceptor.open(endpoint.protocol());
		acceptor.bind(endpoint);
		acceptor.listen();



	}


	ConcreteServer::~ConcreteServer()
	{
		;
	}

	void ConcreteServer::start()
	{
	}

	void ConcreteServer::terminate()
	{
	}

	void ConcreteServer::handleAccept(const error_code & ec, std::shared_ptr<Connection> connection)
	{

	}

	

}
