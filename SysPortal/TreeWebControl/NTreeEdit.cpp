// NTreeEdit.cpp : Implementation of CNTreeEdit

#include "stdafx.h"
#include "TreeWebControl.h"
#include "NTreeEdit.h"
#include <comdef.h>

/////////////////////////////////////////////////////////////////////////////
// CNTreeEdit

VOID CNTreeEdit::ResizeWindowPanel()
{
	long lStartPos;
		RECT Rect;
		::GetWindowRect(hWndPlus,&Rect);
		lStartPos = Rect.bottom- Rect.top + 2*GetSystemMetrics(SM_CYBORDER) ; 
		::GetWindowRect(m_hWnd,&Rect);
		InnerWidth = Rect.right - Rect.left ;
		InnerHeight = Rect.bottom - Rect.top; 
	  DWORD wHightEdit = 0;
	  DWORD wHightUrl = 0;
	  DWORD wHightTree = InnerHeight - lStartPos  ;
	  DWORD wBorder = GetSystemMetrics(SM_CYBORDER);
 	  h_tree = GetDlgItem(IDC_TREE_CTRL);
    

  


	::MoveWindow(h_tree,0,lStartPos,InnerWidth,wHightTree,TRUE);
	
}

VOID CNTreeEdit::SetTextParam()
{
 int k = 1;
}

STDMETHODIMP CNTreeEdit::get_URL(BSTR *pVal)
{
		*pVal = m_URL.Copy();
	return S_OK;
}

STDMETHODIMP CNTreeEdit::put_URL(BSTR newVal)
{
	m_URL=newVal ;
	if (BoolInit == TRUE ){
	  LoadUserMenu();
	}
	return S_OK;
}

BOOL CNTreeEdit::TestNoChildren(HTREEITEM hti)
{
	HTREEITEM hItem;
	hItem = TreeView_GetChild(h_tree,hti);
	if (hItem){ return FALSE;} else
	{return TRUE;}
}

VOID CNTreeEdit::TestFolderIcon(HTREEITEM hti)
{
    TVITEM tvi; 
    
        tvi.mask = 
            TVIF_IMAGE |  
            TVIF_PARAM |
            TVIF_STATE | TVIF_SELECTEDIMAGE ; 

        tvi.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_STATE ; 
        tvi.hItem = hti; 

		TreeView_GetItem(h_tree, &tvi); 


//
		if ((tvi.iSelectedImage == mi_nOpen) ||  
			(  tvi.iImage == mi_nClose)) {

		if (tvi.state & TVIS_EXPANDED){
			if (TestNoChildren(hti)){
                tvi.hItem = hti; 
                tvi.iImage = mi_nClose; 
                tvi.iSelectedImage = mi_nClose; 
			} else {
                tvi.hItem = hti; 
                tvi.iImage = mi_nOpen; 
                tvi.iSelectedImage = mi_nOpen; 
			}
		} else {
                tvi.hItem = hti; 
                tvi.iImage = mi_nClose; 
                tvi.iSelectedImage = mi_nClose; 
		}
		TreeView_SetItem(h_tree, &tvi); 
	}

}


void CNTreeEdit::TestChildFolderIcon(HTREEITEM hti)
{
	//
	// Get the first subitem.
	//
	HTREEITEM hItem;

	HTREEITEM hItemBase;
	hItem = TreeView_GetChild(h_tree,hti);
	hItemBase = hItem;
	//
	while (hItem != NULL) {
  	   TestFolderIcon(hItem);
	   hItem = TreeView_GetNextItem(h_tree,hItem,TVGN_NEXT );
	}
}




