using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RemoteControlPotrableClassLib
{
    class RemoteControl : IRemoteControl
    {
        public void CloseConnection()
        {
            throw new NotImplementedException();
        }

        public void Connect(string address, ushort port)
        {
            throw new NotImplementedException();
        }

        public void RemoteShutdown()
        {
            throw new NotImplementedException();
        }

        public void RemoteVolumeDown()
        {
            throw new NotImplementedException();
        }

        public void RemoteVolumeUp()
        {
            throw new NotImplementedException();
        }
    }
}
