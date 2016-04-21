using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Xamarin.Forms;

namespace RemoteControlApp
{
    public partial class AddConnectionDialog : ContentPage
    {
        public AddConnectionDialog()
        {
            InitializeComponent();
        }

        async public void OnSaveConnectionClicked(Object sender, EventArgs e)
        {
            this.Navigation.PopModalAsync();
        }
    }
}
