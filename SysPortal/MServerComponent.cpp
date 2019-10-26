// MServerComponent.cpp: implementation of the CMServerComponent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdio.h"
#include "MServerComponent.h"
#include "DialogProp.h"
#include "RegisterSave.h"
#include "MSteck.h"
#include "DownloadData.h"
#include "shlwapi.h"
#include "Exit.h"




//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CMServerComponent::CMServerComponent()
{
pDialogProp = NULL;
pTreeEditor = NULL;
pCWndExit = NULL;
iLenMenuSub = 0;
//hBitmapMenu = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_CHECK));


 hBitmapMenu = LoadBitmap(NULL,MAKEINTRESOURCE(OBM_LFARROW));
 hBitmapItemMask = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_ITEMMASK));
}

CMServerComponent::~CMServerComponent()
{
 DeleteObject(hBitmapMenu);
 DeleteObject(hBitmapItemMask);
}

void CMServerComponent::DrawHBitmap(HDC hDC, LPPOINT lppt, HBITMAP hBitPaint,HBITMAP hBitmapMask)
    {
    HDC     hMemDC1;
    HDC     hMemDC2;
    HBITMAP hBitTemp;
	HBITMAP hBitMask;
    BITMAP  bm;
	BITMAP bmMask;
    long   cx, cy; //For more readbility
	
	if (hBitmapMask == NULL){
	    GetObject(hBitPaint, sizeof(BITMAP), (LPSTR)&bmMask);
         for (long iTemp=0;bmMask.bmWidthBytes>iTemp;iTemp++)
		 {
		 }
	}else {
	    GetObject(hBitmapMask, sizeof(BITMAP), (LPSTR)&bmMask);
	}
	    hBitMask = CreateBitmapIndirect(&bmMask);

    hMemDC1=CreateCompatibleDC(hDC);
    hMemDC2=CreateCompatibleDC(hDC);
    SetMapMode(hMemDC1, GetMapMode(hDC));
    SetMapMode(hMemDC2, GetMapMode(hDC));

    GetObject(hBitPaint, sizeof(BITMAP), (LPSTR)&bm);
    cx=bm.bmWidth;
    cy=bm.bmHeight;

    hBitTemp=CreateCompatibleBitmap(hDC, cx, cy);

    /* Draw the mask */
    SelectObject(hMemDC1, hBitMask);
    SelectObject(hMemDC2, hBitTemp);
    BitBlt(hMemDC2, 0, 0, cx, cy, hDC, lppt->x, lppt->y, SRCCOPY);
    BitBlt(hMemDC2, 0, 0, cx, cy, hMemDC1, 0, 0, SRCAND);

    SelectObject(hMemDC1, hBitPaint);
    SetBkColor(hMemDC2, RGB(0,0,0));
    BitBlt(hMemDC2, 0, 0, cx, cy, hMemDC1, 0, 0, SRCCOPY);//SRCPAINT);


    BitBlt(hDC, lppt->x, lppt->y, cx, cy, hMemDC2, 0, 0, SRCCOPY);

    DeleteDC(hMemDC1);
    DeleteDC(hMemDC2);

    DeleteObject(hBitTemp);
	DeleteObject(hBitMask);
     }

void CMServerComponent::ShowPropertiesWindow()
{
	if (pDialogProp != NULL) {
		((CDialogProp *)pDialogProp)->ShowWindow(SW_HIDE);
		((CDialogProp *)pDialogProp)->ShowWindow(SW_SHOW);
	} else {
       CDialogProp *pD = new CDialogProp;
       pDialogProp = pD;
       pD->DoModal(::GetDesktopWindow());
	   delete pD;
	   pDialogProp = NULL;
	}

}


void CMServerComponent::CreateMenuListRBotton(HMENU hmenuMain,HMENU hmenuContext){
	static ITEMMENU ItemAbout;
	ItemAbout.WhBitmap = IDB_ABOUT;
	strcpy(ItemAbout.psz_ItemText,"About");



	static ITEMMENU ItemConfig;
	ItemConfig.WhBitmap = IDB_CONFIG;
	strcpy(ItemConfig.psz_ItemText,"Configuration");


	static ITEMMENU ItemExit;
	ItemExit.WhBitmap = IDB_CLOSE;
	strcpy(ItemExit.psz_ItemText,"Close");



	static ITEMMENU ItemEdit;
	ItemEdit.WhBitmap = IDB_EDIT_PERSONAL_LINE;
	strcpy(ItemEdit.psz_ItemText,"Edit personal line");


	

    ModifyMenu(hmenuContext, ID_ABOUT, MF_BYCOMMAND | 
                MF_OWNERDRAW, ID_ABOUT, (LPTSTR) &ItemAbout); 


    ModifyMenu(hmenuContext, ID_PROPERTIES, MF_BYCOMMAND | 
                MF_OWNERDRAW, ID_PROPERTIES, (LPTSTR) &ItemConfig); 


    ModifyMenu(hmenuContext, ID_EXIT, MF_BYCOMMAND | 
                MF_OWNERDRAW, ID_EXIT, (LPTSTR) &ItemExit); 





}

