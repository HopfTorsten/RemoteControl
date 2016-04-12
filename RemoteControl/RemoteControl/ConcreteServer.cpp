#include "ConcreteServer.h"
#include "boost\log\trivial.hpp"
#include "TCPConnection.h"
#include <memory>
#include <functional>
namespace remote {

	ConcreteServer::ConcreteServer(unsigned short pPort)
		:port{ pPort }, endpoint{ tcp::v4(),port }, ioServicePtr{ new ioService{} },
		acceptor{ *ioServicePtr }
	{
		BOOST_LOG_TRIVIAL(info) << "Starting Remote Control Server on port " << port;

		acceptor.open(endpoint.protocol());
		acceptor.bind(endpoint);
		acceptor.listen();

		auto connection = TCPConnection::create(*ioServicePtr,*this);

		auto acceptHandler = [this, connection](const error_code& ec) {this->handleAccept(ec, connection); };

		acceptor.async_accept(connection->getSocket(), acceptHandler);

		auto threadFunction = [this]() 
		{
			BOOST_LOG_TRIVIAL(info) << "Worker Thread started"; 
			ioServicePtr->run();
		};

		threadPtr = std::make_unique<std::thread>(threadFunction);
		

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
		if (!ec) {
			BOOST_LOG_TRIVIAL(info) << "Successfully accepted connection attempt!";
		}else{
			BOOST_LOG_TRIVIAL(error) << "An error occured while accepting an connection attempt: Code" 
				<< ec.value()<<":" << ec.message();
			connection->close();

		}
	}

	void ConcreteServer::interprete(message & msg)
	{
	}

	

}
