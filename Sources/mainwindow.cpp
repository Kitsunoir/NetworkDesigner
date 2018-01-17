//------------------------------- mainwindow.cpp -------------------------------

/***************************************************************************
                            -  description
                         -----------------------
    Begin                : 9 July, 2012
    Copyright            : (C) 2012 by Simo
    E-Mail               : simo@furrydolphin.net
    Version              : 1.2.0

 ***************************************************************************

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

#include <stdio.h>
#include "mainwindow.h"
#include "netdesign.h"
#include "icons.h"
#include "locations.h"
#include "about.h"
#include "splmsgbox.h"

FXDEFMAP(MainWindow) Callbacks[]=
{
    FXMAPFUNCS(SEL_UPDATE,  MainWindow::ID_R_SOURCE,  MainWindow::ID_FREQ,      MainWindow::TxtFldUD),
    FXMAPFUNCS(SEL_UPDATE,  MainWindow::ID_FILE_NEW,  MainWindow::ID_FILE_EXIT, MainWindow::MenuCmdUD),
    FXMAPFUNCS(SEL_UPDATE,  MainWindow::ID_PROJ_OK,   MainWindow::ID_PROJ_XNL,  MainWindow::CmdBtnUD),
    FXMAPFUNCS(SEL_COMMAND, MainWindow::ID_FILE_NEW,  MainWindow::ID_FILE_EXIT, MainWindow::MainMenuClick),
    FXMAPFUNCS(SEL_COMMAND, MainWindow::ID_CAPDIV,    MainWindow::ID_HIZ_II,    MainWindow::OptionMenuClick),
    FXMAPFUNCS(SEL_COMMAND, MainWindow::ID_PROJ_OK,   MainWindow::ID_PROJ_XNL,  MainWindow::CmdBtnClick),
    FXMAPFUNCS(SEL_COMMAND, MainWindow::ID_HELP_CNTS, MainWindow::ID_DOLPHINS,  MainWindow::DialogsClick),
    FXMAPFUNC(SEL_CLOSE,    MainWindow::ID_TITLE,     MainWindow::AppExit),
    FXMAPFUNC(SEL_SIGNAL,   MainWindow::ID_FILE_EXIT, MainWindow::AppExit)
};

FXIMPLEMENT(MainWindow, FXMainWindow, Callbacks, ARRAYNUMBER(Callbacks))

MainWindow::MainWindow(FXApp *aApp) :
FXMainWindow(aApp, "Network Designer", NULL, NULL, DECOR_ALL, 0, 0, 724, 631),
ThisApp(aApp),
ProjStatus(PROJ_NONE),
ProjIndex(NET_NONE),
SaveStatus(SAVED),
ProjSchemos(0),
Welcome(0)

{
    SmDolphinIco= new FXGIFIcon(ThisApp, atldolphin_gif);
    NewIco=       new FXGIFIcon(ThisApp, New_gif);
    SaveIco=      new FXGIFIcon(ThisApp, filesaveas_gif);
    PrintIco=     new FXGIFIcon(ThisApp, fileprint_gif);
    CopyIco=      new FXGIFIcon(ThisApp, copy_gif);
    CutIco=       new FXGIFIcon(ThisApp, cut_gif);
    PasteIco=     new FXGIFIcon(ThisApp, paste_gif);
    CntsIco=      new FXGIFIcon(ThisApp, help_gif);
    AboutIco=     new FXGIFIcon(ThisApp, about_gif);
    XnlIco=       new FXGIFIcon(ThisApp, CancelX_gif);
    ClrIco=       new FXGIFIcon(ThisApp, clear_up_gif);
    OKChkIco=     new FXGIFIcon(ThisApp, OKCheck_gif);
    ExitIco=      new FXGIFIcon(ThisApp, Exit_gif);
    LEDGrayIco=   new FXGIFIcon(ThisApp, LedGray_gif);
    LEDOnIco=     new FXGIFIcon(ThisApp, LedOn_gif);
    LEDOffIco=    new FXGIFIcon(ThisApp, LedOff_gif);

    setIcon(SmDolphinIco);
    setMiniIcon(SmDolphinIco);
    setTarget(this);
    setSelector(ID_TITLE);


//                                    Layout Managers

    FXVerticalFrame   *MainLO, *SubLO1;
    FXHorizontalFrame *ImgDispLO, *TextLO, *CmdBtnLO;
    FXGroupBox *DataGrp;
    FXMatrix *Grid1;
    FXSplitter *DataLO;

//                                    Main Menu

    DockUp=  new FXDockSite(this, LAYOUT_SIDE_TOP|LAYOUT_FILL_X);
    DockDwn= new FXDockSite(this, LAYOUT_SIDE_BOTTOM|LAYOUT_FILL_X);
    DockRt=  new FXDockSite(this, LAYOUT_SIDE_RIGHT|LAYOUT_FILL_Y);
    DockLt=  new FXDockSite(this, LAYOUT_SIDE_LEFT|LAYOUT_FILL_Y);
    Drag1=   new FXToolBarShell(this, FRAME_RAISED);
    Drag2=   new FXToolBarShell(this, FRAME_RAISED);

    FXMenuBar *MainMenu= new FXMenuBar(DockUp, Drag1, LAYOUT_DOCK_NEXT|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|FRAME_RAISED);
    new FXToolBarGrip(MainMenu, MainMenu, FXMenuBar::ID_TOOLBARGRIP, TOOLBARGRIP_DOUBLE);

    FileMenu= new FXMenuPane(this);
              new FXMenuTitle(MainMenu, "&File", NULL, FileMenu);
              new FXMenuCommand(FileMenu, "&New Project...", NULL, this, ID_FILE_NEW);
              new FXMenuCommand(FileMenu, "&Save as...", NULL, this, ID_FILE_SAVE);
              new FXMenuCommand(FileMenu, "&Print...", NULL, this, ID_FILE_PRINT);
	      new FXMenuCommand(FileMenu, "Print &Text...", NULL, this, ID_PRINT_TXT);
              new FXMenuSeparator(FileMenu);
	      new FXMenuCommand(FileMenu, "&Reset", NULL, this, ID_FILE_RESET);
              new FXMenuCommand(FileMenu, "&Exit", NULL, this, ID_FILE_EXIT);

    HelpMenu= new FXMenuPane(this);
              new FXMenuTitle(MainMenu, "&Help", NULL, HelpMenu, LAYOUT_RIGHT);
              new FXMenuCommand(HelpMenu, "&Contents...", NULL, this, ID_HELP_CNTS);
              new FXMenuCommand(HelpMenu, "&About...", NULL, this, ID_ABOUT);
              new FXMenuSeparator(HelpMenu);
              new FXMenuCommand(HelpMenu, "&Dolphins...", NULL, this, ID_DOLPHINS);

//                                   Tool Bar

    FXToolBar *MainTB= new FXToolBar(DockUp, Drag2, LAYOUT_DOCK_NEXT|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|FRAME_RAISED);
    new FXToolBarGrip(MainTB, MainTB, FXToolBar::ID_TOOLBARGRIP, TOOLBARGRIP_DOUBLE);

    new FXButton(MainTB, "\tSave...\tSave current project to file", SaveIco, this, ID_FILE_SAVE,
                 ICON_ABOVE_TEXT|BUTTON_TOOLBAR|FRAME_RAISED|LAYOUT_TOP|LAYOUT_LEFT);

    new FXButton(MainTB, "\tPrint...\tPrepare hard copy of curent project", PrintIco, this, ID_FILE_PRINT,
                 ICON_ABOVE_TEXT|BUTTON_TOOLBAR|FRAME_RAISED|LAYOUT_TOP|LAYOUT_LEFT);

    new FXButton(MainTB, "\tNew Project\tStart a new project", NewIco, this, ID_FILE_NEW,
                 ICON_ABOVE_TEXT|BUTTON_TOOLBAR|FRAME_RAISED|LAYOUT_TOP|LAYOUT_LEFT);

    new FXFrame(MainTB, FRAME_SUNKEN|LAYOUT_CENTER_Y|LAYOUT_FIXSIZE, 0, 0, 2, 22);

    new FXFrame(MainTB, FRAME_SUNKEN|LAYOUT_CENTER_Y|LAYOUT_FIXSIZE, 0, 0, 2, 22);

    new FXButton(MainTB, "\tAbout...\tShow the \"About\" dialog", AboutIco, this, ID_ABOUT,
                 ICON_ABOVE_TEXT|BUTTON_TOOLBAR|FRAME_RAISED|LAYOUT_TOP|LAYOUT_LEFT);

    new FXButton(MainTB, "\tHelp contents\tShow the on-line help in web browser", CntsIco, this, ID_HELP_CNTS,
                 ICON_ABOVE_TEXT|BUTTON_TOOLBAR|FRAME_RAISED|LAYOUT_TOP|LAYOUT_LEFT);

//                                               Status Bar

    MainStatusbar= new FXStatusBar(this, LAYOUT_SIDE_BOTTOM|LAYOUT_FILL_X|STATUSBAR_WITH_DRAGCORNER|FRAME_RAISED);

    new FXButton(MainStatusbar, "\tClick Me!\tA special message for you", SmDolphinIco, this, ID_DOLPHINS,
		 LAYOUT_FILL_Y|LAYOUT_RIGHT);

    new FXLabel(MainStatusbar, "Project status", NULL, JUSTIFY_RIGHT|FRAME_NONE|ICON_BEFORE_TEXT);

    StatusLbl= new FXLabel(MainStatusbar, "No project", LEDGrayIco, LABEL_NORMAL|FRAME_NORMAL|ICON_AFTER_TEXT);
    new FXToolTip(ThisApp);

/*                                        Main Window

	  1) Make main layout
	     a) Add main panel
	     b) Add Designer panel
*/

    MainLO=    new FXVerticalFrame(this, LAYOUT_SIDE_TOP|FRAME_NORMAL|LAYOUT_FILL);
    MainPanel= new FXSwitcher(MainLO, SWITCHER_HCOLLAPSE|LAYOUT_FILL);

    ImgDispLO= new FXHorizontalFrame(MainPanel, LAYOUT_SIDE_TOP|FRAME_NORMAL|LAYOUT_FILL);
    MainDisp=  new FXImageView(ImgDispLO, NULL, NULL, 0, IMAGEVIEW_NORMAL|LAYOUT_FILL|FRAME_NONE, 0, 0, 690, 477);

    DataLO=  new FXSplitter(MainPanel, SPLITTER_HORIZONTAL|SPLITTER_TRACKING|LAYOUT_FILL|FRAME_NORMAL);
    SubLO1=  new FXVerticalFrame(DataLO, FRAME_NORMAL|LAYOUT_FILL);
    TopPane= new FXPopup(this);
             new FXOption(TopPane, "Capacitor Divider", NULL, this, ID_CAPDIV, JUSTIFY_HZ_APART|ICON_AFTER_TEXT);
             new FXOption(TopPane, "L-Network I", NULL, this, ID_TWOCAP_L_I, JUSTIFY_HZ_APART|ICON_AFTER_TEXT);
             new FXOption(TopPane, "L-Network II", NULL, this, ID_TWOCAP_L_II, JUSTIFY_HZ_APART|ICON_AFTER_TEXT);
             new FXOption(TopPane, "LoZ L-Network I", NULL, this, ID_LOZ_I, JUSTIFY_HZ_APART|ICON_AFTER_TEXT);
	     new FXOption(TopPane, "LoZ L-Network II", NULL, this, ID_LOZ_II, JUSTIFY_HZ_APART|ICON_AFTER_TEXT);
             new FXOption(TopPane, "HiZ L-Network I", NULL, this, ID_HIZ_I, JUSTIFY_HZ_APART|ICON_AFTER_TEXT);
	     new FXOption(TopPane, "HiZ L-Network II", NULL, this, ID_HIZ_II, JUSTIFY_HZ_APART|ICON_AFTER_TEXT);
             new FXOption(TopPane, "Pi Network", NULL, this, ID_PI_NET, JUSTIFY_HZ_APART|ICON_AFTER_TEXT);
             new FXOption(TopPane, "T Network", NULL, this, ID_T_NET, JUSTIFY_HZ_APART|ICON_AFTER_TEXT);

    TopologyOM= new FXOptionMenu(SubLO1, TopPane, FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER|JUSTIFY_HZ_APART|ICON_AFTER_TEXT);

    DataGrp= new FXGroupBox(SubLO1, "Network Data", GROUPBOX_TITLE_CENTER|LAYOUT_CENTER_X|FRAME_GROOVE);
    Grid1=   new FXMatrix(DataGrp, 4, MATRIX_BY_ROWS|PACK_UNIFORM_WIDTH);
    new FXLabel(Grid1, "R-source (R, K)", NULL, JUSTIFY_RIGHT|FRAME_NONE|TEXT_BEFORE_ICON);
    new FXLabel(Grid1, "R-load (R, K)", NULL, JUSTIFY_RIGHT|FRAME_NONE|TEXT_BEFORE_ICON);
    new FXLabel(Grid1, "Q-Factor", NULL, JUSTIFY_RIGHT|FRAME_NONE|TEXT_BEFORE_ICON);
    new FXLabel(Grid1, "Frequency (Hz, KHz, MHz)", NULL, JUSTIFY_RIGHT|FRAME_NONE|TEXT_BEFORE_ICON);
    NetEntries[0]= new FXTextField(Grid1, 16, this, ID_R_SOURCE, TEXTFIELD_LIMITED|TEXTFIELD_NORMAL);
    NetEntries[1]= new FXTextField(Grid1, 16, this, ID_R_LOAD, TEXTFIELD_LIMITED|TEXTFIELD_NORMAL);
    NetEntries[2]= new FXTextField(Grid1, 16, this, ID_Q_NOM, TEXTFIELD_LIMITED|TEXTFIELD_NORMAL);
    NetEntries[3]= new FXTextField(Grid1, 16, this, ID_FREQ, TEXTFIELD_LIMITED|TEXTFIELD_NORMAL);

    TextLO=   new FXHorizontalFrame(DataLO, FRAME_NORMAL|LAYOUT_FILL);
    CharDisp= new FXText(TextLO, NULL, 0, TEXT_WORDWRAP|LAYOUT_FILL);

    CmdBtnLO= new FXHorizontalFrame(MainLO, LAYOUT_SIDE_BOTTOM|FRAME_NORMAL|LAYOUT_FILL_X);
    new FXButton(CmdBtnLO, "&OK", OKChkIco, this, ID_PROJ_OK,
		 BUTTON_NORMAL|LAYOUT_SIDE_LEFT|LAYOUT_CENTER_Y|ICON_BEFORE_TEXT);
    new FXButton(CmdBtnLO, "&Clear", ClrIco, this, ID_PROJ_CLR,
		 BUTTON_NORMAL|LAYOUT_SIDE_LEFT|LAYOUT_CENTER_Y|ICON_BEFORE_TEXT);
    new FXButton(CmdBtnLO, "C&ancel", XnlIco, this, ID_PROJ_XNL,
		 BUTTON_NORMAL|LAYOUT_SIDE_LEFT|LAYOUT_CENTER_Y|ICON_BEFORE_TEXT);
    new FXButton(CmdBtnLO, "&Exit", ExitIco, this, ID_FILE_EXIT,
		 BUTTON_NORMAL|LAYOUT_SIDE_LEFT|LAYOUT_CENTER_Y|ICON_BEFORE_TEXT|LAYOUT_RIGHT);

