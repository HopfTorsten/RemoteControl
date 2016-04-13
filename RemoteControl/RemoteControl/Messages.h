#pragma once

#define SHUTDOWN 1
#define VOLUME_UP 2
#define VOLUME_DOWN 3
#define TOGGLE_MUTE 4


namespace remote {

	struct header {
		unsigned char appType;
		unsigned char appVersion;
		unsigned long long timestamp;
	};

	struct body {
		unsigned int command;
	};

	struct message {
		header mHead;
		body   mBody;
	};
}