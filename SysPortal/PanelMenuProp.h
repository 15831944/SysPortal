// PanelMenuProp.h : Declaration of the CPanelMenuProp

#ifndef __PANELMENUPROP_H_
#define __PANELMENUPROP_H_

#include "resource.h"       // main symbols
#include "RegisterSave.H"
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CPanelMenuProp
class CPanelMenuProp : 
	public CAxDialogImpl<CPanelMenuProp>
{

public:
	VOID SaveParameters(VOID);
	CPanelMenuProp()
	{
	}

	~CPanelMenuProp()
	{
	}

	enum { IDD = IDD_PANELMENUPROP };

BEGIN_MSG_MAP(CPanelMenuProp)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{

DWORD cbDomainName;
char DomainName[255];
SID_NAME_USE SIDType = SidTypeUser;
unsigned long lSid = 255;

cbDomainName = 255;
DomainName[0]=0;


			//


	  ::SendMessage(GetDlgItem(IDC_COMBO_UPDATE), CB_ADDSTRING, 
            0, (LPARAM) _T(" [None] ")); 
	  ::SendMessage(GetDlgItem(IDC_COMBO_UPDATE), CB_ADDSTRING, 
            0, (LPARAM) _T(" 1 Min")); 
	  ::SendMessage(GetDlgItem(IDC_COMBO_UPDATE), CB_ADDSTRING, 
            0, (LPARAM) _T("30 Min")); 
	  ::SendMessage(GetDlgItem(IDC_COMBO_UPDATE), CB_ADDSTRING, 
            0, (LPARAM) _T(" 1 Hour")); 
	  ::SendMessage(GetDlgItem(IDC_COMBO_UPDATE), CB_ADDSTRING, 
            0, (LPARAM) _T(" 5 Hour")); 
	  ::SendMessage(GetDlgItem(IDC_COMBO_UPDATE), CB_ADDSTRING, 
            0, (LPARAM) _T(" 1 Day")); 
	  ::SendMessage(GetDlgItem(IDC_COMBO_UPDATE), CB_ADDSTRING, 
            0, (LPARAM) _T(" 1 Week")); 
	  
	  
	  //



  CRegisterSave Reg;

    HWND hWndDlg;
    char BufText[255];

    Reg.UserKeyStore("Group folder",BufText,254,CRegisterSave::READ);
	hWndDlg = GetDlgItem(IDC_EDIT_GROUP_FOLDER);
    ::SetWindowText(hWndDlg,BufText);

	

  

    Reg.UserKeyStore("Time update",BufText,254,CRegisterSave::READ);

	char CurSel ;
    CurSel = 1;
	if (strlen(BufText) > 0 ) {
       CurSel	= BufText[0];
	   CurSel = CurSel - '0';
	}
	int k = CurSel;

	    ::SendMessage(GetDlgItem(IDC_COMBO_UPDATE), CB_SETCURSEL, 
            CurSel, (LPARAM) 0); 

//-----
		char BufR[50];
  Reg.UserKeyStore("IExplorer",BufR,50,CRegisterSave::READ);
  if (strcmp(BufR,_T("true"))== 0 ) {
	    SendDlgItemMessage(IDC_RADIO_INTERNET_EXPLORER, BM_SETCHECK , BST_CHECKED, 0);

  } else {
	    SendDlgItemMessage(IDC_RADIO_INTERNET_EXPLORER, BM_SETCHECK , BST_UNCHECKED, 0);
  }

//-----
  Reg.UserKeyStore("Netscape",BufR,50,CRegisterSave::READ);
  if (strcmp(BufR,_T("true"))== 0 ) {
	    SendDlgItemMessage(IDC_RADIO_NETSCAPE, BM_SETCHECK , BST_CHECKED, 0);

  } else {
	    SendDlgItemMessage(IDC_RADIO_NETSCAPE, BM_SETCHECK , BST_UNCHECKED, 0);
  }

//------
//-----
  Reg.UserKeyStore("Default browser",BufR,50,CRegisterSave::READ);
  if (strcmp(BufR,_T("true"))== 0 ) {
	    SendDlgItemMessage(IDC_RADIO_SYSTEM_DEFAULT_BROWSER, BM_SETCHECK , BST_CHECKED, 0);

  } else {
	    SendDlgItemMessage(IDC_RADIO_SYSTEM_DEFAULT_BROWSER, BM_SETCHECK , BST_UNCHECKED, 0);
  }
//-----

  Reg.UserKeyStore("New Window",BufR,50,CRegisterSave::READ);
  if (strcmp(BufR,_T("true"))== 0 ) {
	    SendDlgItemMessage(IDC_RADIO_NEW_WINDOW, BM_SETCHECK , BST_CHECKED, 0);

  } else {
	    SendDlgItemMessage(IDC_RADIO_NEW_WINDOW, BM_SETCHECK , BST_UNCHECKED, 0);
  }

//-----

  Reg.UserKeyStore("Active Window",BufR,50,CRegisterSave::READ);
  if (strcmp(BufR,_T("true"))== 0 ) {
	    SendDlgItemMessage(IDC_RADIO_ACTIVE_WINDOW, BM_SETCHECK , BST_CHECKED, 0);

  } else {
	    SendDlgItemMessage(IDC_RADIO_ACTIVE_WINDOW, BM_SETCHECK , BST_UNCHECKED, 0);
  }

//-----

  Reg.UserKeyStore("Random Update",BufR,50,CRegisterSave::READ);
  if (strcmp(BufR,_T("true"))== 0 ) {
	    SendDlgItemMessage(IDC_CHECK_RANDOM, BM_SETCHECK , BST_CHECKED, 0);

  } else {
	    SendDlgItemMessage(IDC_CHECK_RANDOM, BM_SETCHECK , BST_UNCHECKED, 0);
  }



 
//------
	

		return 1;  // Let the system set the focus
	}

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
	


    VOID DownloadFile(char *FileName,char *strOptName){



	TCHAR dirName[250];
	TCHAR m_DownloadURLFile[MAX_PATH];
	GetCurrentDirectory(250,dirName);
	strcat(dirName,"\\");
	strcat(dirName,FileName);
	HWND hWndDlg = GetDlgItem(IDC_EDIT_GROUP_FOLDER);

    ::GetWindowText(hWndDlg,m_DownloadURLFile,MAX_PATH);
	strcat(m_DownloadURLFile,"/");
	strcat(m_DownloadURLFile,FileName);

   if ( (URLDownloadToFile(
      NULL,                // control's IUnknown
      m_DownloadURLFile ,                         // URL to download
      dirName,// buffer to fill with name
      0,                                      // reserved
      NULL )!=S_OK) )                               // no status information
   {
	   char Buf[255];
	   strcpy(Buf,"Cannot download :\n");
	   strcat(Buf,strOptName);
	   strcat(Buf,"\n File: ");
	   strcat(Buf,FileName);
	   ::MessageBox(NULL,Buf,"alert",MB_OK);

   }
	}

};

#endif //__PANELMENUPROP_H_
