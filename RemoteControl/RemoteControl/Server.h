#pragma once
namespace remote {

	struct message;

	class Server {
	
		public:
			virtual ~Server() = default;

			virtual void start() = 0;

			virtual void terminate() = 0;

			virtual void interprete(message& msg)=0;



	};

}