void CNTreeEdit::LoadUserMenu()
{


       TreeView_DeleteAllItems(GetDlgItem(IDC_TREE_CTRL));
	   LenStectItem = 0;
       NFolder = 0;
 

IStream* pStream;
char strWork[255];
int indexStart = 0;
char buffer;
DWORD dwGot;
HRESULT hr = NOERROR;


LPCSTR lpzrUniqueIdentifier = NULL;  

  USES_CONVERSION;
 
lpzrUniqueIdentifier = OLE2A(m_URL.m_str);
    

//mbtowc(,bufName,m_URL.Length());

// Open a blocking type stream to the Web site stored in the 
// string szWebSite.
if (URLOpenBlockingStream( 0, lpzrUniqueIdentifier  , &pStream, 0, 0)== S_OK ) {

do {
    hr = pStream->Read( &buffer, 1, &dwGot );
	strWork[indexStart] = buffer;
	indexStart++;
	if (buffer == 13) {
      strWork[indexStart-1] = '\0';
	  MakeStringLoadFile(strWork);
	  indexStart = 0;
	}
    // Do something with contents of buffer. 
} while( SUCCEEDED(hr) && hr != S_FALSE);

  pStream->Release();
}
}

BOOL CNTreeEdit::TestFolder(HTREEITEM hDest)
{
	    TVITEM tvi;
        tvi.mask = 
            TVIF_IMAGE |  
            TVIF_PARAM |
            TVIF_STATE | TVIF_SELECTEDIMAGE ; 

        tvi.hItem = hDest; 
		BOOL ret = TreeView_GetItem(h_tree, &tvi); 
		if ((tvi.iImage == mi_nClose) || (tvi.iImage == mi_nOpen)){
			return TRUE;
		}
		return FALSE;
}

int CNTreeEdit::AddIconsToImageList(DWORD IDI_icon)
{
	int iRet;	
    HICON hicon;
    hicon = LoadIcon(_Module.GetModuleInstance(), MAKEINTRESOURCE(IDI_icon)); 
	iRet = ImageList_AddIcon(hImageList, hicon); 
	return iRet;
}

HTREEITEM CNTreeEdit::InsertNewFolder(LPSTR lpszItem, int IndexFolder)
{
	HWND hwndTV;
    TVITEM tvi; 
    TVINSERTSTRUCT tvins; 
    HTREEITEM hPrev = NULL; 
    HTREEITEM hPrevRootItem = NULL; 
    HTREEITEM hPrevLev2Item = NULL; 
	HTREEITEM hDest= NULL;
	hwndTV = GetDlgItem(IDC_TREE_CTRL);
  


       tvi.mask = TVIF_TEXT | TVIF_IMAGE 
         | TVIF_SELECTEDIMAGE | TVIF_PARAM; 
 
         // Set the text of the item. 
         tvi.pszText = lpszItem; 
         tvi.cchTextMax = lstrlen(lpszItem); 
 
   
		    // Save the heading level in the item's application-defined 
		    // data area. 


	int intLenStr = 5;
    LPSTR ParStr = (LPSTR)malloc(intLenStr+2);
	strcpy(ParStr," ");
    tvi.lParam = (LPARAM) ParStr; 

		    tvi.iImage = mi_nClose; 
		    tvi.iSelectedImage = mi_nClose; 
		    tvins.item = tvi; 
		    tvins.hInsertAfter = TVI_LAST; 



     hDest=TreeView_GetSelection(hwndTV);
     if (hDest) {
		    // Set the parent item based on the specified level. 
		    if (TestFolder(hDest) == TRUE ) {
		      tvins.hInsertAfter = (HTREEITEM) TVI_LAST; 
		      tvins.hParent = hDest; 
			} else {
		      tvins.hInsertAfter = hDest; 
		      tvins.hParent = TreeView_GetParent(h_tree,hDest); 
			}
	 } else {
 	   tvins.hParent = TVI_ROOT;
       tvins.hInsertAfter = TVI_LAST; 

	 }

   
    // Add the item to the tree view control. 
	 hPrev = (HTREEITEM) ::SendMessage(hwndTV, TVM_INSERTITEM, 0, 
         (LPARAM) (LPTVINSERTSTRUCT) &tvins); 
	return hPrev;
}


