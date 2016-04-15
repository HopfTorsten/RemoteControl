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
#include "Connection.h"
#include "Messages.h"
namespace remote {
	using tcp = boost::asio::ip::tcp;
	class Server;
	class TCPConnection :
		public Connection
	{
	public:
		TCPConnection(boost::asio::io_service& service,Server& server);
		virtual ~TCPConnection();

		// Geerbt über Connection
		virtual void receive(void * buffer, size_t length, readHandler handler) override;
		virtual void send(void * data, size_t length, writeHandler handler) override;
		virtual void receive() override;
		virtual void send(message msg) override;
		virtual void close() override;
		virtual tcp::socket& getSocket() override;

		static std::shared_ptr<TCPConnection> create(boost::asio::io_service& service,Server& server);

	private:
		tcp::socket socket;
		message lastMessage;
		Server* serverInstance;
	};

}
