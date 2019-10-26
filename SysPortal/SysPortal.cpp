// sysportal.cpp : Implementation of WinMain


#define OEMRESOURCE
#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include <WindowsX.h>
#include "SysPortal.h"
#include "MServerComponent.h"
#include "DownloadData.h"
#include "MSystemConfig.h"
#include "STRUCTMENU.H"
#include "RegisterSave.h"

#include "SysPortal_i.c"
#define UM_DISPRESICONNOTIFY     (WM_USER + 100)

const DWORD dwTimeOut = 5000; // time for EXE to be idle before shutting down
const DWORD dwPause = 1000; // time to wait for threads to finish up

CMServerComponent *_MServerComponent;
CMSystemConfig *_MSystemConfig;

///////////////////////////////////////////////////////////////////////////////


// The normal HANDLE_MSG macro in WINDOWSX.H does not work properly for dialog
// boxes because DlgProc's return a BOOL instead of an LRESULT (like
// WndProcs). This adgHANDLE_DLGMSG macro corrects the problem:
#define adgHANDLE_DLGMSG(hwnd, message, fn)                          \
   case (message): return (SetDlgMsgResult(hwnd, uMsg,               \
      HANDLE_##message((hwnd), (wParam), (lParam), (fn))))


///////////////////////////////////////////////////////////////////////////////


// The name of our application.
static TCHAR g_szAppName[] = __TEXT("SysPortal Internet Connecter");



///////////////////////////////////////////////////////////////////////////////


BOOL DispRes_OnInitDialog (HWND hwnd, HWND hwndFocus, LPARAM lParam) {

   // Add the notification icon to the taskbar
   NOTIFYICONDATA nid;
   nid.cbSize = sizeof(nid);
   nid.hWnd = hwnd;        
   nid.uID = IDI_DISPRES;   
   nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
   nid.uCallbackMessage = UM_DISPRESICONNOTIFY;
   nid.hIcon = LoadIcon(_Module.GetModuleInstance(), MAKEINTRESOURCE(IDI_DISPRES));
   lstrcpyn(nid.szTip, g_szAppName, sizeof(nid.szTip) / sizeof(nid.szTip[0]));
   Shell_NotifyIcon(NIM_ADD, &nid);

   // Set an icon with our window
   SendMessage(hwnd, WM_SETICON, (WPARAM) TRUE, (LPARAM) nid.hIcon);

   return(TRUE);
}


///////////////////////////////////////////////////////////////////////////////


void DispRes_OnDestroy (HWND hwnd) {

   // Remove the notification icon from the taskbar
   NOTIFYICONDATA nid;
	nid.cbSize = sizeof(nid);
	nid.hWnd = hwnd;
	nid.uID = IDI_DISPRES;
	Shell_NotifyIcon(NIM_DELETE, &nid);
}






// A mouse message occured over our notification icon.
void DispRes_OnIconNotify (HWND hwnd, UINT uID, UINT uMsg) {

   DWORD dwModeNum = (DWORD) -1; // # of DEVMODEs
   DWORD dwMenuIndex = 0;  // Index into menu where item should be inserted
   HMENU hmenuMain = NULL;
   HMENU hmenuContext = NULL;


   HMENU ghMenu = NULL;
   BOOL startVal=FALSE;


  switch (uMsg) {
	  
 
      case WM_LBUTTONUP:  // The menu was cancelled
		   hmenuMain = LoadMenu(_Module.GetModuleInstance(), 
		      MAKEINTRESOURCE(IDR_LBUTTON));
		   hmenuContext = GetSubMenu(hmenuMain, 0);
		   _Module.hMenuSub = new 	SUBMENU[3000];
	       _Module.MenuJob = new MENUJOB[3000];
		  _MServerComponent->CreateMenuList(hmenuMain,hmenuContext);
		  startVal=TRUE;
		  break;
      case WM_RBUTTONUP:
		  {
		   hmenuMain = LoadMenu(_Module.GetModuleInstance(), 
		      MAKEINTRESOURCE(IDR_RBUTTON));
		   hmenuContext = GetSubMenu(hmenuMain, 0);
		  _MServerComponent->CreateMenuListRBotton(hmenuMain,hmenuContext);
          
		  break;
		  }
      default:
          return;
  }		  


	_Module.CheckMenuHwnd = hwnd;
	SetForegroundWindow(hwnd);	

   // Display the context menu near the mouse cursor
   POINT pt;
   GetCursorPos(&pt);
   UINT uMenuID = TrackPopupMenu(hmenuContext, 
      TPM_BOTTOMALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON | TPM_RETURNCMD,
      pt.x, pt.y, 0, hwnd, NULL);

   char Job[512];
   
  if (startVal){
    _MServerComponent->GetJobString(uMenuID,Job);
    _MServerComponent->ClearMenu();
	   delete[] _Module.hMenuSub;
	   delete[] _Module.MenuJob;
  }


   DestroyMenu(hmenuContext);
   DestroyMenu(hmenuMain);
   

	PostMessage(hwnd, WM_NULL, 0, 0);	

   switch (uMenuID) {
      case 0:  // The menu was cancelled
         break;

      case ID_PROPERTIES:
		  _MServerComponent->ShowPropertiesWindow();
		  break;
      case ID_ABOUT:
         RECT rc;
         GetWindowRect(hwnd, &rc);
         SetWindowPos(hwnd, NULL, 
            (GetSystemMetrics(SM_CXSCREEN) - (rc.right - rc.left)) / 2,
            (GetSystemMetrics(SM_CYSCREEN) - (rc.bottom - rc.top)) / 2,
            0, 0, SWP_NOZORDER | SWP_NOSIZE);

         ShowWindow(hwnd, SW_SHOW);
         break;

      case ID_EXIT:
		    if (_MServerComponent->AskExit()== TRUE){
              PostQuitMessage(1);
			}
         break;

      default:



		  if (startVal){


       //  "[InternetShortcut]"


			int k;
 		    FILE *stream;
			char line[500];
			k = strlen(Job);
			if ( k > 4 ) {
			if (strcmp(&Job[k-4],".url") == 0 ){

                if( (stream = fopen( Job, "r" )) != NULL )
				{
				   fgets( line, 550, stream );
				   while (!feof( stream )){
					   if (strlen(line)>18){line[18]=0;}
					   if (strcmp(line,"[InternetShortcut]") == 0 ){
				           fgets( line, 550, stream );
						   strcpy(Job,&line[4]);
						   Job[strlen(Job)-1]=0;
						   break;
					   }
				      fgets( line, 550, stream );
                      if (ferror( stream )){
						break;
					  }
				   }
                   fclose( stream );
				}


			}
			}


			char cmdRun[500];


        char s_cszDebugKey[255];
   		HKEY hkeyRun;
		DWORD dwType;
		const char s_ValueName[] = _T("Path");
		unsigned long LenRead;
		LenRead = 200;


  BOOL noExe = TRUE;
  CRegisterSave Reg;
		char BufR[50];
  Reg.UserKeyStore("IExplorer",BufR,50,CRegisterSave::READ);



  // -------- Internet Explorer ------

  if (strcmp(BufR,_T("true"))== 0 ) {
        strcpy((char *)s_cszDebugKey,_T("SOFTWARE\\Microsoft\\IE Setup\\SETUP"));
		RegOpenKeyEx(HKEY_LOCAL_MACHINE,s_cszDebugKey,0,KEY_READ,&hkeyRun);
		RegQueryValueEx(hkeyRun,s_ValueName,NULL,&dwType,(unsigned char *)cmdRun,&LenRead);
		RegCloseKey(hkeyRun);
		strcat(cmdRun,"\\iexplore.exe ");
     ShellExecute(NULL, "open", cmdRun, Job, NULL, SW_SHOWNORMAL);
     noExe = FALSE;	 


/*      IEchannel = DDEInitiate("iexplore", "www_getwindowinfo")
      Info = DDERequest(IEchannel, "dogetwindowinfo")
      DDETerminateAll()
*/   

  } 


//  --------- netscape communicator ------


  Reg.UserKeyStore("Netscape",BufR,50,CRegisterSave::READ);
  if (strcmp(BufR,_T("true"))== 0 ) {
     noExe = FALSE;	 

//----- netscape -----
      // Attempt to open the file exclusively.
       char s_csz1DebugKey[255];
		char psz_Buf[255];
		unsigned long LenRead1 = 250;
		psz_Buf[0] = 0;
		strcpy(s_csz1DebugKey,"SOFTWARE\\Netscape\\Netscape Navigator");
		char *s_1ValueName= "CurrentVersion";

	    RegOpenKeyEx(HKEY_LOCAL_MACHINE,s_csz1DebugKey,0,KEY_READ,&hkeyRun);
		LONG ret = RegQueryValueEx(hkeyRun,s_1ValueName,NULL,&dwType,(unsigned char *)psz_Buf,&LenRead1);
        RegCloseKey(hkeyRun);
		if (ERROR_SUCCESS != ret){
			return;
		}

		strcat(s_csz1DebugKey,"\\");
		strcat(s_csz1DebugKey,psz_Buf);
		strcat(s_csz1DebugKey,"\\Main");

		char *s_V = "Install Directory";
		LenRead1 = 250;
		psz_Buf[0] = 0;
		RegOpenKeyEx(HKEY_LOCAL_MACHINE,s_csz1DebugKey,0,KEY_READ,&hkeyRun);
		ret = RegQueryValueEx(hkeyRun,s_V,NULL,&dwType,(unsigned char *)psz_Buf,&LenRead1);
        RegCloseKey(hkeyRun);

		if (ERROR_SUCCESS != ret){
			return;
		}

		
	  strcpy(cmdRun,psz_Buf);
	  strcat(cmdRun,"\\program\\netscape.exe");
     ShellExecute(NULL, "open", cmdRun, Job, NULL, SW_SHOWNORMAL);

  }



  Reg.UserKeyStore("Default browser",BufR,50,CRegisterSave::READ);
  if (strcmp(BufR,_T("true"))== 0 ) {
     ShellExecute(NULL, "open", Job, NULL, NULL, SW_SHOWNORMAL);
     noExe = FALSE;	 
  }


  if (noExe == TRUE ) {
     ShellExecute(NULL, "open", Job, NULL, NULL, SW_SHOWNORMAL);
     noExe = FALSE;	 
  }

 
  






			  
		  }



         break;
   }         
   
}


///////////////////////////////////////////////////////////////////////////////
LRESULT  DispRes_OnActivate (HWND hwnd, int id, HWND hwndCtl, UINT codeNotify ){
		if (hwndCtl == WA_INACTIVE ){
			::ShowWindow(hwnd, SW_HIDE);
		}
		return 0;
}

void DispRes_OnCommand (HWND hwnd, int id, HWND hwndCtl, UINT codeNotify) {

   switch (id) {
      case IDOK:
      case IDCANCEL:
         ShowWindow(hwnd, SW_HIDE);
         break;
   }
}




HFONT GetAFontA(int fnFont) 
{ 
    static LOGFONT lf;  // structure for font information  
 
 
    GetObject(GetStockObject(SYSTEM_FONT), sizeof(LOGFONT), 
        &lf); 
 
 
    if (fnFont == 1) lf.lfWeight = FW_BOLD; 
    
 
    return CreateFont(lf.lfHeight, lf.lfWidth, 
        lf.lfEscapement, lf.lfOrientation, lf.lfWeight, 
        lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet, 
        lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality, 
        lf.lfPitchAndFamily, lf.lfFaceName); 

}

///////////////////////////////////////////////////////////////////////////////

VOID ShowMenuItem_WM_MEASUREITEM(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{ 
 
    ITEMMENU *pmyitem;      // pointer to item's font and string        
//    static HMENU hmenu;             // handle to main menu            

   

    LPMEASUREITEMSTRUCT lpmis;  // pointer to item of data             
      
    HDC hdc;                    // handle to screen DC                
    SIZE size;                  // menu-item text extents             
                
              
 
    HFONT hfontOld;             // handle to old font                 
    BOOL fSelected = FALSE;     // menu-item selection flag      
    BITMAP  bm;
	HBITMAP hBmp;
	HFONT hFont;


 
            hdc = GetDC(hwnd); 
            lpmis = (LPMEASUREITEMSTRUCT) lParam; 
            pmyitem = (ITEMMENU *) lpmis->itemData; 

			hBmp = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(pmyitem->WhBitmap));
		    GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bm);
			DeleteObject(hBmp);

			hFont = GetAFontA(0);
            hfontOld = (HFONT)SelectObject(hdc,hFont ); 
 
            GetTextExtentPoint32(hdc, pmyitem->psz_ItemText, 
                lstrlen(pmyitem->psz_ItemText), &size); 
            lpmis->itemWidth = size.cx + bm.bmWidth ;
			if (size.cy < bm.bmHeight ){
				lpmis->itemHeight = bm.bmHeight ;
			}else {
            lpmis->itemHeight = size.cy; 
			}
 
 
            SelectObject(hdc, hfontOld); 
            ReleaseDC(hwnd, hdc); 
			DeleteObject(hFont);
 
} 


void DrawTransparentBitmap(HDC hdc, HBITMAP hBitmap, long xStart,
                           long yStart, COLORREF cTransparentColor);

////--------------
///////////////////////////////////////////////////////////////////////////////

VOID ShowMenuItem_WM_DRAWITEM(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{ 
 
    ITEMMENU *pmyitem;      // pointer to item's font and string        
//    static HMENU hmenu;             // handle to main menu            
    static COLORREF crSelText;  // text color of selected item        
    static COLORREF crSelBkgnd; // background color of selected item  
    COLORREF crText;            // text color of unselected item      
    COLORREF crBkgnd;           // background color unselected item   
          
    LPDRAWITEMSTRUCT lpdis;     // pointer to item drawing data        
    HDC hdc;                    // handle to screen DC                
    SIZE size;                  // menu-item text extents             
    WORD wCheckX;               // check-mark width                   
    int nTextX;                 // width of menu item                 
    int nTextY;                 // height of menu item 
    HFONT hfontOld;             // handle to old font                 
    BOOL fSelected = FALSE;     // menu-item selection flag      
    BITMAP  bm;
	HBITMAP hBmp;
	HFONT hFont;
	DWORD ItemHeight;


 

			


		    crSelText = GetSysColor(COLOR_HIGHLIGHTTEXT); 
		    crSelBkgnd = GetSysColor(COLOR_HIGHLIGHT); 


 
            lpdis = (LPDRAWITEMSTRUCT) lParam; 
            pmyitem = (ITEMMENU *) lpdis->itemData; 


			if ((pmyitem->WhBitmap == IDB_ITEMDEFAULT)&&(lpdis->itemState & ODS_SELECTED)){
			   hBmp = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_ITEMDEFAULT_N));
			} else {
			     if ((pmyitem->WhBitmap == IDB_NEXT)&&(lpdis->itemState & ODS_SELECTED)){
			         hBmp = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_NEXT_S));
				 }else {
			         hBmp = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(pmyitem->WhBitmap));
				 }
			}
		    GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bm);
			
 
            if (lpdis->itemState & ODS_SELECTED) 
            { 
                crText = SetTextColor(lpdis->hDC, crSelText); 
                crBkgnd = SetBkColor(lpdis->hDC, crSelBkgnd); 
                fSelected = TRUE; 
            } 
 
            wCheckX = GetSystemMetrics(SM_CXMENUCHECK); 

            wCheckX = 0; 
            nTextX = wCheckX ;
			nTextX = nTextX + lpdis->rcItem.left+bm.bmWidth; 
            nTextY = lpdis->rcItem.top; 
 
			if ( pmyitem->Whfont == 1 ) {
 			  hFont = GetAFontA(0);
              hfontOld = (HFONT)SelectObject(lpdis->hDC,hFont ); 
			}

			 
            hdc = GetDC(hwnd); 
			
           GetTextExtentPoint32(hdc, pmyitem->psz_ItemText, 
                lstrlen(pmyitem->psz_ItemText), &size); 
			if (size.cy < bm.bmHeight ){
				nTextY = nTextY + (bm.bmHeight-size.cy)/2 ;
			}			
		
			ItemHeight = bm.bmHeight;
			
			ExtTextOut(lpdis->hDC, nTextX, nTextY, ETO_OPAQUE, 
                &lpdis->rcItem, pmyitem->psz_ItemText, 
                lstrlen(pmyitem->psz_ItemText), NULL); 

			if ( pmyitem->Whfont == 1 ) {
            SelectObject(lpdis->hDC, hfontOld); 
            }
 
            if (fSelected) 
            { 
               SetTextColor(lpdis->hDC, crText); 
               SetBkColor(lpdis->hDC, crBkgnd); 
            } 

			POINT pS;
            nTextY = lpdis->rcItem.top; 
			pS.x = wCheckX/2 + lpdis->rcItem.left;
			pS.x = lpdis->rcItem.left;
			pS.y = nTextY;

            DrawTransparentBitmap(lpdis->hDC,hBmp,pS.x,pS.y,RGB(0,128,0));
			DeleteObject(hBmp);



			if ( pmyitem->Whfont == 1 ) {
			if (fSelected){
			    hBmp = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_SELECTED));
		        GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bm);
            pS.y = nTextY+(ItemHeight - bm.bmHeight) / 2;
                DrawTransparentBitmap(lpdis->hDC,hBmp,pS.x,pS.y,RGB(0,128,0));
			    DeleteObject(hBmp);
			} else {
			    hBmp = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_SELECTING));
		        GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bm);
                pS.y = nTextY+(ItemHeight - bm.bmHeight) / 2;
              DrawTransparentBitmap(lpdis->hDC,hBmp,pS.x,pS.y,RGB(0,128,0));
			    DeleteObject(hBmp);
			}
			  DeleteObject(hFont);
			}

            ReleaseDC(hwnd, hdc); 
			return;
} 