void CMServerComponent::CreateMenuList(HMENU hmenuMain,HMENU hmenuContext)
{
	
        WIN32_FIND_DATA FindFileData;
        HANDLE hFind;
		char strMask[255];
		char fileName[MAX_PATH];
		char NameMenu[MAX_PATH];
		BOOL ret= TRUE;

        InsertMenuTop(hmenuContext);
        AddExplorerFovorites();


		GetCurrentDirectory(254,strMask);
		strcat(strMask,"\\*.mnu");
        hFind = FindFirstFile(strMask, &FindFileData);

        if (hFind != INVALID_HANDLE_VALUE) {
			if (FindFileData.cFileName[0]=='.'){
			   ret = FindNextFile(hFind,&FindFileData);
			}
		}

        if (hFind != INVALID_HANDLE_VALUE) {
			if (FindFileData.cFileName[0]=='.'){
			   ret = FindNextFile(hFind,&FindFileData);
			}
		}


        if (hFind != INVALID_HANDLE_VALUE) {
			while (ret){
				strcpy(fileName,FindFileData.cFileName);
				strcpy(NameMenu,FindFileData.cFileName);
				NameMenu[strlen(NameMenu)-4] = 0;
		        InsertSubMenuN("Top",fileName,NameMenu,IDB_FIND);
		        InsertSubMenuFromFile(fileName,fileName);

			   ret = FindNextFile(hFind,&FindFileData);
			}
		}
  
        FindClose(hFind);
  


//		AddNetscapeFoforites();
//		InsertSubMenuN("Top","FIND_LINK","Internet Search system",IDB_FIND);
//		InsertSubMenuFromFile("FIND_LINK","Search.mnu");
//		InsertSubMenuN("Top","PUBLIC_LINK","Public bookmark",IDB_PUBLIC_LINK);
//		InsertSubMenuFromFile("PUBLIC_LINK","PublicBookmark.mnu");
//		InsertSubMenuN("Top","WORKGROUP","Workgroup favorites",IDB_WORKGROUPS);
//		InsertSubMenuFromFile("WORKGROUP","workgroup.mnu");
//		InsertSubMenuN("Top","PERSONAL","Personal line",IDB_PERSONAL);
//		InsertSubMenuFromFile("PERSONAL","personal.mnu");
//		InsertSubMenuN("Top","LIBRARY","Virtual Library",IDB_BOOKS);
//		InsertSubMenuFromFile("LIBRARY","Library.mnu");
		AddAllBookmarks();

		InsertSubMenuN("Top","SysPortalSite","SysPortal Web",IDB_WORKGROUPS);
		InsertMunuItemN("SysPortalSite","About SysPortal","http://members.fortunecity.com/multiwindows/sysportal/index.htm",IDB_HANDICO);
		InsertMunuItemN("SysPortalSite","Help","http://members.fortunecity.com/multiwindows/sysportal/help/index.htm",IDB_COMMENT);
		InsertMunuItemN("SysPortalSite","Download additional menu","http://members.fortunecity.com/multiwindows/sysportal/DownLoadMenu.htm",IDB_INTRANET);

}




void CMServerComponent::InsertSubMenu(char *psz_Parent,char *psz_Name,char *pszTextI,WORD Image_ID)
{
	char pParentName[255];
	strcpy(pParentName,psz_Parent);
	if (strcmp(pParentName,"Top")!=0) {
 int InsertMenuIndex= -1;
 int i;
 int Red= 0;



for ( i=iLenMenuSub;i>=0;i--)
   {
	   if (strcmp(_Module.hMenuSub[i].sMenuName,pParentName) == 0 ){
		   InsertMenuIndex = i;
		   break;
	   }
   }

char NempName[255];
  strcpy(NempName,_Module.hMenuSub[i].myitem->psz_ItemText);

 if ( LenRedirectMenu >= 0){
    for (i = 0; i <= LenRedirectMenu;i++){
		if(strcmp(RedirectMenu[i].Sourse,pParentName)==0){
			strcpy(pParentName,RedirectMenu[i].Distanation);
			Red++;
		}
	}
 }




//

 for ( i=iLenMenuSub;i>=0;i--)
   {
	   if (strcmp(_Module.hMenuSub[i].sMenuName,pParentName) == 0 ){
		   InsertMenuIndex = i;
		   break;
	   }
   }







   if (InsertMenuIndex == -1 ){
	   InsertMenuIndex = 0;
   }


   if (_Module.hMenuSub[InsertMenuIndex].NextPozSubItem > LenItem){
	   LenRedirectMenu++;
	   strcpy(RedirectMenu[LenRedirectMenu].Sourse,pParentName);
	   strcat(pParentName,"_*");
	   pParentName[0]='&';
	   strcpy(RedirectMenu[LenRedirectMenu].Distanation,pParentName);
	    char mess[100];
		sprintf(mess,"%d %s",Red+1,NempName);
	   InsertSubMenuN(RedirectMenu[LenRedirectMenu].Sourse,RedirectMenu[LenRedirectMenu].Distanation,mess,IDB_NEXT);
		   InsertMenuIndex = iLenMenuSub;
   }


}
    InsertSubMenuN(pParentName,psz_Name,pszTextI,Image_ID);
}

