//-------------------------- networks-n-filters.cpp ----------------------------

/***************************************************************************
                            -  Description
                             -------------------
    Begin                : 26 January, 2012
    Copyright            : (C) 2012 by Simo
    E-Mail               : simo@furrydolphin.net
    Version              : 1.2.0
 **************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *                                                                         *
 *       ----> If software can be free, why can't dolphins? <----          *
 *                                                                         *
 ***************************************************************************/

#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "mainwindow.h"

/*
     Name: main

     Type: Function (int)

     Parameters:
                 argc (int) - Number of command line options
		 argv (Dbl Pointer: char) - Array of command line options
		 Note: FOX parses argv for FOX specific options, passes these
		       along to the FOX application object, leaves user
		       defined options for processing.

     Returns:
              0 --  Indicates success to shell
	      1 --     "     failure  "   "

     Note:
           1) Create FOX application object, initialize with app name &
              vendor name (used for FOX config files in user home dir),
	      initialize with FOX-specific command line options.

           2) Create the app main window, pass in application object pointer

	   3) Connect interrupt signal to the main window exit routine (allows
              keyboard kill without causing uncontrolled exit)

           4) Request X-Server resources and connect, enter main event loop.
*/

int main(int argc, char *argv[])
{
    for(int i= 0; i < argc; i++)
    {
	char *Current= argv[i];

	if (! (strcmp(Current, "-v") && strcmp(Current, "--version")))
      {
	    printf("NetworkDesigner Version: %s\n", VERSION);
	    return 0;
      }
    }

    FXApp MyApp("NetworkDesigner", "Simo");
    MyApp.init(argc, argv);
    MainWindow *Mw= new MainWindow(&MyApp);
    MyApp.addSignal(SIGINT, Mw, MainWindow::ID_FILE_EXIT);
    MyApp.create();
    return MyApp.run();
}

//-------------------------- networks-n-filters.cpp ----------------------------
