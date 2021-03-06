﻿/*
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

using RemoteControlApp.Model;
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
        private Connections connections;

        public ConnectionPage(Connections connections)
        {
            InitializeComponent();
            this.connections = connections;
            ConnectionList.ItemsSource = connections.Values;
        }

        async public void OnAddConnectionClicked(Object sender, EventArgs e)
        {
            //DisplayAlert("Verbindung hinzufügen", "Bald kannst Du hier Verbindungen hinzufügen", "Verbinden");
            await Navigation.PushModalAsync(new AddConnectionDialog());
        }
    }
}
