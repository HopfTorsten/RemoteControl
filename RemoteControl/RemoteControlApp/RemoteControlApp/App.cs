﻿using RemoteControlApp.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Xamarin.Forms;

namespace RemoteControlApp
{
    public class App : Application
    {
        public App()
        {
            // The root page of your application
            MainPage = new ConnectionPage(CreateDummyData());
            
        }

        private Connections CreateDummyData()
        {
            Connections connections = new Connections();
            for(int i=1; i<5; i++)
            {
                Connection connection = new Connection { Name= "Verbindung " + i, IP = i*50 + "." + i*30 + "." + i*20 + "." + i};
                connections.Values.Add(connection);
            }
            return connections;
        }

        protected override void OnStart()
        {
            // Handle when your app starts
        }

        protected override void OnSleep()
        {
            // Handle when your app sleeps
        }

        protected override void OnResume()
        {
            // Handle when your app resumes
        }
    }
}