void CMServerComponent::InsertSubMenuN(char *psz_Parent,char *psz_Name,char *pszTextI,WORD Image_ID)
{
 char pszText[60];
 int LenMenuName; 
   LenMenuName = strlen(pszTextI);
   if (LenMenuName > 40 ){LenMenuName = 40;}
 strncpy(pszText,pszTextI,LenMenuName);
 pszText[LenMenuName]=0;

 HMENU hmenuContext;
 MENUITEMINFO   mii;
 ZeroMemory(&mii, sizeof(mii));
 int InsertMenuIndex= -1;
 
 //
   for (int i=iLenMenuSub;i>=0;i--)
   {
	   if (strcmp(_Module.hMenuSub[i].sMenuName,psz_Parent) == 0 ){
		   InsertMenuIndex = i;
		   break;
	   }
   }
   if (InsertMenuIndex == -1 ){
	   InsertMenuIndex = 0;
   }
   hmenuContext = _Module.hMenuSub[InsertMenuIndex].hMenu;
   _Module.hMenuSub[InsertMenuIndex].NextPozSubItem++;
 //

 iLenMenuSub++;
 _Module.hMenuSub[iLenMenuSub].hMenu = CreatePopupMenu();

	 ITEMMENU *pMyItem = (ITEMMENU *) LocalAlloc(LMEM_FIXED, 
                sizeof(ITEMMENU)); 

   _Module.hMenuSub[iLenMenuSub].myitem = pMyItem;

   strcpy(_Module.hMenuSub[iLenMenuSub].myitem->psz_ItemText,pszText);
   strcpy(_Module.hMenuSub[iLenMenuSub].szParentName,psz_Name);
   strcpy(_Module.hMenuSub[iLenMenuSub].sMenuName,psz_Name);
   _Module.hMenuSub[iLenMenuSub].NextPozSubItem = 0;


		dwNextIDMenu++;
         mii.cbSize = sizeof(mii);
         mii.fMask = MIIM_ID | MIIM_TYPE | MIIM_STATE | MIIM_SUBMENU;
         mii.wID = IDM_DISPRES + dwNextIDMenu;
         mii.fType = MF_STRING ;
         mii.dwTypeData = _TEXT(pszText);
         mii.fState =  MF_UNCHECKED  ;
		 mii.hSubMenu = _Module.hMenuSub[iLenMenuSub].hMenu;
         InsertMenuItem(   hmenuContext,
                           _Module.hMenuSub[InsertMenuIndex].NextPozSubItem,
                           TRUE,
                           &mii);


            _Module.hMenuSub[iLenMenuSub].myitem->Whfont = 1; 
			_Module.hMenuSub[iLenMenuSub].myitem->WhBitmap = Image_ID;
//			_Module.hMenuSub[iLenMenuSub].myitem.hBitmap = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(Image_ID));



     strcpy(_Module.hMenuSub[iLenMenuSub].myitem->psz_ItemText,pszText) ; 
            ModifyMenu(hmenuContext, IDM_DISPRES + dwNextIDMenu, MF_BYCOMMAND | 
                MF_OWNERDRAW, IDM_DISPRES + dwNextIDMenu, (LPTSTR) pMyItem); 

		 


			
}

void CMServerComponent::InsertMenuTop(HMENU hMenu)
{
  iLenMenuSub = 0;
  LenItem = GetCountMenuInScreen();
  LenRedirectMenu= -1;
  	 ITEMMENU *pMyItem = (ITEMMENU *) LocalAlloc(LMEM_FIXED, 
                sizeof(ITEMMENU)); 
   _Module.hMenuSub[iLenMenuSub].myitem = pMyItem;
   strcpy(_Module.hMenuSub[iLenMenuSub].myitem->psz_ItemText,_TEXT(""));
   strcpy(_Module.hMenuSub[iLenMenuSub].szParentName,_TEXT(""));
   strcpy(_Module.hMenuSub[iLenMenuSub].sMenuName,_TEXT(""));
   _Module.hMenuSub[iLenMenuSub].hMenu = hMenu;
   dwNextIDMenu= 0;
   iLenMenuJob = 0;
   _Module.hMenuSub[0].NextPozSubItem = 0;
}

