//
//////////////////////////////////////////////////////////////////////



#ifndef _MTREE_CONTROL
#define _MTREE_CONTROL

#include "stdafx.h"
#include "commctrl.h"

// CreateATreeView - creates a tree view control. 
// Returns the handle to the new control if successful,
// or NULL otherwise. 
// hwndParent - handle to the control's parent window. 
// lpszFileName - name of the file to parse for tree view items.

HWND CreateATreeView(HWND hwndParent, LPSTR lpszFileName) 
{ 
    RECT rcClient;  // dimensions of client area 
    HWND hwndTV;    // handle to tree view control 
 
    // Ensure that the common control DLL is loaded. 
    InitCommonControls(); 
 
    // Get the dimensions of the parent window's client area, and create 
    // the tree view control. 
    GetClientRect(hwndParent, &rcClient); 
    hwndTV = CreateWindowEx(0, WC_TREEVIEW, "Tree View", 
        WS_VISIBLE | WS_CHILD | WS_BORDER | TVS_HASLINES, 
        0, 0, rcClient.right, rcClient.bottom, 
        hwndParent, (HMENU) ID_TREEVIEW, g_hinst, NULL); 
 
    // Initialize the image list, and add items to the control. 
    // InitTreeViewImageLists and InitTreeViewItems are application- 
    // defined functions. 
    if (!InitTreeViewImageLists(hwndTV) || 
            !InitTreeViewItems(hwndTV, lpszFileName)) { 
        DestroyWindow(hwndTV); 
        return FALSE; 
    } 
    return hwndTV;
} 



// InitTreeViewImageLists - creates an image list, adds three bitmaps 
// to it, and associates the image list with a tree view control. 
// Returns TRUE if successful, or FALSE otherwise. 
// hwndTV - handle to the tree view control. 
//
// Global variables and constants 
// g_nOpen, g_nClosed, and g_nDocument - integer variables for 
// indexes of the images. 
// CX_BITMAP and CY_BITMAP - width and height of an icon. 
// NUM_BITMAPS - number of bitmaps to add to the image list. 

BOOL InitTreeViewImageLists(HWND hwndTV) 
{ 
    HIMAGELIST himl;  // handle to image list 
    HBITMAP hbmp;     // handle to bitmap 

    // Create the image list. 
    if ((himl = ImageList_Create(CX_BITMAP, CY_BITMAP, 
        FALSE, NUM_BITMAPS, 0)) == NULL) 
        return FALSE; 

    // Add the open file, closed file, and document bitmaps. 
    hbmp = LoadBitmap(g_hinst, MAKEINTRESOURCE(IDB_OPEN_FILE)); 
    g_nOpen = ImageList_Add(himl, hbmp, (HBITMAP) NULL); 
    DeleteObject(hbmp); 

    hbmp = LoadBitmap(g_hinst, MAKEINTRESOURCE(IDB_CLOSED_FILE)); 
    g_nClosed = ImageList_Add(himl, hbmp, (HBITMAP) NULL); 
    DeleteObject(hbmp); 

    hbmp = LoadBitmap(g_hinst, MAKEINTRESOURCE(IDB_DOCUMENT)); 
    g_nDocument = ImageList_Add(himl, hbmp, (HBITMAP) NULL); 
    DeleteObject(hbmp); 

    // Fail if not all of the images were added. 
    if (ImageList_GetImageCount(himl) < 3) 
        return FALSE; 

    // Associate the image list with the tree view control. 
    TreeView_SetImageList(hwndTV, himl, TVSIL_NORMAL); 

    return TRUE; 
} 


// InitTreeViewItems - extracts headings from the specified file and 
// passes them to a function that adds them to a tree view control. 
// Returns TRUE if successful, or FALSE otherwise. 
// hwndTV - handle to the tree view control. 
// lpszFileName - name of file with headings.
 