//                                            Preliminary Setup

    Welcome= new FXGIFImage(ThisApp, NULL, IMAGE_KEEP|IMAGE_SHMI|IMAGE_SHMP, 690, 447);
    FXFileStream PixStream;

    if (PixStream.open(INTROSCREEN, FXStreamLoad))
    {
	Welcome->loadPixels(PixStream);
	Welcome->create();
	PixStream.close();
    }
    else
    {
	fprintf(stderr, "Couldn't load the welcome screen: %s\nFile Corrupt? Relocated?", INTROSCREEN);
	Welcome->create();
	FXDCWindow DevCntx(Welcome);
	DevCntx.setForeground(FXRGB(255, 255, 255));
	DevCntx.fillRectangle(0, 0, 690, 447);
	DevCntx.setForeground(FXRGB(0, 0, 0));
	DevCntx.drawText(60, 214, "Can't load welcome screen. File moved or corrupt?", 49);
    }

    MainDisp->setImage(Welcome);
    TxtResults= new FXString;
}

//------------------------------------------------------------------------------

MainWindow::~MainWindow(void)
{
    delete Drag1;
    delete Drag2;
    delete DockUp;
    delete DockDwn;
    delete DockRt;
    delete DockLt;
    delete FileMenu;
    delete HelpMenu;
    delete SmDolphinIco;
    delete NewIco;
    delete SaveIco;
    delete PrintIco;
    delete CopyIco;
    delete CutIco;
    delete PasteIco;
    delete CntsIco;
    delete AboutIco;
    delete XnlIco;
    delete ClrIco;
    delete OKChkIco;
    delete ExitIco;
    delete LEDGrayIco;
    delete LEDOnIco;
    delete LEDOffIco;
    delete TopPane;
    delete TopologyOM;
    delete Welcome;
    delete TxtResults;

    if (ProjSchemos) delete ProjSchemos;
}