void CMServerComponent::InsertMunuItemN(char *pNParentName, char *sz_TextMenuI,char *URLText,WORD Image_ID)
{
 char sz_TextMenu[60];
 char pParentName[255];
 strcpy(pParentName,pNParentName);
 int LenMenuName;
   LenMenuName = strlen(sz_TextMenuI);
   if (LenMenuName > 40 ){LenMenuName = 40;}
 strncpy(sz_TextMenu,sz_TextMenuI,LenMenuName);
 sz_TextMenu[LenMenuName]=0;

 HMENU hmenuContext;
 MENUITEMINFO   mii;
 ZeroMemory(&mii, sizeof(mii));
 int InsertMenuIndex= -1;
 
 //

 int i;
 int Red= 0;



for ( i=iLenMenuSub;i>=0;i--)
   {
	   if (strcmp(_Module.hMenuSub[i].sMenuName,pParentName) == 0 ){
		   InsertMenuIndex = i;
		   break;
	   }
   }

char NempName[255];
  strcpy(NempName,_Module.hMenuSub[i].myitem->psz_ItemText);

 if ( LenRedirectMenu >= 0){
    for (i = 0; i <= LenRedirectMenu;i++){
		if(strcmp(RedirectMenu[i].Sourse,pParentName)==0){
			strcpy(pParentName,RedirectMenu[i].Distanation);
			Red++;
		}
	}
 }




//

 for ( i=iLenMenuSub;i>=0;i--)
   {
	   if (strcmp(_Module.hMenuSub[i].sMenuName,pParentName) == 0 ){
		   InsertMenuIndex = i;
		   break;
	   }
   }







   if (InsertMenuIndex == -1 ){
	   InsertMenuIndex = 0;
   }


   if (_Module.hMenuSub[InsertMenuIndex].NextPozSubItem > LenItem){
	   LenRedirectMenu++;
	   strcpy(RedirectMenu[LenRedirectMenu].Sourse,pParentName);
	   strcat(pParentName,"_*");
	   pParentName[0]='&';
	   strcpy(RedirectMenu[LenRedirectMenu].Distanation,pParentName);
	    char mess[100];
		sprintf(mess,"%d %s",Red+1,NempName);
	   InsertSubMenuN(RedirectMenu[LenRedirectMenu].Sourse,RedirectMenu[LenRedirectMenu].Distanation,mess,IDB_NEXT);
		   InsertMenuIndex = iLenMenuSub;
   }


   hmenuContext = _Module.hMenuSub[InsertMenuIndex].hMenu;
   _Module.hMenuSub[InsertMenuIndex].NextPozSubItem++;
			dwNextIDMenu++;
			iLenMenuJob++;
       ZeroMemory(&mii, sizeof(mii));
         mii.cbSize = sizeof(mii);
         mii.fMask = MIIM_ID | MIIM_TYPE | MIIM_STATE;
         mii.wID = IDM_DISPRES + dwNextIDMenu;
         mii.fType = MFT_STRING;
         mii.dwTypeData = TEXT(sz_TextMenu);
         mii.fState = MFS_ENABLED | MFS_UNCHECKED;
         InsertMenuItem(   hmenuContext,
                           _Module.hMenuSub[InsertMenuIndex].NextPozSubItem,
                           TRUE,
                           &mii);
	 strcpy(_Module.MenuJob[iLenMenuJob-1].URL,URLText);
     strcpy(_Module.MenuJob[iLenMenuJob-1].szParentName,pParentName);
	 _Module.MenuJob[iLenMenuJob-1].idMenu = IDM_DISPRES + dwNextIDMenu;
			
	 ITEMMENU *pMyItem = (ITEMMENU *) LocalAlloc(LMEM_FIXED, 
                sizeof(ITEMMENU)); 

			_Module.MenuJob[iLenMenuJob-1].myitem = pMyItem;
            _Module.MenuJob[iLenMenuJob-1].myitem->Whfont = 0; 
			_Module.MenuJob[iLenMenuJob-1].myitem->WhBitmap = Image_ID;
//			MenuJob[iLenMenuJob-1].myitem.hBitmap = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(Image_ID));



     strcpy(_Module.MenuJob[iLenMenuJob-1].myitem->psz_ItemText,sz_TextMenu) ; 
            ModifyMenu(hmenuContext, IDM_DISPRES + dwNextIDMenu, MF_BYCOMMAND | 
                MF_OWNERDRAW, IDM_DISPRES + dwNextIDMenu, (LPTSTR) pMyItem); 


 //
}

void CMServerComponent::ClearMenu()
{
	int i;
   for (i=iLenMenuSub;i>0;i--)
   {  
	   DestroyMenu(_Module.hMenuSub[i].hMenu);
	   LocalFree(_Module.hMenuSub[i].myitem);
   }
	   LocalFree(_Module.hMenuSub[0].myitem);

   for (i = iLenMenuJob-1;i>=0;i--){
	   LocalFree(_Module.MenuJob[i].myitem);
   }
}

void CMServerComponent::GetJobString(DWORD id, char *pJob)
{
	int k=-1;
    for (int i=0;i<iLenMenuJob;i++){
		if (_Module.MenuJob[i].idMenu == id){
			k = i;
			break;
		}
	}
	if (k >=0 ){
	 strcpy(pJob,_Module.MenuJob[i].URL);
	} else
	{
		strcpy(pJob,_TEXT(""));
	}
}




