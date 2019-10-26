// DialogProp.h : Declaration of the CDialogProp

#ifndef __DIALOGPROP_H_
#define __DIALOGPROP_H_

#include "resource.h"       // main symbols
#include <atlhost.h>
#include <atlctl.h>
#include "commctrl.h"
#include "PanelMenuProp.h"
#include "PanelInternetOptions.h"
#include "CPanelUserConfig.h"
// main register key - HKEY_LOCAL_MACHINE


	#define CX_ICON  16 
	#define CY_ICON  16 
	#define NUM_ICONS 10 



/////////////////////////////////////////////////////////////////////////////
// CDialogProp
class CDialogProp : 
	public CAxDialogImpl<CDialogProp>
{
public:
	CDialogProp();

	~CDialogProp();


	enum { IDD = IDD_DIALOGPROP };

BEGIN_MSG_MAP(CDialogProp)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	
MESSAGE_HANDLER(WM_ACTIVATE, OnActivate)
MESSAGE_HANDLER(WM_CLOSE, OnClose)
COMMAND_HANDLER(IDOK, BN_CLICKED, OnOK)
NOTIFY_HANDLER(IDC_TAB_MAIN, TCN_SELCHANGE, OnSelchangeTab_main)
MESSAGE_HANDLER(WM_MOVE, OnMove)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
private:
	VOID RepositionActivePanel();
	VOID SetPanel(DWORD nPanel);
	VOID AddIconsToImageList(DWORD IDI_icon);
	VOID SaveParameters(VOID);
	HIMAGELIST hImageList;
	LRESULT OnSelchangeTab_main(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
	CPanelMenuProp m_PanelMenuProp;
	CPanelInternetOptions m_PanelInternetOptions;
	CCPanelUserConfig m_CPanelUserConfig;
    HWND mChieldWnd[10];
	DWORD LenmChieldWnd;
	DWORD ActivePanel;
	LRESULT OnMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

};

#endif //__DIALOGPROP_H_
