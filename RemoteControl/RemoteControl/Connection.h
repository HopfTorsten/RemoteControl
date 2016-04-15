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
#include <functional>
#include <boost\system\error_code.hpp>
#include <boost\asio.hpp>
namespace remote {
	using error_code = boost::system::error_code;
	using writeHandler = std::function<void(const error_code&,size_t)>;
	using readHandler = std::function<void(const error_code&, size_t)>;

	struct message;
	class Connection
	{
	public:

		virtual ~Connection() = default;

		virtual void receive(void* buffer, size_t length, readHandler handler)=0;

		virtual void send(void* data, size_t length, writeHandler handler) = 0;

		virtual void receive() = 0;

		virtual void send(message msg) = 0;

		virtual void close() = 0;

		virtual boost::asio::ip::tcp::socket& getSocket()=0;
	};

}