void DrawTransparentBitmap(HDC hdc, HBITMAP hBitmap, long xStart,
                           long yStart, COLORREF cTransparentColor)
   {
   BITMAP     bm;
   COLORREF   cColor;
   HBITMAP    bmAndBack, bmAndObject, bmAndMem, bmSave;
   HBITMAP    bmBackOld, bmObjectOld, bmMemOld, bmSaveOld;
   HDC        hdcMem, hdcBack, hdcObject, hdcTemp, hdcSave;
   POINT      ptSize;

   hdcTemp = CreateCompatibleDC(hdc);
   SelectObject(hdcTemp, hBitmap);   // Select the bitmap

   GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&bm);
   ptSize.x = bm.bmWidth;            // Get width of bitmap
   ptSize.y = bm.bmHeight;           // Get height of bitmap
   DPtoLP(hdcTemp, &ptSize, 1);      // Convert from device

                                     // to logical points

   // Create some DCs to hold temporary data.
   hdcBack   = CreateCompatibleDC(hdc);
   hdcObject = CreateCompatibleDC(hdc);
   hdcMem    = CreateCompatibleDC(hdc);
   hdcSave   = CreateCompatibleDC(hdc);

   // Create a bitmap for each DC. DCs are required for a number of
   // GDI functions.

   // Monochrome DC
   bmAndBack   = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);

   // Monochrome DC
   bmAndObject = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);

   bmAndMem    = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);
   bmSave      = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);

   // Each DC must select a bitmap object to store pixel data.
   bmBackOld   = (HBITMAP )SelectObject(hdcBack, bmAndBack);
   bmObjectOld = (HBITMAP )SelectObject(hdcObject, bmAndObject);
   bmMemOld    = (HBITMAP )SelectObject(hdcMem, bmAndMem);
   bmSaveOld   = (HBITMAP )SelectObject(hdcSave, bmSave);

   // Set proper mapping mode.
   SetMapMode(hdcTemp, GetMapMode(hdc));

   // Save the bitmap sent here, because it will be overwritten.
   BitBlt(hdcSave, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCCOPY);

   // Set the background color of the source DC to the color.
   // contained in the parts of the bitmap that should be transparent
   cColor = SetBkColor(hdcTemp, cTransparentColor);

   // Create the object mask for the bitmap by performing a BitBlt
   // from the source bitmap to a monochrome bitmap.
   BitBlt(hdcObject, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0,
          SRCCOPY);

   // Set the background color of the source DC back to the original
   // color.
   SetBkColor(hdcTemp, cColor);

   // Create the inverse of the object mask.
   BitBlt(hdcBack, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0,
          NOTSRCCOPY);

   // Copy the background of the main DC to the destination.
   BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdc, xStart, yStart,
          SRCCOPY);

   // Mask out the places where the bitmap will be placed.
   BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0, SRCAND);

   // Mask out the transparent colored pixels on the bitmap.
   BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcBack, 0, 0, SRCAND);

   // XOR the bitmap with the background on the destination DC.
   BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCPAINT);

   // Copy the destination to the screen.
   BitBlt(hdc, xStart, yStart, ptSize.x, ptSize.y, hdcMem, 0, 0,
          SRCCOPY);

   // Place the original bitmap back into the bitmap sent here.
   BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcSave, 0, 0, SRCCOPY);

   // Delete the memory bitmaps.
   DeleteObject(SelectObject(hdcBack, bmBackOld));
   DeleteObject(SelectObject(hdcObject, bmObjectOld));
   DeleteObject(SelectObject(hdcMem, bmMemOld));
   DeleteObject(SelectObject(hdcSave, bmSaveOld));

   // Delete the memory DCs.
   DeleteDC(hdcMem);
   DeleteDC(hdcBack);
   DeleteDC(hdcObject);
   DeleteDC(hdcSave);
   DeleteDC(hdcTemp);
   } 




void CMServerComponent::ShowMenuItem(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{ 
 
    ITEMMENU *pmyitem;      // pointer to item's font and string        
//    static HMENU hmenu;             // handle to main menu            
    static COLORREF crSelText;  // text color of selected item        
    static COLORREF crSelBkgnd; // background color of selected item  
    COLORREF crText;            // text color of unselected item      
    COLORREF crBkgnd;           // background color unselected item   
    LPMEASUREITEMSTRUCT lpmis;  // pointer to item of data             
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


 
    switch (uMsg) 
    { 

        case WM_MEASUREITEM: 

  
 
            hdc = GetDC(hwnd); 
            lpmis = (LPMEASUREITEMSTRUCT) lParam; 
            pmyitem = (ITEMMENU *) lpmis->itemData; 

			hBmp = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(pmyitem->WhBitmap));
		    GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bm);
			DeleteObject(hBmp);

			hFont = GetAFont(0);
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




 
			return; 
            break; 
 
        case WM_DRAWITEM: 

			


		    crSelText = GetSysColor(COLOR_HIGHLIGHTTEXT); 
		    crSelBkgnd = GetSysColor(COLOR_HIGHLIGHT); 


 
            lpdis = (LPDRAWITEMSTRUCT) lParam; 
            pmyitem = (ITEMMENU *) lpdis->itemData; 


			if ((pmyitem->WhBitmap == IDB_ITEMDEFAULT)&&(lpdis->itemState & ODS_SELECTED)){
			   hBmp = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_ITEMDEFAULT_N));
			} else {
			   hBmp = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(pmyitem->WhBitmap));
			}
		    GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bm);
			
 
            if (lpdis->itemState & ODS_SELECTED) 
            { 
                crText = SetTextColor(lpdis->hDC, crSelText); 
                crBkgnd = SetBkColor(lpdis->hDC, crSelBkgnd); 
                fSelected = TRUE; 
            } 
 
//            wCheckX = GetSystemMetrics(SM_CXMENUCHECK); 

            wCheckX = 0; 
            nTextX = wCheckX + lpdis->rcItem.left+bm.bmWidth; 
            nTextY = lpdis->rcItem.top; 
 
			if ( pmyitem->Whfont == 1 ) {
 			  hFont = GetAFont(0);
              hfontOld = (HFONT)SelectObject(lpdis->hDC,hFont ); 
			}
//			GetStockObject (SYSTEM_FONT)

            SIZE size;
			 
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
//			pS.x = wCheckX/2 + lpdis->rcItem.left;
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
//++			  DeleteObject(hFont);
			}



			return;
			break;
 
    } 
} 
 
HFONT CMServerComponent::GetAFont(int fnFont) 
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

