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
#include "TCPConnection.h"
#include "boost\log\trivial.hpp"
#include "boost\asio.hpp"
#include "Server.h"
namespace remote {

	TCPConnection::TCPConnection(boost::asio::io_service& service, Server& server) 
		:socket{ service },serverInstance{&server}
	{

	}

	TCPConnection::~TCPConnection()
	{
		close();
	}

	void TCPConnection::receive(void * buffer, size_t length, readHandler handler)
	{
		auto boostBuffer = boost::asio::buffer(buffer, length);
		boost::asio::async_read(this->socket,boostBuffer, handler);
	}
	
	void TCPConnection::send(void * data, size_t length, writeHandler handler)
	{
		auto buffer = boost::asio::buffer(data, length);
		boost::asio::async_write(this->socket,buffer,handler);
	}

	void TCPConnection::close()
	{
		error_code ec;
		this->socket.shutdown(tcp::socket::shutdown_both,ec);
		BOOST_LOG_TRIVIAL(info) << "Connection closed with error code " << ec.value() << ": " << ec.message();
	}

	boost::asio::ip::tcp::socket & TCPConnection::getSocket()
	{
		return socket;
	}

	std::shared_ptr<TCPConnection> TCPConnection::create(boost::asio::io_service & service,Server& server)
	{
		return std::make_shared<TCPConnection>(service,server);
	}
	void TCPConnection::receive()
	{
		auto receiveHandler = [this](const error_code& ec,size_t) 
		{
			if (!ec)
			{
				serverInstance->interprete(lastMessage);
				receive();
			}
			else 
			{
				BOOST_LOG_TRIVIAL(error) << "An error occured while receiving a message. Code:"
					<< ec.value() << ": " << ec.message();
				close();
			}
		}				;
		receive(&lastMessage, sizeof(lastMessage), receiveHandler);
	}

	void TCPConnection::send(message msg)
	{
		auto buffer = boost::asio::buffer(&msg, sizeof(msg));
		auto writeHandler = [](const error_code ec, size_t) 
		{
			if (ec) BOOST_LOG_TRIVIAL(error) << "An error occured while sending";
		};

		boost::asio::async_write(this->socket, buffer, writeHandler);
	}
}
