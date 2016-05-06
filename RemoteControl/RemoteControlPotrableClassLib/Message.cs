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
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RemoteControlPotrableClassLib
{
    class Message
    {
        
        public Header header { get; set; }
        public Body body { get; set; }


        public byte[] GetBytes()
        {
            MemoryStream mStream = new MemoryStream();
            //write the header
            mStream.WriteByte(header.appType);
            mStream.WriteByte(header.appVersion);
            mStream.Write(BitConverter.GetBytes(header.timestamp),0,sizeof(UInt64));
            // write the body
            mStream.Write(BitConverter.GetBytes(body.command), 0, sizeof(UInt32));
            // return byte array
            return mStream.ToArray();
        }

        public class Body
        {
            public UInt32 command { get; set; }
        }

        public class Header
        {
            public Byte appType {  get; set; }
            public Byte appVersion { get; set; }
            public UInt64 timestamp { get; set; }
        }
    }
}