void CMServerComponent::InitServer()
{
	LPSTR lpCmdLine = GetCommandLine();

	char strPath[255];
	int k;
	strcpy(strPath,lpCmdLine);
	for (k = strlen(strPath)-1;k>0;k--){
		if (strPath[k] == '\\'){break;}
	}
	strPath[k] = 0;
	if (strlen(strPath) > 0 ){
	SetCurrentDirectory(&strPath[1]);
	}



    CRegisterSave Reg;
	Reg.AutoRun(TRUE);
//	DownLoadBookMark("SGCombo.com","/mis/bookmark/bookmark.htm","\\about.htm");
}

void CMServerComponent::ExitServer()
{

}





void CMServerComponent::AddExplorerFovorites()
{
		HKEY hkeyRun;
		unsigned long LenRead;
		DWORD dwType;
	char FolderFovorites[255];
	    LenRead = 254;
        const char s_cszDebugKey[] = _T("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders");
		const char s_ValueName[] = _T("Favorites");


	    RegOpenKeyEx(HKEY_CURRENT_USER,s_cszDebugKey,0,KEY_READ,&hkeyRun);
		RegQueryValueEx(hkeyRun,s_ValueName,NULL,&dwType,(unsigned char *)FolderFovorites,&LenRead);
        RegCloseKey(hkeyRun);

		//

		  WIN32_FIND_DATA FindFileData;
		  HANDLE hFind;
		  char workFileName[255];
		  char CurrentPath[255];
		  char temp[255];
		  char temp1[255];
		  strcpy(workFileName,FolderFovorites);
		  strcpy(CurrentPath,FolderFovorites);
			CMSteck Steck;
			Steck.Save(CurrentPath);
  		  InsertSubMenu("Top",CurrentPath,"Explorer Favorites",IDB_EXPLORER);
		  while (Steck.Restore(workFileName) == TRUE )
		  {
		  strcpy(CurrentPath,workFileName);
		  strcat(workFileName,"\\*.*");

          hFind = FindFirstFile(workFileName, &FindFileData);
          if (hFind != INVALID_HANDLE_VALUE) {
			  FindNextFile(hFind,&FindFileData);
			  while (FindNextFile(hFind,&FindFileData)== TRUE){
				  if (FindFileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY){
					  strcpy(temp,CurrentPath);
					  strcat(temp,"\\");
					  strcat(temp,FindFileData.cFileName);
		              InsertSubMenu(CurrentPath,temp,FindFileData.cFileName);
					  Steck.Save(temp);
				  }else{
					  strcpy(temp,CurrentPath);
					  strcat(temp,"\\");
					  strcat(temp,FindFileData.cFileName);
					  strncpy(temp1,FindFileData.cFileName,strlen(FindFileData.cFileName)-4);
					  temp1[strlen(FindFileData.cFileName)-4] = 0;
  		              InsertMunuItemN(CurrentPath,temp1,temp);
				  }
			  }
  
		  }    
          FindClose(hFind);
		  }
  
		//

}

#define MAX_FILE_NETSCAPE 100000
void CMServerComponent::AddNetscapeFoforites()
{
			char szMessage[255];
			unsigned long ls=254;
			GetUserName(szMessage,&ls);
	struct LINKName{
		char strParent[255];
	};
		InsertSubMenu("Top","NetscapeFovorites","Netscape Bookmarks",IDB_NETSCAPE);

	  LINKName Par[15];
	  strcpy(Par[0].strParent,"NetscapeFovorites");
      HFILE theFile = HFILE_ERROR;
      DWORD lastErr  = NO_ERROR;
	  long lBuf = MAX_FILE_NETSCAPE;
	  long Count;
	  char Buf[MAX_FILE_NETSCAPE];
 		HKEY hkeyRun;
		DWORD dwType;

      // Attempt to open the file exclusively.
        char s_cszDebugKey[255];
		char psz_Buf[255];
		unsigned long LenRead = 250;
		psz_Buf[0] = 0;
		strcpy(s_cszDebugKey,"SOFTWARE\\Netscape\\Netscape Navigator");
		char *s_ValueName= "CurrentVersion";

	    RegOpenKeyEx(HKEY_LOCAL_MACHINE,s_cszDebugKey,0,KEY_READ,&hkeyRun);
		LONG ret = RegQueryValueEx(hkeyRun,s_ValueName,NULL,&dwType,(unsigned char *)psz_Buf,&LenRead);
        RegCloseKey(hkeyRun);
		if (ERROR_SUCCESS != ret){
			return;
		}

		strcat(s_cszDebugKey,"\\");
		strcat(s_cszDebugKey,psz_Buf);
		strcat(s_cszDebugKey,"\\Main");

		char *s_V = "Install Directory";
		LenRead = 250;
		psz_Buf[0] = 0;
		RegOpenKeyEx(HKEY_LOCAL_MACHINE,s_cszDebugKey,0,KEY_READ,&hkeyRun);
		ret = RegQueryValueEx(hkeyRun,s_V,NULL,&dwType,(unsigned char *)psz_Buf,&LenRead);
        RegCloseKey(hkeyRun);

		if (ERROR_SUCCESS != ret){
			return;
		}


		if (LenRead < 13){
			return;
		}

		strncpy(s_cszDebugKey,psz_Buf,strlen(psz_Buf)-13);
		s_cszDebugKey[strlen(psz_Buf)-13]=0;
		strcat(s_cszDebugKey,"\\Users\\");
		strcat(s_cszDebugKey,szMessage);
		strcat(s_cszDebugKey,"\\bookmark.htm");

      theFile = _lopen(s_cszDebugKey, OF_READ | OF_SHARE_EXCLUSIVE);
	  Count = 0;
	  Count = _lread(theFile,Buf,lBuf);
	  _lclose(theFile);	

	  if (Count > 0 ) {
       AddSubMenuFromBookmark("NetscapeFovorites",Buf,Count);
	  } else {
		strncpy(s_cszDebugKey,psz_Buf,strlen(psz_Buf)-13);
		s_cszDebugKey[strlen(psz_Buf)-13]=0;
		strcat(s_cszDebugKey,"\\Users\\default\\");
		strcat(s_cszDebugKey,"\\bookmark.htm");


      theFile = _lopen(s_cszDebugKey, OF_READ | OF_SHARE_EXCLUSIVE);
	  Count = 0;
	  Count = _lread(theFile,Buf,lBuf);
	  _lclose(theFile);	
		if (Count > 0 ) {
			AddSubMenuFromBookmark("NetscapeFovorites",Buf,Count);
		  }
	  }

}

