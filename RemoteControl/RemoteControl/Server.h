#pragma once
namespace remote {

	class Server {
	
		public:
			virtual ~Server() = 0;

			virtual void start() = 0;

			virtual void terminate() = 0;



	};

}