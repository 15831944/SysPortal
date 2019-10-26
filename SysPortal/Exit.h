// Exit.h : Declaration of the CExit

#ifndef __EXIT_H_
#define __EXIT_H_

#include "resource.h"       // main symbols
#include <atlhost.h>
#include "RegisterSave.h"

/////////////////////////////////////////////////////////////////////////////
// CExit
class CExit : 
	public CAxDialogImpl<CExit>
{
public:
	BOOL boolReturnValue;
	CExit()
	{
	}

	~CExit()
	{
	}

	enum { IDD = IDD_EXIT };

BEGIN_MSG_MAP(CExit)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	COMMAND_HANDLER(IDOK, BN_CLICKED, OnOK)
	COMMAND_HANDLER(IDC_BUTTON_CANCEL, BN_CLICKED, OnClickedButton_cancel)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
	boolReturnValue = FALSE;
    HICON hIcon = ::LoadIcon(_Module.GetModuleInstance(), MAKEINTRESOURCE(IDI_HOTINTERNET));
	this->SetIcon(hIcon);
		return 1;  // Let the system set the focus
	}

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		boolReturnValue = TRUE;
        CRegisterSave Reg;
	    Reg.AutoRun(FALSE);
		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
	LRESULT OnClickedButton_cancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		// TODO : Add Code for control notification handler.
		return 0;
	}
};

#endif //__EXIT_H_
