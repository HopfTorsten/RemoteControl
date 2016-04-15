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
