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
#pragma once
#include "Server.h"
#include "boost\asio.hpp"
#include <thread>
#include "Connection.h"
#include <vector>
#include "AudioMasterMind.h"
namespace remote{

	using ioService = boost::asio::io_service;
	using  tcp = boost::asio::ip::tcp;
	class ConcreteServer :
		public Server
	{
	public:
		ConcreteServer(unsigned short port);
		virtual ~ConcreteServer();

		
		virtual void start() override;
		virtual void terminate() override;
		virtual void interprete(message & msg) override;

		void shutdownHostPC();
		void sleepHostPC();
		void setAudioMasterMind(AudioMasterMind* mind);

	private:
		std::unique_ptr<ioService> ioServicePtr;
		std::unique_ptr<std::thread> threadPtr;
		tcp::acceptor acceptor;
		tcp::endpoint endpoint;
		unsigned short port;
		std::vector<std::shared_ptr<Connection>> connections;
		AudioMasterMind* audioMaster = nullptr;

		// methods
		void handleAccept(const error_code& ec, std::shared_ptr<Connection> connection);
		
		

	};

}
