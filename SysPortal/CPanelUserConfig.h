// CPanelUserConfig.h : Declaration of the CCPanelUserConfig

#ifndef __CPANELUSERCONFIG_H_
#define __CPANELUSERCONFIG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CCPanelUserConfig
class CCPanelUserConfig : 
	public CAxDialogImpl<CCPanelUserConfig>
{
public:
	CCPanelUserConfig()
	{
	}

	~CCPanelUserConfig()
	{
	}

	enum { IDD = IDD_CPANELUSERCONFIG };

BEGIN_MSG_MAP(CCPanelUserConfig)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

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
public:
	VOID SaveParameters(VOID);
};

#endif //__CPANELUSERCONFIG_H_
