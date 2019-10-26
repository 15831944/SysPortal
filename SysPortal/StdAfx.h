// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__4914A084_DA4A_11D3_9F4B_005004816FFF__INCLUDED_)
#define AFX_STDAFX_H__4914A084_DA4A_11D3_9F4B_005004816FFF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif
#define _ATL_APARTMENT_THREADED

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module

   typedef struct _ITEMMENU
    { 
        WORD Whfont;  // HFONT 
        char psz_ItemText[255]; 
	    WORD WhBitmap;
    } ITEMMENU;             // structure for item font and string  



struct SUBMENU              
{
   HMENU   hMenu;              // Declare member types
   char sMenuName[255];
   char szParentName[255];
//   char szTextMenu[255];
   int NextPozSubItem;
    ITEMMENU *myitem;
   DWORD idMenu;
};



struct MENUJOB
{
	 char URL[500];
     char szParentName[30];
	 DWORD idMenu;
  	 ITEMMENU *myitem;
};




class CExeModule : public CComModule
{
public:
	SUBMENU  *hMenuSub;
    MENUJOB  *MenuJob;
	HWND CheckMenuHwnd;
	LONG Unlock();
	DWORD dwThreadID;
	HANDLE hEventShutdown;
	void MonitorShutdown();
	bool StartMonitor();
	bool bActivity;
};
extern CExeModule _Module;


#include <atlcom.h>
#include <atlwin.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__4914A084_DA4A_11D3_9F4B_005004816FFF__INCLUDED)
