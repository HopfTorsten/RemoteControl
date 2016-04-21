using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Xamarin.Forms;

namespace RemoteControlApp
{
    public partial class ConnectionPage : ContentPage
    {
        public ConnectionPage()
        {
            InitializeComponent();

            ConnectionList.ItemsSource = new List<String> { "Porno Pub", "Zur goldenen Sackratte", "ZUm Klöten-Wirt" };
        }
    }
}
