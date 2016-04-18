/*
RemoteControl is a client server solution for remote control a PC. Copyright (C) 2016 Torsten Hopf

This program is free software: you can redistribute it and/or modify it under the terms of
the GNU General Public License as published by the Free Software Foundation, either version
3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. 
If not, see http://www.gnu.org/licenses/.
*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RemoteControlPotrableClassLib
{
    class RemoteControlMessageFactory
    {
        private const UInt32 SHUTDOWN_COMMAND = 1;
        private const UInt32 VOLUME_UP_COMMAND = 2;
        private const UInt32 VOLUME_DOWN_COMMAND = 3;
        private const UInt32 TOGGLE_MUTE_COMMAND = 4;

        public Message CreateVolumeUpMessage()
        {
            Message volUpMsg = CreateMessageWithHeader();

            volUpMsg.body.command = VOLUME_UP_COMMAND;

            return volUpMsg;
        }

        public Message CreateVolumeDownMessage()
        {
            Message volDownMessage = CreateMessageWithHeader();

            volDownMessage.body.command = VOLUME_DOWN_COMMAND;

            return volDownMessage;
        }

        public Message CreateToggleMuteMessage()
        {
            Message toggleMsg = CreateMessageWithHeader();

            toggleMsg.body.command = VOLUME_DOWN_COMMAND;

            return toggleMsg;
        }

        public Message CreateShutdownMessage()
        {
            Message shutdownMsg = CreateMessageWithHeader();

            shutdownMsg.body.command = SHUTDOWN_COMMAND;

            return shutdownMsg;
        }

        private Message CreateMessageWithHeader()
        {
            Message msg = new Message();
            UInt64 timestamp = (UInt64)DateTime.Now.ToBinary();

            msg.header.appVersion = 1;
            msg.header.timestamp = timestamp;
            msg.header.appType = 1;

            return msg;
        }
    }
}