//------------------------------------------------------------------------------

void MainWindow::create(void)
{
    FXMainWindow::create();
    Drag1->create();
    Drag2->create();
    FileMenu->create();
    HelpMenu->create();
    LEDGrayIco->create();
    LEDOnIco->create();
    LEDOffIco->create();
    show(PLACEMENT_SCREEN);
}

//--------------------------- Event Handlers: Update ---------------------------

long MainWindow::CmdBtnUD(FXObject *Sender, FXSelector, void*)
{
    if (ProjStatus == PROJ_PEND)
	Sender->handle(this, FXSEL(SEL_COMMAND, ENABLE), 0);
    else
	Sender->handle(this, FXSEL(SEL_COMMAND, DISABLE), 0);

    return 1;
}

//------------------------------------------------------------------------------

long MainWindow::TxtFldUD(FXObject *Sender, FXSelector CallerID, void*)
{
    FXuint Caller= FXSELID(CallerID);

    if (ProjIndex == NET_NONE)
    {
	Sender->handle(this, FXSEL(SEL_COMMAND, DISABLE), 0);
	return 1;
    }

    switch (Caller)
    {
        case ID_R_SOURCE:

        case ID_FREQ:

        case ID_R_LOAD:
	    if (ProjIndex) Sender->handle(this, FXSEL(SEL_COMMAND, ENABLE), 0);
	    break;

        case ID_Q_NOM:
	    if ((ProjIndex >= TWOCAP_L_I) && (ProjIndex <= PI_NET))
	        Sender->handle(this, FXSEL(SEL_COMMAND, ENABLE), 0);
	    else Sender->handle(this, FXSEL(SEL_COMMAND, DISABLE), 0);
	    break;
    }

    return 1;
}

//------------------------------------------------------------------------------

long MainWindow::MenuCmdUD(FXObject *Sender, FXSelector CallerID, void*)
{
    switch (FXSELID(CallerID))
    {
        case ID_FILE_NEW:
	    if (ProjStatus != PROJ_PEND) Sender->handle(this, FXSEL(SEL_COMMAND, ENABLE), 0);
	    else Sender->handle(this, FXSEL(SEL_COMMAND, DISABLE), 0);
	    break;

        case ID_FILE_SAVE:

        case ID_PRINT_TXT:

        case ID_FILE_PRINT:
	    if (ProjStatus == PROJ_COMP) Sender->handle(this, FXSEL(SEL_COMMAND, ENABLE), 0);
	    else Sender->handle(this, FXSEL(SEL_COMMAND, DISABLE), 0);
	    break;

        default: return 0;
    }

    return 1;
}