BOOL InitTreeViewItems(HWND hwndTV, LPSTR lpszFileName) 
{ 
    HANDLE hf;            // handle to file 
    char szItemText[128]; // label text of tree view item 
    int nLevel;           // heading level 
 
    // Open the file to parse. 
    if ((hf = CreateFile(lpszFileName, GENERIC_READ, 
            FILE_SHARE_READ, (LPSECURITY_ATTRIBUTES) NULL, 
            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 
            (HANDLE) NULL)) == (HANDLE) INVALID_HANDLE_VALUE) 
        return FALSE; 
    
    // Call private function to parse the file looking for headings.
    while ( GetNextHeadingAndLevelFromFile(hf, szItemText, &nLevel) )
         // Add the item to the tree view control. 
         AddItemToTree(hwndTV, szItemText, nLevel); 
 
    return TRUE; 
} 
 
// AddItemToTree - adds items to a tree view control. 
// Returns the handle to the newly added item. 
// hwndTV - handle to the tree view control. 
// lpszItem - text of the item to add. 
// nLevel - level at which to add the item. 

HTREEITEM AddItemToTree(HWND hwndTV, LPSTR lpszItem, int nLevel)
{ 
    TVITEM tvi; 
    TVINSERTSTRUCT tvins; 
    static HTREEITEM hPrev = (HTREEITEM) TVI_FIRST; 
    static HTREEITEM hPrevRootItem = NULL; 
    static HTREEITEM hPrevLev2Item = NULL; 
    HTREEITEM hti; 
 
    tvi.mask = TVIF_TEXT | TVIF_IMAGE 
        | TVIF_SELECTEDIMAGE | TVIF_PARAM; 
 
    // Set the text of the item. 
    tvi.pszText = lpszItem; 
    tvi.cchTextMax = lstrlen(lpszItem); 
 
    // Assume the item is not a parent item, so give it a 
    // document image. 
    tvi.iImage = g_nDocument; 
    tvi.iSelectedImage = g_nDocument; 
 
    // Save the heading level in the item's application-defined 
    // data area. 
    tvi.lParam = (LPARAM) nLevel; 
 
    tvins.item = tvi; 
    tvins.hInsertAfter = hPrev; 
 
    // Set the parent item based on the specified level. 
    if (nLevel == 1) 
        tvins.hParent = TVI_ROOT; 
    else if (nLevel == 2) 
        tvins.hParent = hPrevRootItem; 
    else 
        tvins.hParent = hPrevLev2Item; 
 
    // Add the item to the tree view control. 
    hPrev = (HTREEITEM) SendMessage(hwndTV, TVM_INSERTITEM, 0, 
         (LPARAM) (LPTVINSERTSTRUCT) &tvins); 
 
    // Save the handle to the item. 
    if (nLevel == 1) 
        hPrevRootItem = hPrev; 
    else if (nLevel == 2) 
        hPrevLev2Item = hPrev; 
 
    // The new item is a child item. Give the parent item a 
    // closed folder bitmap to indicate it now has child items. 
    if (nLevel > 1) { 
        hti = TreeView_GetParent(hwndTV, hPrev); 
        tvi.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE; 
        tvi.hItem = hti; 
        tvi.iImage = g_nClosed; 
        tvi.iSelectedImage = g_nClosed; 
        TreeView_SetItem(hwndTV, &tvi); 
    } 
 
    return hPrev; 
} 

/*
 case WM_NOTIFY: 
     switch (((LPNMHDR) lParam)->code) {
	    case TVN_BEGINDRAG:
		 Main_OnBeginDrag(   // application-defined function 
                         hwndTV, (LPNMTREEVIEW) lParam); 
             break; 

		// Handle other notifications here. 

	   }
	 break; 

*/


// Main_OnBeginDrag - begins dragging an item in a tree view control. 
// hwndTV - handle to the image list. 
// lpnmtv - address of information about the item being dragged. 