HWND WINAPI CNTreeEdit::CreateToolTip(HWND hwndOwner,char *strTT)
{
   
    INITCOMMONCONTROLSEX iccex; 
    HWND hwndTT;                 // handle to the tooltip control
          // struct specifying info about tool in tooltip control
    TOOLINFO ti;
    unsigned int uid = 0;       // for ti initialization
    LPTSTR lptstr = strTT;
    RECT rect;                  // for client area coordinates

    /* INITIALIZE COMMON CONTROLS */
    iccex.dwICC = ICC_WIN95_CLASSES;
    iccex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    InitCommonControlsEx(&iccex);
	
    /* CREATE A TOOLTIP WINDOW */
    hwndTT = CreateWindowEx(WS_EX_TOPMOST,
        TOOLTIPS_CLASS,
        NULL,
        WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP,		
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        hwndOwner,
        NULL,
        _Module.GetModuleInstance(),
        NULL
        );

    ::SetWindowPos(hwndTT,
        HWND_TOPMOST,
        0,
        0,
        0,
        0,
        SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

    /* GET COORDINATES OF THE MAIN CLIENT AREA */
    ::GetClientRect (hwndOwner, &rect);
	
    /* INITIALIZE MEMBERS OF THE TOOLINFO STRUCTURE */
    ti.cbSize = sizeof(TOOLINFO);
    ti.uFlags = TTF_SUBCLASS;
    ti.hwnd = hwndOwner;
    ti.hinst = _Module.GetModuleInstance();
    ti.uId = uid;
    ti.lpszText = lptstr;
        // Tooltip control will cover the whole window
    ti.rect.left = rect.left;    
    ti.rect.top = rect.top;
    ti.rect.right = rect.right;
    ti.rect.bottom = rect.bottom;
    
    /* SEND AN ADDTOOL MESSAGE TO THE TOOLTIP CONTROL WINDOW */
    ::SendMessage(hwndTT, TTM_ADDTOOL, 0, (LPARAM) (LPTOOLINFO) &ti);

    return(hwndTT);    
}

VOID CNTreeEdit::ExpandChildren(HTREEITEM hti,DWORD Key)
{
 	//
	// Get the first subitem.
	//
	HTREEITEM hItem;
	HTREEITEM hItemBase;
	hItem = TreeView_GetChild(h_tree,hti);
	hItemBase = hItem;
	//
	// Do the same for other subitems of hSrc.
	//
	while (hItem != NULL) {
		   if (TestFolder(hItem)){
              TreeView_Expand(h_tree,hItem,Key);
                TestFolderIcon(hItem);
	    	  ExpandChildren(hItem,Key);
		   }
	   hItem = TreeView_GetNextItem(h_tree,hItem,TVGN_NEXT );
	} 
}




VOID CNTreeEdit::ExpandAllW(DWORD Key) {
	//
	//
	HTREEITEM hItem;
	HTREEITEM hItemBase;
	    hItemBase =  TreeView_GetRoot(h_tree); 

	hItem = hItemBase; //TreeView_GetChild(h_tree,hItemBase);
	//
	//
	while (hItem != NULL) {
		   if (TestFolder(hItem)){
              TreeView_Expand(h_tree,hItem,Key);
              ExpandChildren(hItem,Key);
              TestFolderIcon(hItem);
		   }
	   hItem = TreeView_GetNextItem(h_tree,hItem,TVGN_NEXT );
	}
}





LRESULT CNTreeEdit::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		ATLTRACE(_T("OnInitDialog\n"));
 
	   	HWND tmhWnd = GetDlgItem(IDC_TREE_CTRL);
	    h_tree = tmhWnd;
//        m_TreeClient.Attach(::GetDlgItem(m_hWnd, IDC_TREE_CTRL));
		FreezeEvents(FALSE);
  

//----

	    hWndPlus = GetDlgItem(IDC_BTN_PLUS);
	    hWndMinus = GetDlgItem(IDC_BTN_COLLAPSE);
		CreateToolTip(hWndPlus,"Expand");
		CreateToolTip(hWndMinus,"Collapse");
  


        ::SendMessage(hWndPlus,BM_SETIMAGE, IMAGE_BITMAP, 
            (LPARAM)hPlusBitmap);
    

        ::SendMessage(hWndMinus,BM_SETIMAGE, IMAGE_BITMAP, 
          (LPARAM)m_MinusBitmap);




    
		ResizeWindowPanel();

	    TreeView_SetImageList(
        tmhWnd,
        hImageList,
        TVSIL_NORMAL );	
		// TODO : Add Code for message handler. Call DefWindowProc if necessary.
	    LoadUserMenu();
	  ::SendMessage(GetDlgItem(IDC_TREE_CTRL), 
                           TVM_SETTEXTCOLOR, 
                           0, 
                           m_TreeTextColor);
	      ::SendMessage(GetDlgItem(IDC_TREE_CTRL), 
                           TVM_SETBKCOLOR, 
                           0, 
                           m_TreeBkColor);
		BoolInit = TRUE;
		return 0;
	}