////--------------



BOOL WINAPI DispRes_WndProc (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
   switch (uMsg) {



      case WM_DRAWITEM:
		  if (_Module.CheckMenuHwnd == hwnd ){ 
            ShowMenuItem_WM_DRAWITEM(hwnd, uMsg, wParam,lParam); 
		  }
		  return(TRUE);
        break;
      case WM_MEASUREITEM:
		  if (_Module.CheckMenuHwnd == hwnd ){ 
            ShowMenuItem_WM_MEASUREITEM(hwnd, uMsg, wParam,lParam); 
		  }
		  return(TRUE);
      case UM_DISPRESICONNOTIFY:
         // A mouse message occured over our notification icon
         DispRes_OnIconNotify(hwnd, (UINT) wParam, (UINT) lParam);
         return(TRUE);
      adgHANDLE_DLGMSG(hwnd, WM_INITDIALOG, DispRes_OnInitDialog);
      adgHANDLE_DLGMSG(hwnd, WM_DESTROY,    DispRes_OnDestroy);
      adgHANDLE_DLGMSG(hwnd, WM_COMMAND,    DispRes_OnCommand);
      adgHANDLE_DLGMSG(hwnd, WM_ACTIVATE,    DispRes_OnActivate);
      break;

//	  default: 
//            return DefWindowProc(hwnd, uMsg, wParam, lParam); 
    
   }

   return(FALSE);
}


