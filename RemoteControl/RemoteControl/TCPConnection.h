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