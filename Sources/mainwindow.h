//-------------------------------- mainwindow.h --------------------------------

/***************************************************************************
                            -  description
                         -----------------------
    Begin                : 9 July, 2012
    Copyright            : (C) 2012 by Simo
    E-Mail               : simo@furrydolphin.net
    Version              : 1.2.0

 **************************************************************************

 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *                                                                         *
 *       ----> If software can be free, why can't dolphins? <----          *
 *                                                                         *
 ***************************************************************************

*/

#ifndef MAIN_H
#define MAIN_H

#include <fox-1.6/fx.h>
#include "defs.h"
#include "messages.h"

//                 Convenience Macros

#define ENABLE         FXWindow::ID_ENABLE
#define DISABLE        FXWindow::ID_DISABLE
#define LAYOUT_CENTER  LAYOUT_CENTER_X|LAYOUT_CENTER_Y
#define LAYOUT_FIXSIZE LAYOUT_FIX_HEIGHT|LAYOUT_FIX_WIDTH

/*
     Type: Macro Function

     Name: USER_ENTRY_ERROR

     Parameters: x (FXint)

     Returns: RetVal (FXString)

     Note: If there is either missing data, or the data was unreadable,
           then display a message box, set the focus on the missing
	   data field, and return to the displayb area so the user can
	   enter/reenter the missing/bad data.
 */

#define USER_ENTRY_ERROR(x) {\
FXMessageBox::error(ThisApp, MBOX_OK, "NetworkDesigner Error", NETENTRY_ERROR);\
NetEntries[x]->setFocus();\
RetVal= "None";\
return RetVal;}


class MainWindow : public FXMainWindow
{
    FXDECLARE(MainWindow)

//                                  Methods

    public:

        MainWindow(FXApp *aApp);
        virtual ~MainWindow(void);
        virtual void create(void);

//                                  Event Handlers: Command

        long MainMenuClick(FXObject*, FXSelector, void*);
        long OptionMenuClick(FXObject*, FXSelector, void*);
        long CmdBtnClick(FXObject*, FXSelector, void*);
        long DialogsClick(FXObject*, FXSelector, void*);
        long AppExit(FXObject*, FXSelector, void*);

//                                  Event Handlers: Update

        long MenuCmdUD(FXObject*, FXSelector, void*);
        long CmdBtnUD(FXObject*, FXSelector, void*);
        long TxtFldUD(FXObject*, FXSelector, void*);

    protected:

        long AppReset(void);
        long ProjectNew(void);
        long ProjectSave(void);
        long ProjectPrint(void);
        long PrintText(void);
        void WriteOut(const FXString&);
        FXdouble GetData(FXTextField*);
        const FXString& MatchDesigner(FXuint Index);
        const FXString& FindBrowser(void);
        const FXString& FormatData(FXdouble, FXchar);

    private:

        MainWindow(void) {}
        MainWindow(const MainWindow&);
        MainWindow& operator=(const MainWindow&);

//                                   Variables

    public:

        enum
        {
            ID_CAPDIV= FXMainWindow::ID_LAST,
            ID_TWOCAP_L_I,
            ID_TWOCAP_L_II,
	    ID_PI_NET,
	    ID_T_NET,
            ID_LOZ_I,
	    ID_LOZ_II,
            ID_HIZ_I,
	    ID_HIZ_II,
	    ID_R_SOURCE,
	    ID_R_LOAD,
	    ID_Q_NOM,
	    ID_FREQ,
            ID_FILE_NEW,
            ID_FILE_SAVE,
            ID_FILE_PRINT,
	    ID_PRINT_TXT,
	    ID_FILE_RESET,
	    ID_FILE_EXIT,
            ID_PROJ_OK,
            ID_PROJ_CLR,
	    ID_PROJ_XNL,
	    ID_HELP_CNTS,
	    ID_ABOUT,
	    ID_DOLPHINS,
	    ID_TITLE,
            ID_LAST
        };

        enum
        {
            MAIN_PANE= FXSwitcher::ID_OPEN_FIRST,
            NET_PANE
        };

//                                  ProjStatus

        enum
        {
            PROJ_NONE= 0,
            PROJ_PEND,
            PROJ_COMP
        };

//                                  SaveStatus

        enum
        {
            NOT_SAVED= 0,
            SAVED
        };

	FXDockSite     *DockUp, *DockDwn, *DockRt, *DockLt;
	FXToolBarShell *Drag1, *Drag2;
	FXMenuPane     *FileMenu, *HelpMenu;
        FXSwitcher     *MainPanel;
        FXImageView    *MainDisp;
        FXLabel        *StatusLbl;
        FXTextField    *NetEntries[NETFIELDS];
        FXPopup        *TopPane;
        FXOptionMenu   *TopologyOM;
        FXText         *CharDisp;
        FXStatusBar    *MainStatusbar;

    protected:

        FXIcon *SmDolphinIco, *NewIco,   *SaveIco,   *PrintIco, *CntsIco, 
               *AboutIco,     *XnlIco,   *ClrIco,    *OKChkIco, *ExitIco,
	       *LEDGrayIco,   *LEDOnIco, *LEDOffIco, *CutIco,   *CopyIco,
               *PasteIco;

    private:

        FXApp      *ThisApp;
        FXuint      ProjStatus, ProjIndex, SaveStatus;
        FXGIFImage *ProjSchemos, *Welcome;
        FXString   *TxtResults;
};

#endif

//-------------------------------- mainwindow.h --------------------------------
