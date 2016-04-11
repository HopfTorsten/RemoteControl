#pragma once
#include <functional>
#include <boost\system\error_code.hpp>
#include <boost\asio.hpp>
namespace remote {
	using error_code = boost::system::error_code;
	using writeHandler = std::function<void(const error_code&,size_t)>;
	using readHandler = std::function<void(const error_code&, size_t)>;

	class Connection
	{
	public:
		Connection() = delete;

		virtual ~Connection() = 0;

		virtual void receive(void* buffer, size_t length, readHandler handler)=0;

		virtual void send(void* data, size_t length, writeHandler handler) = 0;

		virtual void close() = 0;

		virtual boost::asio::ip::tcp::socket& getSocket()=0;
	};

}