//-------------------------- Event Handlers: Command  --------------------------

long MainWindow::MainMenuClick(FXObject *Sender, FXSelector CallerID, void*)
{
    long RetVal= 0;

    switch (FXSELID(CallerID))
    {
        case ID_FILE_NEW:   RetVal= ProjectNew(); break;

        case ID_FILE_SAVE:  RetVal= ProjectSave(); break;

        case ID_FILE_PRINT: RetVal= ProjectPrint(); break;

        case ID_PRINT_TXT:  RetVal= PrintText(); break;

        case ID_FILE_RESET: RetVal= AppReset(); break;

        case ID_FILE_EXIT:  RetVal= AppExit(Sender, CallerID, 0); break;
    }

    return RetVal;
}

//------------------------------------------------------------------------------

long MainWindow::OptionMenuClick(FXObject*, FXSelector CallerID, void*)
{
    ProjStatus= PROJ_PEND;
    SaveStatus= NOT_SAVED;

    StatusLbl->setText("Start New Project");

    switch (FXSELID(CallerID))
    {
        case ID_CAPDIV:
	    ProjIndex= CAPDIV;
	    CharDisp->setText(CAPDIV_DSC);
	    *TxtResults= "Capacitor Divider\n";
	    break;

        case ID_TWOCAP_L_I:
	    ProjIndex= TWOCAP_L_I;
	    CharDisp->setText(TWOCAP_L_DSC);
	    *TxtResults= "L-Network Type I\n";
	    break;

        case ID_TWOCAP_L_II:
	    ProjIndex= TWOCAP_L_II;
	    CharDisp->setText(TWOCAP_L_DSC);
	    *TxtResults= "L-Network Type II";
	    break;

        case ID_LOZ_I:
	    ProjIndex= L_LOZ_I;
	    CharDisp->setText(L_LOZ_DSC);
	    *TxtResults= "Lo-Z L-Network: Parallel Inductor\n";
	    break;

        case ID_LOZ_II:
	    ProjIndex= L_LOZ_II;
	    CharDisp->setText(L_LOZ_DSC);
	    *TxtResults= "Lo-Z L-Network:Parallel Capacitor\n";
	    break;

        case ID_HIZ_I:
	    ProjIndex= L_HIZ_I;
	    CharDisp->setText(L_HIZ_DSC);
	    *TxtResults= "Hi-Z L-Network: Series Inductor\n";
	    break;

        case ID_HIZ_II:
	    ProjIndex= L_HIZ_II;
	    CharDisp->setText(L_HIZ_DSC);
	    *TxtResults= "Hi-Z L-NetworkL Series Capacitor\n";
	    break;

        case ID_PI_NET:
	    ProjIndex= PI_NET;
	    CharDisp->setText(PI_NET_DSC);
	    *TxtResults= "Pi Network\n";
	    break;

        case ID_T_NET:
	    ProjIndex= T_NET;
	    CharDisp->setText(T_NET_DSC);
	    *TxtResults= "T Network\n";
	    break;
    }

    return 1;
}

long MainWindow::CmdBtnClick(FXObject*, FXSelector CallerID, void*)
{
    switch (FXSELID(CallerID))
    {
        case ID_PROJ_OK:
	    {
		FXString Results;
	        Results= MatchDesigner(ProjIndex);

		if (Results == "None") return 1;

	        WriteOut(Results);
	        ProjStatus= PROJ_COMP;
                StatusLbl->setIcon(LEDOffIco);
	        StatusLbl->setText("Project Complete: Not Saved");
		MainPanel->handle(this, FXSEL(SEL_COMMAND, MAIN_PANE), 0);
	    }
	    break;

        case ID_PROJ_CLR:
	    for (int i= 0; i < NETFIELDS; i++)
	        NetEntries[i]->setText("");
	    break;

        case ID_PROJ_XNL: ProjectNew();
    }

    return 1;
}

//------------------------------------------------------------------------------

long MainWindow::DialogsClick(FXObject*, FXSelector CallerID, void*)
{
    FXString UseBrowser, SysArg;
    FXDialogBox *SplMsg= 0;

    switch (FXSELID(CallerID))
    {
      case ID_ABOUT:
	  SplMsg= new About(ThisApp);
	  SplMsg->execute(PLACEMENT_SCREEN);
	  break;

      case ID_DOLPHINS:
	  SplMsg= new SplMsgBox(ThisApp);
	  SplMsg->execute(PLACEMENT_SCREEN);
	  break;

      case ID_HELP_CNTS:
	  UseBrowser= FindBrowser();

	  if (UseBrowser == "None")
	  {
	      FXMessageBox::error(ThisApp, MBOX_OK, "NetworkDesigner Error", HELP_ERROR);
	      return 1;
	  }

	  SysArg= UseBrowser + DOCPATH;

	  if (system(SysArg.text()))
	      FXMessageBox::error(ThisApp, MBOX_OK, "NetworkDesigner Error", OPEN_ERROR);
    }

    if (SplMsg) delete SplMsg;
    return 1;
}

//                                 Methods: Support

long MainWindow::ProjectNew(void)
{
    FXuint Code= 0;

    if ((SaveStatus == NOT_SAVED) && (ProjStatus == PROJ_COMP))
    {
	Code= FXMessageBox::question(ThisApp, MBOX_OK_CANCEL, "NetworkDesigner Question", NEW_SAVE_WARN);

	if (Code != MBOX_CLICKED_OK) return 0;
    }

    ProjIndex=  NET_NONE;
    ProjStatus= PROJ_NONE;
    SaveStatus= NOT_SAVED;

    if (ProjSchemos)
    {
	delete ProjSchemos;
	ProjSchemos= 0;
    }

    StatusLbl->setText("New Project");
    StatusLbl->setIcon(LEDGrayIco);
    MainPanel->handle(this, FXSEL(SEL_COMMAND, NET_PANE), 0);

    for (int i= 0; i < NETFIELDS; i++)
	NetEntries[i]->setText("");

    TxtResults->clear();

    return 1;
}

//------------------------------------------------------------------------------

