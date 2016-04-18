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
using Sockets.Plugin;

namespace RemoteControlPotrableClassLib
{
    class RemoteControl : IRemoteControl
    {
        private TcpSocketClient tcpClient;
        private bool connected = false;
        private RemoteControlMessageFactory messageFactory = new RemoteControlMessageFactory();

        private const UInt32 SHUTDOWN_COMMAND = 1;
        private const UInt32 VOLUME_UP_COMMAND = 2;
        private const UInt32 VOLUME_DOWN_COMMAND = 3;
        private const UInt32 TOGGLE_MUTE_COMMAND = 4;

        public void CloseConnection()
        {

            tcpClient.DisconnectAsync().Wait();
            connected = false;
        }

        public void Connect(string address, ushort port)
        {
            tcpClient = new TcpSocketClient();
            tcpClient.ConnectAsync(address, port).Wait(); ;
            connected = true;
        }

        public void RemoteShutdown()
        {
            if (!connected)
                throw new InvalidOperationException("Can not shutdown remote host before connecting!");
            var shutdownMessage = messageFactory.CreateShutdownMessage();
            var shutdownBytes = shutdownMessage.GetBytes();
            tcpClient.WriteStream.Write(shutdownBytes, 0, shutdownBytes.Length);
        }

        public void RemoteVolumeDown()
        {
            if (!connected)
                throw new InvalidOperationException("Can not decrease volume on remote host before connecting!");
            var volumeDownMessage = messageFactory.CreateVolumeDownMessage();
            var volumeDownBytes = volumeDownMessage.GetBytes();
            tcpClient.WriteStream.Write(volumeDownBytes, 0, volumeDownBytes.Length);
        }

        public void RemoteVolumeUp()
        {
            if (!connected)
               throw new InvalidOperationException("Can not increace volume on remote host before connecting!");
            var volumeUpMessage = messageFactory.CreateVolumeUpMessage();
            var volumeUpBytes = volumeUpMessage.GetBytes();
            tcpClient.WriteStream.Write(volumeUpBytes, 0, volumeUpBytes.Length);

        }
    }
}