///////////////////////////////////////////////////////////////////////////////


// Variables shared across all instances of our application which ensure
// that only one instance of this application  will run at a given time.
#pragma data_seg("Shared")
static LONG g_lInstanceCount = -1;
#pragma data_seg()

#pragma data_seg(".drectve")
static char szShared[] = "-section:Shared,rws";
#pragma data_seg()


///////////////////////////////////////////////////////////////////////////////





// Passed to CreateThread to monitor the shutdown event
static DWORD WINAPI MonitorProc(void* pv)
{
    CExeModule* p = (CExeModule*)pv;
    p->MonitorShutdown();
    return 0;
}

LONG CExeModule::Unlock()
{
    LONG l = CComModule::Unlock();
    if (l == 0)
    {
        bActivity = true;
        SetEvent(hEventShutdown); // tell monitor that we transitioned to zero
    }
    return l;
}

//Monitors the shutdown event
void CExeModule::MonitorShutdown()
{
    while (1)
    {
        WaitForSingleObject(hEventShutdown, INFINITE);
        DWORD dwWait=0;
        do
        {
            bActivity = false;
            dwWait = WaitForSingleObject(hEventShutdown, dwTimeOut);
        } while (dwWait == WAIT_OBJECT_0);
        // timed out
        if (!bActivity && m_nLockCnt == 0) // if no activity let's really bail
        {
#if _WIN32_WINNT >= 0x0400 & defined(_ATL_FREE_THREADED)
            CoSuspendClassObjects();
            if (!bActivity && m_nLockCnt == 0)
#endif
                break;
        }
    }
    CloseHandle(hEventShutdown);
    PostThreadMessage(dwThreadID, WM_QUIT, 0, 0);
}