long MainWindow::ProjectSave(void)
{
    FXuint   Code;
    FXString FileName;

    FXFileDialog SaveDlg(ThisApp, "Save Project to File");
    SaveDlg.setSelectMode(SELECTFILE_ANY);
    SaveDlg.setPatternList("Project (*.gif)");
    SaveDlg.setCurrentPattern(0);

    if (! SaveDlg.execute(PLACEMENT_OWNER))
    {
        FXMessageBox::information(ThisApp, MBOX_OK, "NetworkDesigner Advisory",
				  "File Save Cancelled");
        return 0;
    }

    FileName= SaveDlg.getFilename();

    if (FXStat::exists(FileName))
      Code= FXMessageBox::question(ThisApp, MBOX_YES_NO, "PTX Designer Question",
				   "Overwrite File: %s", FileName.text());

    if (Code == MBOX_CLICKED_NO) return 1;

    FXFile WriteFile(FileName, FXFile::Writing);
    FXFileStream PixStream;
    ProjSchemos->restore();
    PixStream.open(FileName, FXStreamSave);
    ProjSchemos->savePixels(PixStream);
    PixStream.close();
    SaveStatus= SAVED;
    StatusLbl->setText("Project Complete: Saved");
    StatusLbl->setIcon(LEDOnIco);
    return 1;
}

//------------------------------------------------------------------------------

long MainWindow::PrintText(void)
{
    FXint Length;                                    //  Length of the text buffer
    const FXint MarginX=  60;                        //  Page metrics: fix the left margin
    FXint MarginY=        60, LineHeight;            //  Page metrics: start of top margin and line spacing
    const FXchar *Buffer= 0, *Head= 0, *Tail= 0;
    FXchar C;
    FXint i= 1;
    FXdouble PageHeight;

    FXPrinter MyPrinter;  //  Declair a print job
/*
          Invoke print dialog box to get the system printer
	  and set it up for printing
*/
    FXPrintDialog PDlgBox(this, "Print Current Project");
    if (PDlgBox.execute(PLACEMENT_OWNER))  //  Start if #1
    {
      PDlgBox.getPrinter(MyPrinter);
      FXDCPrint Pdc(ThisApp);  
      if (! Pdc.beginPrint(MyPrinter))
      {
        FXMessageBox::error(this, MBOX_OK, "Network Designer Error", "Print Fault");
        return 1;
      }

      Length=          TxtResults->length();
      FXFont *SysFont= ThisApp->getNormalFont();
      LineHeight=      SysFont->getFontHeight();
      PageHeight=      MyPrinter.mediaheight;

      FXchar OneLine[Length];
      Pdc.setFont(SysFont);
      Pdc.beginPage(i);
      TxtResults->append('\n');
      Buffer= TxtResults->text();
      Head=   Tail= Buffer;
/*
          Note: Parse the text buffer into a new string at the newline
	        breaks. Otherwise, printer treats the buffer as one
		long string. FOX bug or ideosyncracy?

          1)  Parse the string to newline (character copy)
	  2)  Append C string terminator (ASCII Null)
	  3)  Draw text into image and print.
	  4)  Update the vertical margin, and reset to grab the next line.
*/
      while ((C= *Tail++))
      {
	  if (C == '\n')
	  {
	      memcpy(&OneLine[0], Head, Tail-Head);
	      OneLine[Tail-Head-1]= '\0';
	      Pdc.drawText(MarginX, MarginY, OneLine, Tail-Head);
	      MarginY+= LineHeight;
	      Head= Tail;

	      if (PageHeight - MarginY < 145)
	      {
		  Pdc.endPage();
		  MarginY= 60;
		  Pdc.beginPage(i++);
	      }
	  }
      }

      Pdc.endPage();
      Pdc.endPrint();
    }

    else FXMessageBox::information(this, MBOX_OK, "Network Designer Advisory", "Print job cancelled");

    return 1;
}

//------------------------------------------------------------------------------

long MainWindow::ProjectPrint(void)
{
/*
       ImgToPrint: (Pointer: FXImage) - Generic image object pointer. Initialize with
                                        the image on the main display.
       X: (FXint, constant)  - Starting coordinate of the printer drawing window
       Y: (FXint, Constant)  -    "         "       "  "     "       "      "
       MyPrinter: (FXPrinter) - FOX system printer interface object.
*/

    FXImage     *ImgToPrint;
    const FXint X= 0;
    const FXint Y= 0;
    FXPrinter   MyPrinter;

/*
       * Invoke the FOX printer dialog: get user specified printer metrics.
       * Write the printer metrics to the FOX application "registry".
       * Get the displayed image, restore client-side image resources.
       * Rotate the image so that it will print correctly, then restore
         so it will display properly.
*/

    FXPrintDialog PrintDB(this, "Print Current Project");

    if (PrintDB.execute(PLACEMENT_OWNER))
    {
       ThisApp->beginWaitCursor();
       PrintDB.getPrinter(MyPrinter);
       FXDCPrint PrintCntx(ThisApp);

       if(! PrintCntx.beginPrint(MyPrinter))
       {
	  FXMessageBox::error(this, MBOX_OK, "NetworkDesigner Error",
			      "Print Fault");
	  ThisApp->endWaitCursor();
	  return 1;
       }

       ImgToPrint= MainDisp->getImage();
       ImgToPrint->restore();
       PrintCntx.beginPage(1);
       PrintCntx.drawImage(ImgToPrint, X, Y);
       PrintCntx.endPage();
       PrintCntx.endPrint();
       ThisApp->endWaitCursor();
     }
     else FXMessageBox::information(this, MBOX_OK, "NetworkDesigner",
				    "Print Job Cancelled");

     return 1;
}

//------------------------------------------------------------------------------

long MainWindow::AppReset(void)
{
    FXuint Code= 0;

    if ((SaveStatus == NOT_SAVED) && (ProjStatus == PROJ_COMP))
    {
	Code= FXMessageBox::question(ThisApp, MBOX_OK_CANCEL, "NetworkDesigner Question", NEW_SAVE_WARN);

	if (Code != MBOX_CLICKED_OK) return 0;
    }

    ProjStatus= PROJ_NONE;
    ProjIndex=  NET_NONE;
    SaveStatus= SAVED;

    StatusLbl->setText("No Project");
    StatusLbl->setIcon(LEDGrayIco);
    MainDisp->setImage(Welcome);
    MainPanel->handle(this, FXSEL(SEL_COMMAND, MAIN_PANE), 0);
    TxtResults->clear();

    if (ProjSchemos)
    {
	delete ProjSchemos;
	ProjSchemos= 0;
    }

    return 1;
}

//------------------------------------------------------------------------------