void CNTreeEdit::MakeStringLoadFile(char *line)
{

   char seps[]   = "^\t\n";
   char *token;

   char NameMenuSub1[240];

 
 
   
         
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
			  InsertEndFolder();
  			  NFolder--;
			  break;
		  } else {
			  NFolder++;
			  InsertNextFolder(token,1);	
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
		  char NameP[255];
		  NameP[0]='\0';
          token = strtok( NULL, seps );
		  strcpy(NameP,token);
          token = strtok( NULL, seps );

		  InsertItem(NameMenuSub1,NameP);	
   }
   }
}


void CNTreeEdit::InsertNextFolder(LPSTR lpszItem, int IndexFolder)
{
	HWND hwndTV;
    TVITEM tvi; 
    TVINSERTSTRUCT tvins; 
    HTREEITEM hPrev = (HTREEITEM) TVI_FIRST; 
    HTREEITEM hPrevRootItem = NULL; 
    HTREEITEM hPrevLev2Item = NULL; 
	hwndTV = GetDlgItem(IDC_TREE_CTRL);
  
    tvi.mask = TVIF_TEXT | TVIF_IMAGE 
        | TVIF_SELECTEDIMAGE | TVIF_PARAM; 
 
    // Set the text of the item. 
    tvi.pszText = lpszItem; 
    tvi.cchTextMax = lstrlen(lpszItem); 
 
   
    // Save the heading level in the item's application-defined 
    // data area.
	

	int intLenStr = 2;
    LPSTR ParStr = (LPSTR)malloc(intLenStr+2);
	strcpy(ParStr," ");
    tvi.lParam = (LPARAM) ParStr; 



    tvi.iImage = mi_nClose; 
    tvi.iSelectedImage = mi_nClose; 
    tvins.item = tvi; 
    tvins.hInsertAfter = TVI_LAST; 
 
    // Set the parent item based on the specified level. 
	if (LenStectItem > 0 ) {
         tvins.hParent = SteckItem[LenStectItem-1]; 
	}else {
		tvins.hParent = TVI_ROOT;
	}
   
    // Add the item to the tree view control. 
    hPrev = (HTREEITEM) ::SendMessage(hwndTV, TVM_INSERTITEM, 0, 
         (LPARAM) (LPTVINSERTSTRUCT) &tvins); 
 
		SteckItem[LenStectItem]=hPrev;
		LenStectItem++;

}