void CMServerComponent::AddSubMenuFromBookmark(char *psz_NameMenu, char *Buf,long Count)
{

	struct LINKName{
		char strParent[255];
	};
	  int CountSubMenu = 0;
	  LINKName Par[15];
	  strcpy(Par[0].strParent,psz_NameMenu);

      // Attempt to open the file exclusively.
	  long iN;
	  char bufName[255];
	  char NameMenu[255];
	  char Link[255];
	  int iTemp;
	  int iLavel = 0;
	  BOOL flMenu = false;
	  BOOL flLink = false;
	  iN=0;
	  for (long k=0; k < Count-1;k++){

		  if ((strncmp(&Buf[k],"<H3",3) == 0) || (strncmp(&Buf[k],"<h3",3)== 0)){
            iN++;
			iLavel++;
			flMenu = TRUE;
			k +=4;
		  }

		  if (strncmp(&Buf[k],"\">",2)==0){
			  k+=2;
			  if ((flMenu == TRUE ) || (flLink == TRUE)){
				  iTemp = 0;
				  while (Buf[k]!='<'){
					NameMenu[iTemp]=Buf[k];
					iTemp++;
					k++;
					if (iTemp > 250){
						break;
					}
				  }
				  NameMenu[iTemp]=0;
				  if (flMenu == TRUE){
					  CountSubMenu++;
					  sprintf(bufName,"%d %s",CountSubMenu,Par[0].strParent);
				  InsertSubMenu(Par[iLavel-1].strParent,bufName,NameMenu);
				  strcpy(Par[iLavel].strParent,bufName);
				  }
				  if (flLink == TRUE ){
					  InsertMunuItemN(Par[iLavel].strParent,NameMenu,Link);
				  }
				  flMenu=FALSE;
				  flLink=FALSE;
			  }
		  }
		  	


		  if ((strncmp(&Buf[k],"</DL",3)==0) || (strncmp(&Buf[k],"</dl",3)==0)){
			  k+=3;
			  if (iLavel > 0){
			     iLavel--;
			  }
		}

		  if ((strncmp(&Buf[k],"<A HREF=\"",9)==0) || (strncmp(&Buf[k],"<a HREF=\"",9)==0)){
			flLink = TRUE;
			k += 9;
				  iTemp = 0;
				  while (Buf[k]!='\"'){
					Link[iTemp]=Buf[k];
					iTemp++;
					k++;
					if (iTemp > 250){
						break;
					}
				  }
				  Link[iTemp]=0;

		  }

	  }
}

void CMServerComponent::AddLocalMenu()
{
		InsertSubMenu("Top","LocalMenu","Local menu",IDB_LOCALMENU);


      HFILE theFile = HFILE_ERROR;
      DWORD lastErr  = NO_ERROR;
	  long lBuf = MAX_FILE_NETSCAPE;
	  long Count;
	  char Buf[MAX_FILE_NETSCAPE];
        char s_cszDebugKey[255];
		char psz_Buf[255];
		unsigned long LenRead = 250;
		psz_Buf[0] = 0;

  	strcpy(s_cszDebugKey,"C:\\MIS\\menu.htm");
		
      theFile = _lopen(s_cszDebugKey, OF_READ | OF_SHARE_EXCLUSIVE);
	  Count = _lread(theFile,Buf,lBuf);
	  _lclose(theFile);	
	  if (Count > 0){
       AddSubMenuFromBookmark("LocalMenu",Buf,Count);
	  }


}

void CMServerComponent::AddIntranet(char *NameFolder,WORD Id_Fold)
{
      HFILE theFile = HFILE_ERROR;
      DWORD lastErr  = NO_ERROR;
	  long lBuf = MAX_FILE_NETSCAPE;
	  long Count;
	  char Buf[MAX_FILE_NETSCAPE];
        char s_cszDebugKey[255];
		char psz_Buf[255];
		unsigned long LenRead = 250;
		psz_Buf[0] = 0;

		InsertSubMenu("Top",NameFolder,NameFolder,Id_Fold);
		GetCurrentDirectory(250,s_cszDebugKey);
 	   strcat(s_cszDebugKey,"\\");
 	   strcat(s_cszDebugKey,NameFolder);
 	   strcat(s_cszDebugKey,".htm");
		
      theFile = _lopen(s_cszDebugKey, OF_READ | OF_SHARE_EXCLUSIVE);
	  Count = _lread(theFile,Buf,lBuf);
	  _lclose(theFile);	
	  if (Count > 0){
        AddSubMenuFromBookmark(NameFolder,Buf,Count);
	  }
}
 

