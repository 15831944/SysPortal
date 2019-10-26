// MServerComponent.h: interface for the CMServerComponent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSERVERCOMPONENT_H__1E35492E_DB33_11D3_AE8B_0040951C56A9__INCLUDED_)
#define AFX_MSERVERCOMPONENT_H__1E35492E_DB33_11D3_AE8B_0040951C56A9__INCLUDED_

#include <atlcom.h>
#include <urlmon.h>
#include "resource.h"
#include "structMenu.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



  typedef struct _REDIRECTMENU
    { 
        char Sourse[255]; 
	    char Distanation[255];
    }REDIRECTMENU;           


class CMServerComponent  
{
public:
	BOOL AskExit();
    void CreateMenuListRBotton(HMENU hmenuMain,HMENU hmenuContext);
	void AddAllBookmarks();
	void AddIntranet(char *NameFolder,WORD Id_Fold=IDB_CHECK);
	void AddLocalMenu();
	char sz_LocalMenu[255];
	void ActiveServerSet(char *psz_ServerName);
	void ActiveServerGet(char *psz_ServerName);
	char sz_CmdLine[255];
	void ExitServer();
	void InitServer();
	void ShowMenuItem(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) ;
	void GetJobString(DWORD id,char *pJob);
	void ClearMenu();
	void InsertMunuItemN(char *pParentName,char *sz_TextMenu,char *URLText,WORD Image_ID=IDB_ITEMDEFAULT);
	void InsertMenuTop(HMENU hMenu);
    void InsertSubMenuN(char *psz_Parent,char *psz_Name,char *pszText,WORD Image_ID = IDB_CHECK);
    void InsertSubMenu(char *psz_Parent,char *psz_Name,char *pszText,WORD Image_ID = IDB_CHECK);
	void CreateMenuList(HMENU hmenuMain,HMENU hmenuContext);
	void ShowPropertiesWindow();
	CMServerComponent();
	virtual ~CMServerComponent();
	void *pDialogProp;
	void *pTreeEditor;
private:

	long GetCountMenuInScreen();
	void InsertSubMenuFromFile(char *pTop,char *pFileName);

	void DownLoadBookMark(char *ServerName,char *NameFile,char *NameMenu);
	void AddSubMenuFromBookmark(char *psz_NameMenu,char *Buf,long Count);
	void AddNetscapeFoforites();
	void AddExplorerFovorites();
    void DrawHBitmap(HDC hDC, LPPOINT lppt, HBITMAP hBitPaint,HBITMAP hBitmapMask = NULL);
	HFONT GetAFont(int fnFont) ;
	HBITMAP hBitmapItemMask;	
	HBITMAP hBitmapMenu;
	DWORD dwNextIDMenu;
	int LenItem;

//	int NextPozSubItem;
	int iLenMenuJob;
	int iLenMenuSub;
	_REDIRECTMENU RedirectMenu[100];
	int LenRedirectMenu;
public:
    void * pCWndExit;


};

#ifndef OBM_LFARROW
#define OBM_LFARROW         32750
#endif


#define CITEMS 3
#define BOLD 1
#define ITALIC 2
#define ULINE 3


#endif // !defined(AFX_MSERVERCOMPONENT_H__1E35492E_DB33_11D3_AE8B_0040951C56A9__INCLUDED_)
