// PanelInternetOptions.h : Declaration of the CPanelInternetOptions

#ifndef __PANELINTERNETOPTIONS_H_
#define __PANELINTERNETOPTIONS_H_

#include "resource.h"       // main symbols
#include <atlhost.h>
#include "RegisterSave.h"

/////////////////////////////////////////////////////////////////////////////
// CPanelInternetOptions
class CPanelInternetOptions : 
	public CAxDialogImpl<CPanelInternetOptions>
{
public:
	VOID SavePatameters();
	CPanelInternetOptions()
	{
	}

	~CPanelInternetOptions()
	{
	}

	enum { IDD = IDD_PANELINTERNETOPTIONS };

BEGIN_MSG_MAP(CPanelInternetOptions)
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

char AccountName[255];

DWORD cbDomainName;
char DomainName[255];
SID_NAME_USE SIDType = SidTypeUser;
unsigned long lSid = 255;

cbDomainName = 255;
DomainName[0]=0;


GetUserName(AccountName,&cbDomainName);
  

HWND hWndDlg;
hWndDlg = GetDlgItem(IDC_USER_NAME);

       ::SetWindowText(hWndDlg,AccountName);
			//
			//


      hWndDlg = GetDlgItem(IDC_TITLE_NAME);
         ::SetWindowText(hWndDlg,_T("User Name"));


  CRegisterSave Reg;
  char BufR[100];





  Reg.UserKeyStore("Lock line",BufR,50,CRegisterSave::READ);
  if (strcmp(BufR,_T("true"))== 0 ) {
	    SendDlgItemMessage(IDC_CHECKISDN, BM_SETCHECK , BST_CHECKED, 0);

  } else {
	    SendDlgItemMessage(IDC_CHECKISDN, BM_SETCHECK , BST_UNCHECKED, 0);
  }

  Reg.UserKeyStore("Line ACCELERATE",BufR,50,CRegisterSave::READ);
  if (strcmp(BufR,_T("true"))== 0 ) {
	    SendDlgItemMessage(IDC_ACCELERATE, BM_SETCHECK , BST_CHECKED, 0);

  } else {
	    SendDlgItemMessage(IDC_ACCELERATE, BM_SETCHECK , BST_UNCHECKED, 0);
  }



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
};

#endif //__PANELINTERNETOPTIONS_H_
