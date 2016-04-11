#pragma once
namespace remote {

	class Server {
	
		public:
			virtual ~Server() = default;

			virtual void start() = 0;

			virtual void terminate() = 0;



	};

}