void MainWindow::WriteOut(const FXString &TxtDesc)
{
/*
    Text Metrics:
        Lines: Number of lines to write to image
        Length: Text length

    Font Metrics:
        FontHeight: the height of each line
        MarginX: Left margin of text in image (fixed)
	MarginY: Y co-ordinate of text

    Image Metrics:
        DiagramH: Height of circuit diagram
        ImgHeight: Total height of generated image
	ImgWidth: Total width of image (fixed).

    Images:
        CircuitSchemo: Circuit diagram image loaded from file
	ProjSchemos: Generated image displaying text, incorporating CircuitDiagram
*/

    FXint Length;
    FXint MarginY, FontHeight, CenterX, DiagramH;
    const FXint MarginX=   30;
    const FXint OffsetX=   10;
    const FXint OffsetY=   20;
    const FXint ImgWidth=  690;
    const FXint ImgHeight= 447;
    const FXint SchemoH=   200;
    const FXint SchemoW=   500;
    FXchar *Buffer= 0, *Head= 0, *Tail= 0, C;

    FXString FileName;

    FXGIFImage *CircuitSchemo= 0;

    switch(ProjIndex)
    {
        case TWOCAP_L_I:  FileName= TWOCAP_L_I_PIC; break;

        case TWOCAP_L_II: FileName= TWOCAP_L_II_PIC; break;

        case T_NET:       FileName= T_NET_PIC; break;

        case PI_NET:      FileName= PI_NET_PIC; break;

        case L_LOZ_I:     FileName= L_LOZ_I_PIC; break;

        case L_LOZ_II:    FileName= L_LOZ_II_PIC; break;

        case L_HIZ_I:     FileName= L_HIZ_I_PIC; break;

        case L_HIZ_II:    FileName= L_HIZ_II_PIC; break;

        case CAPDIV:      FileName= CAPDIV_PIC; break;
    }

    FXFont *SysFont= ThisApp->getNormalFont();
    SysFont->create();
    FontHeight= SysFont->getFontHeight();

    CircuitSchemo= new FXGIFImage(ThisApp, NULL, IMAGE_KEEP|IMAGE_SHMI|IMAGE_SHMP);
    FXFileStream PixStream;

    if (PixStream.open(FileName, FXStreamLoad))
    {
	CircuitSchemo->loadPixels(PixStream);
	PixStream.close();
	CircuitSchemo->create();
	CenterX= (ImgWidth - SchemoW)/2;
	DiagramH= SchemoH;
    }
    else
    {
	FXMessageBox::information(ThisApp, MBOX_OK, "NetworkDesigner Advisory",
				  IMG_FILE_ERROR, FileName.text());
	delete CircuitSchemo;
	CircuitSchemo= 0;
	DiagramH= 0;
	CenterX= 0;
    }

//                           Set up for text write

    ProjSchemos= new FXGIFImage(ThisApp, NULL, IMAGE_SHMI|IMAGE_SHMP, ImgWidth, ImgHeight);
    ProjSchemos->create();

    FXDCWindow DevCntx(ProjSchemos);
    DevCntx.setFont(SysFont);
    DevCntx.setForeground(FXRGB(255, 255, 255));
    DevCntx.fillRectangle(0, 0, ImgWidth, ImgHeight);

    if (CircuitSchemo) DevCntx.drawImage(CircuitSchemo, CenterX, 0);

    DevCntx.setForeground(FXRGB(0, 0, 0));
    DevCntx.drawLine(OffsetX, DiagramH+OffsetY, ImgWidth-OffsetX, DiagramH+OffsetY);
    MarginY= DiagramH + 2*OffsetY;
    Length= TxtDesc.length();
    FXchar Oneline[Length];

    Buffer= (FXchar*)(TxtDesc.text());
    Head= Tail= Buffer;

    while((C= *Head++))
    {
	if (C == '\n')
	{
	    memcpy(&Oneline[0], Tail, Head-Tail);
	    Oneline[Head-Tail-1]= '\0';

	    if (Oneline[0]) DevCntx.drawText(MarginX, MarginY, Oneline, Head-Tail-1);

	    MarginY+= FontHeight;
	    Tail= Head;
	}
    }

    MainDisp->setImage(ProjSchemos);
    if (CircuitSchemo) delete CircuitSchemo;
}

//------------------------------------------------------------------------------

