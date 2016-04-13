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