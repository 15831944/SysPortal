// DialogProp.cpp : Implementation of CDialogProp
#include "stdafx.h"
#include "DialogProp.h"
#include "Downloaddata.h"
#include "RegisterSave.h"
#include "MSystemConfig.h"
#include "commctrl.h"
#include "MServerComponent.h"


extern CMServerComponent *_MServerComponent;

/////////////////////////////////////////////////////////////////////////////
// CDialogProp

//------
void GetUserDomain(char *DomainName,char *AccountName)

{ 
     HANDLE hProcess, hAccessToken;
       UCHAR InfoBuffer[1000],szAccountName[200], szDomainName[200];
       PTOKEN_USER pTokenUser = (PTOKEN_USER)InfoBuffer;
       DWORD dwInfoBufferSize,dwAccountSize = 200, dwDomainSize = 200;
       SID_NAME_USE snu;

       hProcess = GetCurrentProcess();

       OpenProcessToken(hProcess,TOKEN_READ,&hAccessToken);

       GetTokenInformation(hAccessToken,TokenUser,InfoBuffer,
            1000, &dwInfoBufferSize);

       LookupAccountSid(NULL, pTokenUser->User.Sid, (char *)szAccountName,
            &dwAccountSize,(char *)szDomainName, &dwDomainSize, &snu);

	   strcpy(DomainName,(char *)szDomainName);
	   strcpy(AccountName,(char *)szAccountName);
} 
//------



LRESULT CDialogProp::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
    HICON hIcon = ::LoadIcon(_Module.GetModuleInstance(), MAKEINTRESOURCE(IDI_HOTINTERNET));
	this->SetIcon(hIcon);
//	IDI_HOTINTERNET

// ----- init page -----

 ActivePanel = -1;
 m_PanelMenuProp.Create(m_hWnd);
 LenmChieldWnd = 0;
 mChieldWnd[LenmChieldWnd]=m_PanelMenuProp.m_hWnd;

 m_PanelInternetOptions.Create(m_hWnd);
 LenmChieldWnd = 1;
 mChieldWnd[LenmChieldWnd]=m_PanelInternetOptions.m_hWnd;


 m_CPanelUserConfig.Create(m_hWnd);
 LenmChieldWnd = 2;
 mChieldWnd[LenmChieldWnd]=m_CPanelUserConfig.m_hWnd;


 

 // ------------

 TabCtrl_SetImageList(
     GetDlgItem(IDC_TAB_MAIN), 		
     hImageList		
);

TCITEM tie; 

    tie.mask = TCIF_TEXT | TCIF_IMAGE; 
    tie.iImage = 0; 
    tie.pszText = "Menu"; 
 
TabCtrl_InsertItem(
    GetDlgItem(IDC_TAB_MAIN), 		
    1, 		
    &tie);		


//----------------


    tie.mask = TCIF_TEXT | TCIF_IMAGE; 
    tie.iImage = 1; 
    tie.pszText = "Internet"; 
 
TabCtrl_InsertItem(
    GetDlgItem(IDC_TAB_MAIN), 		
    2, 		
    &tie);		




//----------------


    tie.mask = TCIF_TEXT | TCIF_IMAGE; 
    tie.iImage = 2; 
    tie.pszText = "User"; 
 
TabCtrl_InsertItem(
    GetDlgItem(IDC_TAB_MAIN), 		
    2, 		
    &tie);		

    tie.mask = TCIF_TEXT | TCIF_IMAGE; 
    tie.iImage = 3; 
    tie.pszText = "Profile"; 
 
TabCtrl_InsertItem(
    GetDlgItem(IDC_TAB_MAIN), 		
    3, 		
    &tie);		





    SetPanel(0);

		return 1;  // Let the system set the focus
	}

extern CMSystemConfig *_MSystemConfig;


	LRESULT CDialogProp::OnSelchangeTab_main(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
	{
		int nTab  = TabCtrl_GetCurSel(GetDlgItem(IDC_TAB_MAIN));
    
        SetPanel(nTab);
		return 0;
	}



LRESULT CDialogProp::OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
        m_PanelInternetOptions.SavePatameters();
		m_PanelMenuProp.SaveParameters();
		m_CPanelUserConfig.SaveParameters();
  	   _MSystemConfig->Load();
		EndDialog(wID);

		return 0;
	}





LRESULT CDialogProp::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{

			EndDialog(0);
		return 0;
	}






	CDialogProp::CDialogProp()
	{
		
        hImageList = ImageList_Create(CX_ICON, CY_ICON, ILC_MASK, NUM_ICONS, 0); 
		AddIconsToImageList(IDI_MENU_OPTIONS);
		AddIconsToImageList(IDI_INTERNET_OPTIONS);
		AddIconsToImageList(IDI_USER_OPTIONS);
		AddIconsToImageList(IDI_FOLDER);

	}


	CDialogProp::~CDialogProp()
	{
		   		ImageList_Destroy(hImageList);
	}



LRESULT CDialogProp::OnMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		RepositionActivePanel();
		// TODO : Add Code for message handler. Call DefWindowProc if necessary.
		return 0;
	}


LRESULT CDialogProp::OnActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		if (wParam == WA_INACTIVE ){

//			EndDialog(0);
		}
		return 0;
	}








LRESULT CDialogProp::OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}


extern HANDLE threadDD;
extern DWORD threadID;
   VOID ThreadFunc(LPVOID);

VOID CDialogProp::SaveParameters(VOID)
{
}

VOID CDialogProp::AddIconsToImageList(DWORD IDI_icon)
{
    HICON hicon;
    hicon = LoadIcon(_Module.GetModuleInstance(), MAKEINTRESOURCE(IDI_icon)); 
	ImageList_AddIcon(hImageList, hicon); 
 
}

VOID CDialogProp::SetPanel(DWORD nPanel)
{
	if (ActivePanel >= 0 ) { 
		::ShowWindow(mChieldWnd[ActivePanel],SW_HIDE);
	}
	ActivePanel = nPanel;
	RepositionActivePanel();
    ::ShowWindow(mChieldWnd[ActivePanel],SW_SHOW);
  
}

VOID CDialogProp::RepositionActivePanel()
{
 		RECT RectTab;
		RECT Rect;
		RECT RectL;



TabCtrl_GetItemRect(
    GetDlgItem(IDC_TAB_MAIN), 		
    0, 		
    &RectL		
);		



	if (ActivePanel >= 0 ) { 
		::GetWindowRect(
             this->m_hWnd,      // handle to window
             &Rect   // window coordinates
        );


		::GetWindowRect(
             GetDlgItem(IDC_TAB_MAIN),      // handle to window
             &RectTab   // window coordinates
        );




		::MoveWindow(
        mChieldWnd[ActivePanel],      // handle to window
        RectTab.left+::GetSystemMetrics(SM_CXBORDER),          // horizontal position
        RectTab.top+::GetSystemMetrics(SM_CYBORDER),          // vertical position
        RectTab.right-RectTab.left-::GetSystemMetrics(SM_CXBORDER)*2,     // width
        RectTab.bottom-RectTab.top-::GetSystemMetrics(SM_CYBORDER)*4 -
		(RectL.bottom-RectL.top),    // height
        true   // repaint option
);		
			}

}