const FXString& MainWindow::MatchDesigner(FXuint Index)
{
    using namespace NetDesign;

    static FXString RetVal;
    FXdouble Rsrc, Rload, Freq;
    FXuint ErrCode;

    RetVal.clear();

    Rsrc=  GetData(NetEntries[0]);
    Rload= GetData(NetEntries[1]);
    Freq=  GetData(NetEntries[3]);

    if (! Rsrc)  USER_ENTRY_ERROR(0)
    if (! Rload) USER_ENTRY_ERROR(1)
    if (! Freq)  USER_ENTRY_ERROR(3)

    switch (Index)
    {
        case TWOCAP_L_I:

        case TWOCAP_L_II:
        {
	    FXdouble Qi, Qload, XC1, XC2, XL, C1, C2, L;

	    Qi= GetData(NetEntries[2]);

	    if (! Qi) USER_ENTRY_ERROR(2)

	    ErrCode= SeriesNetDesigner(Rsrc, Rload, Qi, Qload, XC1, XC2, XL, ProjIndex);

	    if (ErrCode)
	    {
		RetVal="\nError: Source resistance is larger than load resistance\n";
	        goto EXIT;
	    }

	    C1= 1/(XC1 * ANGULAR(Freq));
	    C2= 1/(XC2 * ANGULAR(Freq));
	    L=  XL/ANGULAR(Freq);

	    RetVal.append(FXStringFormat("Frequency=%s", FormatData(Freq, 'f').text()));
	    RetVal.append(FXStringFormat("\nDesign Nominal Q= %f\n", Qload));
	    RetVal.append(FXStringFormat("\nC1= %s", FormatData(C1, 'c').text()));
	    RetVal.append(FXStringFormat("\nC2= %s", FormatData(C2, 'c').text()));
	    RetVal.append(FXStringFormat("\nL= %s\n", FormatData(L, 'l').text()));
	}
	break;

        case T_NET:
        {
	    FXdouble Qnom, X1, B2, X3, C, L1, L2;

	    Qnom= GetData(NetEntries[2]);

	    if (! Qnom) USER_ENTRY_ERROR(2)

	    ErrCode= TNetDesigner(Rsrc, Rload, Qnom, X1, B2, X3);

            if (ErrCode)
	    {
	        RetVal= "Error: R-source is larger than R-load\n";
		goto EXIT;
	    }

	    C=  B2/ANGULAR(Freq);
	    L1= X3/ANGULAR(Freq);
	    L2= X1/ANGULAR(Freq);

	    RetVal.append(FXStringFormat("Frequency= %s", FormatData(Freq, 'f').text()));
	    RetVal.append(FXStringFormat("\nDesign Nominal Q= %f\n", Qnom));
	    RetVal.append(FXStringFormat("\nL1= %s", FormatData(L1, 'l').text()));
	    RetVal.append(FXStringFormat("\nL2= %s", FormatData(L2, 'l').text()));
	    RetVal.append(FXStringFormat("\nC= %s\n", FormatData(C, 'c').text()));
	    RetVal.append(FXStringFormat("\nR-source= %s", FormatData(Rsrc, 'z').text()));
	    RetVal.append(FXStringFormat("\nR-load= %s\n", FormatData(Rload, 'z').text()));
        }
        break;

        case L_HIZ_I:
	{
	    FXdouble X1, X2, Qload, L, C;

	    ErrCode= LNetDesigner(Rsrc, Rload, X1, X2, Qload, ProjIndex);

	    if (ErrCode)
	    {
		RetVal= "Error: R-source is too small\n";
		goto EXIT;
	    }

	    L= X1/ANGULAR(Freq);
	    C= 1/(ANGULAR(Freq) * X2);

	    RetVal.append(FXStringFormat("Frequency= %s", FormatData(Freq, 'f').text()));
	    RetVal.append(FXStringFormat("\nQ-Factor= %f\n", Qload));
	    RetVal.append(FXStringFormat("\nL= %s", FormatData(L, 'l').text()));
	    RetVal.append(FXStringFormat("\nC= %s\n", FormatData(C, 'c').text()));
	    RetVal.append(FXStringFormat("\nRsource= %s", FormatData(Rsrc, 'z').text()));
	    RetVal.append(FXStringFormat("\nRload= %s\n", FormatData(Rload, 'z').text()));
	}
	break;

        case L_HIZ_II:
	{
	    FXdouble X1, X2, Qload, L, C;

	    ErrCode= LNetDesigner(Rsrc, Rload, X1, X2, Qload, ProjIndex);

	    if (ErrCode)
	    {
		RetVal= "Error: R-source is too small\n";
		goto EXIT;
	    }

	    L= X2/ANGULAR(Freq);
	    C= 1/(ANGULAR(Freq) * X1);

	    RetVal.append(FXStringFormat("Frequency= %s", FormatData(Freq, 'f').text()));
	    RetVal.append(FXStringFormat("\nQ-Factor= %f\n", Qload));
	    RetVal.append(FXStringFormat("\nL= %s", FormatData(L, 'l').text()));
	    RetVal.append(FXStringFormat("\nC= %s\n", FormatData(C, 'c').text()));
	    RetVal.append(FXStringFormat("\nRsource= %s", FormatData(Rsrc, 'z').text()));
	    RetVal.append(FXStringFormat("\nRload= %s\n", FormatData(Rload, 'z').text()));
	}
	break;

        case L_LOZ_I:
	{
	    FXdouble X1, X2, Qload, L, C;

	    ErrCode= LNetDesigner(Rsrc, Rload, X1, X2, Qload, ProjIndex);

	    if (ErrCode)
	    {
		RetVal= "Error: R-load is too small\n";
		goto EXIT;
	    }

	    L= X1/ANGULAR(Freq);
	    C= 1/(ANGULAR(Freq) * X2);

	    RetVal.append(FXStringFormat("Frequency= %s", FormatData(Freq, 'f').text()));
	    RetVal.append(FXStringFormat("\nQ-Factor= %f\n", Qload));
	    RetVal.append(FXStringFormat("\nL= %s", FormatData(L, 'l').text()));
	    RetVal.append(FXStringFormat("\nC= %s\n", FormatData(C, 'c').text()));
	    RetVal.append(FXStringFormat("\nRsource= %s", FormatData(Rsrc, 'z').text()));
	    RetVal.append(FXStringFormat("\nRload= %s\n", FormatData(Rload, 'z').text()));
	}
	break;

        case L_LOZ_II:
	{
	    FXdouble X1, X2, Qload, L, C;

	    ErrCode= LNetDesigner(Rsrc, Rload, X1, X2, Qload, ProjIndex);

	    if (ErrCode)
	    {
		RetVal= "Error: R-load is too small\n";
		goto EXIT;
	    }

	    L= X2/ANGULAR(Freq);
	    C= 1/(ANGULAR(Freq) * X1);

	    RetVal.append(FXStringFormat("Frequency= %s", FormatData(Freq, 'f').text()));
	    RetVal.append(FXStringFormat("\nQ-Factor= %f\n", Qload));
	    RetVal.append(FXStringFormat("\nL= %s", FormatData(L, 'l').text()));
	    RetVal.append(FXStringFormat("\nC= %s\n", FormatData(C, 'c').text()));
	    RetVal.append(FXStringFormat("\nRsource= %s", FormatData(Rsrc, 'z').text()));
	    RetVal.append(FXStringFormat("\nRload= %s\n", FormatData(Rload, 'z').text()));
	}
	break;

        case PI_NET:
        {
	    FXdouble B1, B3, Qdes, C1, C2, L, X2;

	    Qdes=   GetData(NetEntries[2]);

            if (! Qdes) USER_ENTRY_ERROR(2)

	    ErrCode= PiDesigner(Rsrc, Rload, Qdes, B1, B3, X2);

	    if (ErrCode)
	    {
		RetVal= "Rsrc is less than Rload\n";
		goto EXIT;
	    }

	    C1= B3/ANGULAR(Freq);
	    C2= B1/ANGULAR(Freq);
	    L=  X2/ANGULAR(Freq);

	    RetVal.append(FXStringFormat("Frequency= %s", FormatData(Freq, 'f').text()));
	    RetVal.append(FXStringFormat("\nQ-Factor= %f\n", Qdes));
	    RetVal.append(FXStringFormat("\nC1= %s", FormatData(C1, 'c').text()));
	    RetVal.append(FXStringFormat("\nC2= %s", FormatData(C2, 'c').text()));
	    RetVal.append(FXStringFormat("\nL= %s\n", FormatData(L, 'l').text()));
	    RetVal.append(FXStringFormat("\nR-source= %s", FormatData(Rsrc, 'z').text()));
	    RetVal.append(FXStringFormat("\nR-load= %s\n", FormatData(Rload, 'z').text()));
	}
	break;

        case CAPDIV:
        {
	    FXdouble XC1, XC2, XL, Qloaded, C1, C2, L;

	    Qloaded= GetData(NetEntries[2]);

	    if (! Qloaded) USER_ENTRY_ERROR(2)

            ErrCode= CapDivDesigner(Rsrc, Rload, Qloaded, XC1, XC2, XL);

	    switch (ErrCode)
	    {
	        case 1:
		    RetVal= "Error: R-source is too small\n";
		    goto EXIT;
		    break;

	        case 2:
		    RetVal= "Error: the design nominal Q-factor is too small\n";
		    goto EXIT;
		    break;
	    }

	    C1= 1/(XC1 * ANGULAR(Freq));
	    C2= 1/(XC2 * ANGULAR(Freq));
	    L=  XL/ANGULAR(Freq);

	    RetVal.append(FXStringFormat("Frequency= %s", FormatData(Freq, 'f').text()));
	    RetVal.append(FXStringFormat("\nQ-Factor= %f\n", Qloaded));
	    RetVal.append(FXStringFormat("\nC1= %s", FormatData(C1, 'c').text()));
	    RetVal.append(FXStringFormat("\nC2= %s", FormatData(C2, 'c').text()));
	    RetVal.append(FXStringFormat("\nL= %s\n", FormatData(L, 'l').text()));
	    RetVal.append(FXStringFormat("\nRsource= %s", FormatData(Rsrc, 'z').text()));
	    RetVal.append(FXStringFormat("\nRload= %s\n", FormatData(Rload, 'z').text()));
        }
	break;
    }

    EXIT:
    TxtResults->append(RetVal);
    return RetVal;
}