void Main_OnBeginDrag(HWND hwndTV, LPNMTREEVIEW lpnmtv) 
{ 
    HIMAGELIST himl;    // handle to image list 
    RECT rcItem;        // bounding rectangle of item 
    DWORD dwLevel;      // heading level of item 
    DWORD dwIndent;     // amount that child items are indented 
 
    // Tell the tree view control to create an image to use 
    // for dragging. 
    himl = TreeView_CreateDragImage(hwndTV, lpnmtv->itemNew.hItem); 
 
    // Get the bounding rectangle of the item being dragged. 
    TreeView_GetItemRect(hwndTV, lpnmtv->itemNew.hItem, &rcItem, TRUE); 
 
    // Get the heading level and the amount that the child items are 
    // indented. 
    dwLevel = lpnmtv->itemNew.lParam; 
    dwIndent = (DWORD) SendMessage(hwndTV, TVM_GETINDENT, 0, 0); 
 
    // Start the drag operation. 
    ImageList_BeginDrag(himl, 0, 0, 0); 
 
    // Hide the mouse pointer, and direct mouse input to the 
    // parent window. 
    ShowCursor(FALSE); 
    SetCapture(GetParent(hwndTV)); 
    g_fDragging = TRUE; 
    return; 
} 


// Main_OnMouseMove - drags an item in a tree view control, 
// highlighting the item that is the target. 
// hwndParent - handle to the parent window. 
// hwndTV - handle to the tree view control.
// xCur and yCur - x- and y-coordinates of the mouse pointer. 

void Main_OnMouseMove(HWND hwndParent, HWND hwndTV, LONG xCur, LONG yCur) 
{ 
    HTREEITEM htiTarget;  // handle to target item 
    TVHITTESTINFO tvht;  // hit test information 
 
    if (g_fDragging) { 
 
        // Drag the item to the current position of the mouse pointer. 
        ImageList_DragMove(xCur, yCur); 
 
        // Find out if the pointer is on the item. If it is, 
		// highlight the item as a drop target. 
        tvht.pt.x = xCur; 
        tvht.pt.y = yCur; 
        if ((htiTarget = TreeView_HitTest(hwndTV, &tvht)) != NULL) { 
            TreeView_SelectDropTarget(hwndTV, htiTarget); 
        } 
    } 
    return; 
} 

// Main_OnLButtonUp - stops dragging a tree view item, releases the 
// mouse capture, and shows the mouse pointer.
//
// Global variable g_fDragging - indicates whether
// a drag operation is underway. 

void Main_OnLButtonUp(void) 
{ 
    if (g_fDragging) { 
        ImageList_EndDrag(); 
        ReleaseCapture(); 
        ShowCursor(TRUE); 
        g_fDragging = FALSE; 
    } 
    return; 
} 

BOOL TreeView_SetCheckState(HWND hwndTreeView, HTREEITEM hItem, BOOL fCheck)
{
    TVITEM tvItem;

    tvItem.mask = TVIF_HANDLE | TVIF_STATE;
    tvItem.hItem = hItem;
    tvItem.stateMask = TVIS_STATEIMAGEMASK;

    /*Image 1 in the tree view check box image list is the
    unchecked box. Image 2 is the checked box.*/
    
    tvItem.state = INDEXTOSTATEIMAGEMASK((fCheck ? 2 : 1));

    return TreeView_SetItem(hwndTreeView, &tvItem);
}

BOOL TreeView_GetCheckState(HWND hwndTreeView, HTREEITEM hItem)
{
    TVITEM tvItem;

    // Prepare to receive the desired information.
    tvItem.mask = TVIF_HANDLE | TVIF_STATE;
    tvItem.hItem = hItem;
    tvItem.stateMask = TVIS_STATEIMAGEMASK;

    // Request the information.
    TreeView_GetItem(hwndTreeView, &tvItem);

    // Return zero if it's not checked, or nonzero otherwise.
    return ((BOOL)(tvItem.state >> 12) -1);
}



#endif

