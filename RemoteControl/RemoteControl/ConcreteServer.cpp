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
#include "ConcreteServer.h"
#include "boost\log\trivial.hpp"
#include "TCPConnection.h"
#include <memory>
#include <functional>
#include "Endpointvolume.h"
#include "Mmdeviceapi.h"
namespace remote {

	ConcreteServer::ConcreteServer(unsigned short pPort)
		:port{ pPort }, endpoint{ tcp::v4(),port }, ioServicePtr{ new ioService{} },
		acceptor{ *ioServicePtr }
	{
		BOOST_LOG_TRIVIAL(info) << "Preparing Remote Control Server on port " << port;

		acceptor.open(endpoint.protocol());
		acceptor.bind(endpoint);
		acceptor.listen();

		auto connection = TCPConnection::create(*ioServicePtr,*this);

		auto acceptHandler = [this, connection](const error_code& ec) {this->handleAccept(ec, connection); };

		acceptor.async_accept(connection->getSocket(), acceptHandler);
	}


	ConcreteServer::~ConcreteServer()
	{
		;
	}

	void ConcreteServer::start()
	{
		BOOST_LOG_TRIVIAL(info) << "Starting Remote Control Server on port " << port;
		auto threadFunction = [this]()
		{
			BOOST_LOG_TRIVIAL(info) << "Worker Thread started";
			ioServicePtr->run();
		};

		threadPtr = std::make_unique<std::thread>(threadFunction);
	}

	void ConcreteServer::terminate()
	{
		for (auto& con : connections) 
		{
			con->close();
		}
		error_code ec;
		acceptor.close(ec);
		threadPtr->join();
	}

	void ConcreteServer::handleAccept(const error_code & ec, std::shared_ptr<Connection> connection)
	{
		if (!ec) {
			BOOST_LOG_TRIVIAL(info) << "Successfully accepted connection attempt!";
			connections.push_back(connection);
		}else{
			BOOST_LOG_TRIVIAL(error) << "An error occured while accepting an connection attempt: Code" 
				<< ec.value()<<":" << ec.message();
			connection->close();

		}
	}


	void ConcreteServer::shutdownHostPC()
	{
		BOOST_LOG_TRIVIAL(info) << "Shutdown this Computer";
		terminate();
		system("shutdown /s /t 5");
	}

	void ConcreteServer::sleepHostPC()
	{
		BOOST_LOG_TRIVIAL(info) << "Set pc into sleeping mode";
		terminate();
		system("Rundll32.exe Powrprof.dll,SetSuspendState Sleep");
	}

	void ConcreteServer::interprete(message & msg)
	{
		auto command = msg.mBody.command;
		switch (command)
		{
		case VOLUME_DOWN:
			audioMaster->volumeDown();
			break;
		case VOLUME_UP:
			audioMaster->volumeUp();
			break;
		case TOGGLE_MUTE:
			audioMaster->toggleMute();
			break;
		case SHUTDOWN:
			shutdownHostPC();
			break;
		}
		
	}

	void ConcreteServer::setAudioMasterMind(AudioMasterMind* mind) 
	{
		audioMaster = mind;
	}

}