//------------------------------------------------------------------------------

const FXString& MainWindow::FindBrowser(void)
{
/*
    Length: Length of the text in the file
    Buffer: Pointer to character array of file contents
    Head, Tail: Pointers into the buffer for text parse
    RetVal: Either a file name or error advisory
*/

    FXint   Length;
    FXchar *Buffer= 0, *Head= 0, *Tail= 0, C;
    static  FXString RetVal;

    FXString BrowserPaths= FXString(BROWSER_PATHS);
    FXFile   ReadConfig(BrowserPaths, FXFile::Reading);

    RetVal= "None";

    if (! ReadConfig.isOpen())
    {
        fprintf(stderr, "Couldn't open the config file: %s", BrowserPaths.text());
	return RetVal;
    }

    Length= ReadConfig.size();
    FXchar Oneline[Length];
    FXMALLOC(&Buffer, FXchar, CEIL(Length + 1));

    ReadConfig.readBlock(Buffer, Length);

/*
    Parse the file contents to extract the list of possible paths to
    web browsers. If found a file that *is* a file, and is executable,
    we may have a possibility. Return it to the caller.

*/
    Head= Tail= Buffer;

    while ((C= *Head++))
    {
	if (C == '\n')
	{
	    memcpy(&Oneline[0], Tail, Head - Tail);   //  Fill the character array...
	    Oneline[Head - Tail - 1]= '\0';           //  ...Make it a C string; ditch new line

	    if ((Oneline[0] != '#') && (Oneline[0]))  //  Ditch comments; empty lines
	    {
	        if ((FXStat::isFile(Oneline)) && (FXStat::isExecutable(Oneline)))
		{
		  RetVal= Oneline;
		  FXFREE(&Buffer);
		  Buffer= 0;
		  break;
		}
	    }
	    Tail= Head;
	}
    }
    
    if (Buffer) FXFREE(&Buffer);

    return RetVal;
}

//------------------------------------------------------------------------------

/*
     Name: GetData

     Type: FXdouble function

     Parameters: FXTextField (Pointer) -- Pointer to the text field to extract
                 numeric user entry

     Returns: Real number, with appropriate scaling
*/

FXdouble MainWindow::GetData(FXTextField *Current)
{
    FXString TextEntry;
    FXdouble Mantissa, Multiplier;

    TextEntry= Current->getText();

#ifdef INSTR
    printf("\nEntering function MainWindow::GetData");
#endif

    if (TextEntry.find('R') > -1)
        Multiplier= 1.0;
    else if (TextEntry.find('K') > -1)
	Multiplier= 1000.0;
    else if (TextEntry.find('M') > -1)
	Multiplier= 1.0E6;
    else if (TextEntry.find('u') > -1)
	Multiplier= 1.0E-6;
    else if (TextEntry.find('n') > -1)
	Multiplier= 1.0E-9;
    else if (TextEntry.find('p') > -1)
	Multiplier= 1.0E-12;
    else Multiplier= 1.0;

    Mantissa= FXDoubleVal(TextEntry);

#ifdef INSTR
  printf("\nIn funcrion: MainWindow::GetData: TextEntry= %s", TextEntry.text());
  printf("\nIn function: MainWindow::GetData: Mantissa= %E", Mantissa);
  printf("\nIn function: Mainwindow::GetData: Multiplier= %E", Multiplier);
  printf("\nLeaving function Mainwindow::GetData");
#endif

    return Mantissa * Multiplier;
}

//------------------------------------------------------------------------------

const FXString& MainWindow::FormatData(FXdouble Current, FXchar IDCode)
{
    static FXString RetVal;

#ifdef INSTR
    printf("\nEntering function MainWindow::FormatData");
#endif

    switch(IDCode)
    {
      case 'c':

	if (Current * 1.0E12 <= 6.8E3) RetVal= FXStringFormat("%fpF", Current * 1.0E12);
	else RetVal= FXStringFormat("%fuF", Current * 1.0E6);
	break;

      case 'f':

	if (Current / 1.0E6 >= 1.0) RetVal= FXStringFormat("%fMHz", Current/1.0E6);
	else if (Current / 1.0E3 >= 1.0) RetVal= FXStringFormat("%fKHz", Current/1.0E3);
	else RetVal= FXStringFormat("%fHz", Current);
	break;

      case 'l':

	if (Current >= 1.0) RetVal=  FXStringFormat("%fH", Current);
	else if (Current * 1000.0 >= 1.0) RetVal= FXStringFormat("%fmH", Current * 1000.0);
	else if (Current * 1.0E6 >= 1.0) RetVal= FXStringFormat("%fuH", Current * 1.0E6);
	else RetVal= FXStringFormat("%fnH", Current * 1.0E9);
	break;

      case 'z':

	if (Current / 1.0E6 >= 1.0) RetVal= FXStringFormat("%fMEG", Current/1.0E6);
	else if (Current / 1.0E3 >= 1.0) RetVal= FXStringFormat("%fK", Current/1.0E3);
	else RetVal= FXStringFormat("%fR", Current);
    }
#ifdef INSTR
    printf("\nCurrent= %E", Current);
    printf("\nRetVal= %s", RetVal.text());
    printf("\nLeaving function MainWindow::FormatData");
#endif

    return RetVal;
}

//------------------------------------------------------------------------------

long MainWindow::AppExit(FXObject*, FXSelector, void*)
{
    FXuint Code= 0;

    if ((SaveStatus == NOT_SAVED) && (ProjStatus == PROJ_COMP))
    {
	Code= FXMessageBox::question(ThisApp, MBOX_OK_CANCEL, "NetworkDesigner Question", EXIT_SAVE_WARN);

	if (Code != MBOX_CLICKED_OK) return 0;
    }

    ThisApp->exit(0);
    return 0;
}

//------------------------------- mainwindow.cpp -------------------------------