void CNTreeEdit::InsertItem(LPSTR lpszItem, LPSTR lpszParameters)
{
	HWND hwndTV;
    TVITEM tvi; 
    TVINSERTSTRUCT tvins; 
    static HTREEITEM hPrev = (HTREEITEM) TVI_FIRST; 
    static HTREEITEM hPrevRootItem = NULL; 
    static HTREEITEM hPrevLev2Item = NULL; 
	hwndTV = GetDlgItem(IDC_TREE_CTRL);
 
    tvi.mask = TVIF_TEXT | TVIF_IMAGE 
        | TVIF_SELECTEDIMAGE | TVIF_PARAM; 
 
    // Set the text of the item. 
    tvi.pszText = lpszItem; 
    tvi.cchTextMax = lstrlen(lpszItem); 
 
    // Assume the item is not a parent item, so give it a 
    // document image. 
    tvi.iImage = mi_Document; 
    tvi.iSelectedImage = mi_Document; 
 
    // Save the heading level in the item's application-defined 
    // data area. 

	int intLenStr = strlen(lpszParameters);
    LPSTR ParStr = (LPSTR)malloc(intLenStr+2);
	strcpy(ParStr,lpszParameters);
    tvi.lParam = (LPARAM) ParStr; 
 
    tvins.item = tvi; 
    tvins.hInsertAfter = TVI_LAST; 

	if (LenStectItem > 0 ) {
         tvins.hParent = SteckItem[LenStectItem-1]; 
	}else {
		tvins.hParent = TVI_ROOT;
	}
 
    // Add the item to the tree view control. 
    hPrev = (HTREEITEM) ::SendMessage(hwndTV, TVM_INSERTITEM, 0, 
         (LPARAM) (LPTVINSERTSTRUCT) &tvins); 
 


 
}







STDMETHODIMP CNTreeEdit::Refresh()
{

	LoadUserMenu();

	return S_OK;
}

STDMETHODIMP CNTreeEdit::get_TreeBkColor(long *pVal)
{
	// TODO: Add your implementation code here
        *pVal = m_TreeBkColor;
	return S_OK;
}

STDMETHODIMP CNTreeEdit::put_TreeBkColor(long newVal)
{
	ATLTRACE(_T("put_TreeBkColor\n"));
    m_TreeBkColor = newVal;
		if (BoolInit == TRUE ){
	      ::SendMessage(GetDlgItem(IDC_TREE_CTRL), 
                           TVM_SETBKCOLOR, 
                           0, 
                           m_TreeBkColor);
		}
 
	return S_OK;
}

STDMETHODIMP CNTreeEdit::get_TreeTextColor(long *pVal)
{
    *pVal = m_TreeTextColor;
	return S_OK;
}

STDMETHODIMP CNTreeEdit::put_TreeTextColor(long newVal)
{
    m_TreeTextColor = newVal;
	ATLTRACE(_T("put_TreeTextColor\n"));
	if (BoolInit == TRUE ){
 	  ::SendMessage(GetDlgItem(IDC_TREE_CTRL), 
                           TVM_SETTEXTCOLOR, 
                           0, 
                           m_TreeTextColor);
	}
	return S_OK;
}

VOID CNTreeEdit::GetActiveFolderName()
{

	CComBSTR AllUrl;
	CComBSTR AllName ;
	HTREEITEM hItem;
	HTREEITEM hItemBase;
	    hItem =  m_CurrentItem;
	    TVITEM tvi_Sourse;
		

    AllName = "";

		char strTemp[255];
		strTemp[0]=0;

	//
	//
	while (hItem != NULL) {


//

        tvi_Sourse.mask = 
            TVIF_IMAGE |  
            TVIF_PARAM |
            TVIF_STATE | TVIF_SELECTEDIMAGE |
            TVIF_TEXT ;


        tvi_Sourse.hItem = hItem; 
        tvi_Sourse.pszText = strTemp; 
        tvi_Sourse.cchTextMax = 250; 
		TreeView_GetItem(h_tree, &tvi_Sourse); 

		if ((tvi_Sourse.iImage == mi_nClose) || (tvi_Sourse.iImage == mi_nOpen)){
			AllName += tvi_Sourse.pszText;
		}

//



       hItem = TreeView_GetParent(h_tree,hItem );
	}

   Fire_SelectFolder(AllUrl, AllName);
}