void CMServerComponent::AddAllBookmarks()
{
		  WIN32_FIND_DATA FindFileData;
		  HANDLE hFind;
		  char workFileName[255];
		  char temp1[255];
		  GetCurrentDirectory(250,workFileName);
   	      strcat(workFileName,"\\*.htm");
          hFind = FindFirstFile(workFileName, &FindFileData);
          if (hFind != INVALID_HANDLE_VALUE) {
			  while (TRUE){
				  if (FindFileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY){
				  }else
				  {
					  strncpy(temp1,FindFileData.cFileName,strlen(FindFileData.cFileName)-4);
					  temp1[strlen(FindFileData.cFileName)-4] = 0;
					  AddIntranet(temp1);
				  }
				  if (FindNextFile(hFind,&FindFileData)== FALSE){ break;}
			  }
		  }
}

void CMServerComponent::DownLoadBookMark(char *ServerName,char *NameFile,char *NameMenu)
{
	char dirName[255];
    DWORD cb;


	CDownloadData Data;
	Data.GetURL_ASP(ServerName,NameFile);
 	if (Data.LenData > 0 ){
		GetCurrentDirectory(250,dirName);
		strcat(dirName,NameMenu);


    HANDLE ihfile = CreateFile(dirName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
                      FILE_ATTRIBUTE_NORMAL, NULL);
    

//    HANDLE ihfile  = CreateFile(dirName, GENERIC_WRITE, 0, NULL, OPEN_EXISTING,
//                      FILE_FLAG_SEQUENTIAL_SCAN, NULL);
    
    WriteFile(ihfile, (PVOID) (Data.pData), Data.LenData, &cb, NULL);
    CloseHandle(ihfile);
    
    }

}

void CMServerComponent::InsertSubMenuFromFile(char *pTop, char *pFileName)
{

   FILE *stream;
   char seps[]   = "^\t\n";
   char *token;
   char s_File[255];
   GetCurrentDirectory(255,s_File);
   strcat(s_File,_T("\\"));
   strcat(s_File,pFileName);	   
   long NFolder = 0;
   char line[600];
   char NameMenuSub1[240];
   char ParentName[240];

   if( (stream = fopen( s_File, "r" )) != NULL )
   {
	   fgets( line, 550, stream );
	   while (!feof( stream )){
		
 
   
         
   token = strtok( line, seps );
   if (token != NULL ){
//
//   folder 
//
   if (strcmp(token,"F")==0) {
      while( token != NULL )
	  {
          /* While there are tokens in "string" */
          //printf( " %s\n", token );
          /* Get next token: */
          token = strtok( NULL, seps );
		  if (strcmp(token,"end")==0){
			  NFolder--;
			  break;
		  } else {
			  NFolder++;
			  sprintf(NameMenuSub1,"%s_%d",pTop,NFolder);
			  if ((NFolder-1)> 0 ) {
			    sprintf(ParentName,"%s_%d",pTop,NFolder-1);
			  } else {
			    sprintf(ParentName,"%s",pTop);
			  }

			  InsertSubMenu(ParentName,NameMenuSub1,token);
			  break;
		  }
		}
   }

//
//   Item 
//
   if (strcmp(token,"I")==0) {
          /* While there are tokens in "string" */
          //printf( " %s\n", token );
          /* Get next token: */
          token = strtok( NULL, seps );
		  strcpy(NameMenuSub1,token);
          token = strtok( NULL, seps );
		  char NameP[200];
          token = strtok( NULL, seps );
		  strcpy(NameP,token);
          token = strtok( NULL, seps );
			  if ((NFolder)> 0 ) {
			    sprintf(ParentName,"%s_%d",pTop,NFolder);
			  } else {
			    sprintf(ParentName,"%s",pTop);
			  }

		  InsertMunuItemN(ParentName,NameMenuSub1,NameP);
   }
   }

		if( fgets( line, 550, stream ) == NULL){
		   break;
		}

        if (ferror( stream )){
			break;
		}

	   }
      fclose( stream );
   }

	
}

long CMServerComponent::GetCountMenuInScreen()
{
    BITMAP  bm;
	HBITMAP hBmp;

			hBmp = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_CHECK));
		    GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bm);
			DeleteObject(hBmp);

return (GetSystemMetrics(SM_CYMAXIMIZED)/bm.bmHeight)-2;
}



BOOL CMServerComponent::AskExit()
{

	BOOL ret = FALSE;
	if (pCWndExit != NULL) {
		((CExit *)pCWndExit)->ShowWindow(SW_HIDE);
		((CExit *)pCWndExit)->ShowWindow(SW_SHOW);
	} else {
       CExit *pD = new CExit;
       pCWndExit = pD;
       pD->DoModal(::GetDesktopWindow());
	   ret = pD->boolReturnValue;
	   delete pD;
	   pCWndExit = NULL;

	}

  return ret;
}