bool CExeModule::StartMonitor()
{
    hEventShutdown = CreateEvent(NULL, false, false, NULL);
    if (hEventShutdown == NULL)
        return false;
    DWORD dwThreadID;
    HANDLE h = CreateThread(NULL, 0, MonitorProc, this, 0, &dwThreadID);
    return (h != NULL);
}

CExeModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
END_OBJECT_MAP()


LPCTSTR FindOneOf(LPCTSTR p1, LPCTSTR p2)
{
    while (p1 != NULL && *p1 != NULL)
    {
        LPCTSTR p = p2;
        while (p != NULL && *p != NULL)
        {
            if (*p1 == *p)
                return CharNext(p1);
            p = CharNext(p);
        }
        p1 = CharNext(p1);
    }
    return NULL;
}

/////////////////////////////////////////////////////////////////////////////
//



VOID ThreadFunc(LPVOID);

DWORD threadID;

HANDLE threadDD;


   VOID ThreadFunc(LPVOID)
   { CDownloadData Download;
	   while(TRUE){
//		   Download.GetURL_ASP("us.yimg.com","//images//new2.gif");
			Sleep(90000);
	   }
   }



extern "C" int WINAPI _tWinMain(HINSTANCE hInstance, 
    HINSTANCE /*hPrevInstance*/, LPTSTR lpCmdLine, int /*nShowCmd*/)
{


   // Only allow one instance of our application to execute
   if (InterlockedIncrement(&g_lInstanceCount) > 0) {

      InterlockedDecrement(&g_lInstanceCount);
      MessageBox(NULL, __TEXT("SysPortal Internet Connecter is already running"), 
         g_szAppName, MB_ICONINFORMATION | MB_OK);

   } else {

    lpCmdLine = GetCommandLine(); //this line necessary for _ATL_MIN_CRT

#if _WIN32_WINNT >= 0x0400 & defined(_ATL_FREE_THREADED)
    HRESULT hRes = CoInitializeEx(NULL, COINIT_MULTITHREADED);
#else
    HRESULT hRes = CoInitialize(NULL);
#endif
    _ASSERTE(SUCCEEDED(hRes));
    _Module.Init(ObjectMap, hInstance, &LIBID_SYSPORTALLib);
    _Module.dwThreadID = GetCurrentThreadId();
    TCHAR szTokens[] = _T("-/");

    int nRet = 0;
    BOOL bRun = TRUE;
    LPCTSTR lpszToken = FindOneOf(lpCmdLine, szTokens);
            _Module.UpdateRegistryFromResource(IDR_SysPortal, TRUE);
            nRet = _Module.RegisterServer(TRUE);

    while (lpszToken != NULL)
    {
        if (lstrcmpi(lpszToken, _T("UnregServer"))==0)
        {
            _Module.UpdateRegistryFromResource(IDR_SysPortal, FALSE);
            nRet = _Module.UnregisterServer(TRUE);
            bRun = FALSE;
            break;
        }
        if (lstrcmpi(lpszToken, _T("RegServer"))==0)
        {
            _Module.UpdateRegistryFromResource(IDR_SysPortal, TRUE);
            nRet = _Module.RegisterServer(TRUE);
            bRun = FALSE;
            break;
        }
        lpszToken = FindOneOf(lpszToken, szTokens);
    }

    if (bRun)
    {
        _Module.StartMonitor();
#if _WIN32_WINNT >= 0x0400 & defined(_ATL_FREE_THREADED)
        hRes = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, 
            REGCLS_MULTIPLEUSE | REGCLS_SUSPENDED);
        _ASSERTE(SUCCEEDED(hRes));
        hRes = CoResumeClassObjects();
#else
        hRes = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, 
            REGCLS_MULTIPLEUSE);
#endif
        _ASSERTE(SUCCEEDED(hRes));

        MSG msg;
//

    _MServerComponent = new CMServerComponent;
    _MSystemConfig = new CMSystemConfig ;


      // Create our modeless dialog About dialog box.
      HWND hwnd = CreateDialog(_Module.GetModuleInstance(), MAKEINTRESOURCE(IDD_ABOUT), 
         NULL, DispRes_WndProc);



     threadDD = NULL;
	 _MSystemConfig->Load();

     if (_MSystemConfig->LockLine == TRUE ) {   
        threadDD = CreateThread(0, 0,(LPTHREAD_START_ROUTINE) ThreadFunc,
                    0, 0, &threadID);
	 }
     

	  _MServerComponent->InitServer();
      // Keep our process running


      while (GetMessage(&msg, hwnd, 0, 0)) {
         if (!IsDialogMessage(hwnd, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
         }
      }



	  if (threadDD != NULL ){
          TerminateThread(
            threadDD,    // handle to the thread
           0 );
		  threadDD = NULL;
	  }



	  _MServerComponent->ExitServer();
      // Destroy the dialog box (which removes the notification icon)
      DestroyWindow(hwnd);

//

        _Module.RevokeClassObjects();
        Sleep(dwPause); //wait for any threads to finish
    }

    _Module.Term();
            _Module.UpdateRegistryFromResource(IDR_SysPortal, FALSE);
            nRet = _Module.UnregisterServer(TRUE);


	delete _MServerComponent;
    delete _MSystemConfig;


    CoUninitialize();
   }
    return (0);
}
