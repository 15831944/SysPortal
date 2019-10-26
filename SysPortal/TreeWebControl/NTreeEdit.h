// NTreeEdit.h : Declaration of the CNTreeEdit

#ifndef __NTREEEDIT_H_
#define __NTREEEDIT_H_

#include "resource.h"       // main symbols
#include <atlctl.h>
#include "comdef.h"
#include "commctrl.h"
#include "Windowsx.h"
#include "TreeWebControlCP.h"

#define DISPID_URL 0
#define DISPID_TreeBkColor 2	
#define DISPID_TreeTextColor 3	

	#define TCX_ICON  16 
	#define TCY_ICON  16 
	#define TNUM_ICONS 4 

EXTERN_C const IID DIID__INTreeEditEvents;

enum TYPESAVE             // type save and export file type
{
   Type_SAVE,
   Type_DHTML
} ;            

/////////////////////////////////////////////////////////////////////////////
// CNTreeEdit
class ATL_NO_VTABLE CNTreeEdit : 

	public CComObjectRootEx<CComSingleThreadModel>, 
	public CComCoClass<CNTreeEdit, &CLSID_NTreeEdit>,

   public IDispatchImpl<INTreeEdit, 
                         &IID_INTreeEdit,
                         &LIBID_TREEWEBCONTROLLib>,


	public CComCompositeControl<CNTreeEdit>,
//	public CStockPropImpl<CNTreeEdit, INTreeEdit, &IID_INTreeEdit, &LIBID_TREEWEBCONTROLLib>,
	public IOleControlImpl<CNTreeEdit>,
	public IOleObjectImpl<CNTreeEdit>,
	public IPointerInactiveImpl<CNTreeEdit>,
	public IOleInPlaceActiveObjectImpl<CNTreeEdit>,
	public IViewObjectExImpl<CNTreeEdit>,
	public IOleInPlaceObjectWindowlessImpl<CNTreeEdit>,
	public IConnectionPointContainerImpl<CNTreeEdit>,
	public ISpecifyPropertyPagesImpl<CNTreeEdit>,
	public IQuickActivateImpl<CNTreeEdit>,
	public IDataObjectImpl<CNTreeEdit>,
	public IProvideClassInfo2Impl<&CLSID_NTreeEdit, &DIID__INTreeEditEvents, &LIBID_TREEWEBCONTROLLib>,
	public IPropertyNotifySinkCP<CNTreeEdit>,
	public CProxy_INTreeEditEvents<CNTreeEdit>,
    public IPersistStreamInitImpl<CNTreeEdit>,
    public IPersistStorageImpl<CNTreeEdit>,
    public IPersistPropertyBagImpl<CNTreeEdit>,
    public IObjectSafetyImpl<CNTreeEdit, INTERFACESAFE_FOR_UNTRUSTED_CALLER |INTERFACESAFE_FOR_UNTRUSTED_DATA >

/*


     public CComObjectRootEx<CComSingleThreadModel>,
     public IDispatchImpl<ICompositeATLControl, 
                         &IID_ICompositeATLControl,
                         &LIBID_ALLCTLSLib>,
     public CComCompositeControl<CCompositeATLControl>,
     public IPersistStreamInitImpl<CCompositeATLControl>,
     public IOleControlImpl<CCompositeATLControl>,
     public IOleObjectImpl<CCompositeATLControl>,
     public IOleInPlaceActiveObjectImpl<CCompositeATLControl>,
     public IViewObjectExImpl<CCompositeATLControl>,
     public IOleInPlaceObjectWindowlessImpl<CCompositeATLControl>,
     public IPersistStorageImpl<CCompositeATLControl>,
     public ISpecifyPropertyPagesImpl<CCompositeATLControl>,
     public IQuickActivateImpl<CCompositeATLControl>,
     public IDataObjectImpl<CCompositeATLControl>,
     public IProvideClassInfo2Impl<&CLSID_CompositeATLControl, 
                                  NULL, &LIBID_ALLCTLSLib>,
     public CComCoClass<CCompositeATLControl,
                       &CLSID_CompositeATLControl>
*/

{
private:
	HWND hWndPlus;
	HWND hWndMinus;
	VOID ExpandChildren(HTREEITEM hti,DWORD Key);
	VOID ExpandAllW(DWORD Key);
	HWND WINAPI CreateToolTip(HWND hwndOwner,char *strTT);
	BOOL TestNoChildren(HTREEITEM hti);
	void TestChildFolderIcon(HTREEITEM hti);
	VOID TestFolderIcon(HTREEITEM hti);
	long mi_RootPersonalLink;
	int AddIconsToImageList(DWORD IDI_icon);
	HIMAGELIST hImageList;
	BOOL TestFolder(HTREEITEM hDest);
    void InsertNextFolder(LPSTR lpszItem, int IndexFolder);
    HTREEITEM InsertNewFolder(LPSTR lpszItem, int IndexFolder);
    void InsertItem(LPSTR lpszItem, LPSTR lpszParameters);
    void MakeStringLoadFile(char *line);
	void LoadUserMenu();
	VOID SetTextParam();
	CComBSTR  m_URL;
	BSTR m_URL_P;
	HWND h_tree;
	CComPtr<IOleClientSite> m_TreeClient;
	CWindow m_wndToolTip; 
	HWND m_hTheWnd ;
	HWND h_treeToolTip;
	int InnerWidth;
	int InnerHeight;
	long NFolder;
	VOID CNTreeEdit::ResizeWindowPanel();
	void InsertEndFolder(void){ LenStectItem--;};
	long mi_nOpen;
	BOOL BoolInit;
	long mi_nClose;
	BOOL m_BoolSaveFlag;
	BOOL m_SaveCurrentFolder;
	TYPESAVE m_TypeSave;
	HTREEITEM m_DropItem;
	HTREEITEM m_CurrentItem;
	HTREEITEM m_EditTreeItem;
	HTREEITEM m_TargetItem;
	BOOL m_bDragging;
	HANDLE hPlusBitmap;
	HANDLE m_MinusBitmap;
	DWORD m_TreeBkColor;
	DWORD m_TreeTextColor;
public:

DECLARE_REGISTRY_RESOURCEID(IDR_NTREEEDIT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CNTreeEdit)


	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(INTreeEdit)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IPointerInactive)

    COM_INTERFACE_ENTRY_IMPL(IQuickActivate) 
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
    COM_INTERFACE_ENTRY(IObjectSafety)
     COM_INTERFACE_ENTRY(IPersistStreamInit)
     COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
     COM_INTERFACE_ENTRY(IPersistStorage)
     COM_INTERFACE_ENTRY(IPersistPropertyBag)
 //


END_COM_MAP()

BEGIN_PROP_MAP(CNTreeEdit)
	PROP_ENTRY("URL",DISPID_URL, CLSID_NTreeEdit)
    PROP_ENTRY("TreeBkColor", DISPID_TreeBkColor, CLSID_NTreeEdit)
    PROP_ENTRY("TreeTextColor", DISPID_TreeTextColor, CLSID_NTreeEdit)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
//    PROP_DATA_ENTRY("URL", m_URL_P, VT_BSTR)
//    PROP_DATA_ENTRY("TreeBkColor", m_TreeBkColor, VT_UI4)
//    PROP_DATA_ENTRY("TreeTextColor", m_TreeTextColor, VT_UI4)

   
//	PROP_ENTRY("TreeBkColor", 2, CLSID_NULL)
//	PROP_ENTRY("TreeTextColor", 3, CLSID_NULL)
//	PROP_ENTRY("URL", 1, CLSID_NULL)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()


BEGIN_CONNECTION_POINT_MAP(CNTreeEdit)
	CONNECTION_POINT_ENTRY(DIID__INTreeEditEvents)
    CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink) 
END_CONNECTION_POINT_MAP()



BEGIN_MSG_MAP(CNTreeEdit)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
	CHAIN_MSG_MAP(CComCompositeControl<CNTreeEdit>)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	NOTIFY_HANDLER(IDC_TREE_CTRL, TVN_ITEMEXPANDED, OnItemexpandedTree_ctrl)
	COMMAND_HANDLER(IDC_BTN_PLUS, BN_CLICKED, OnClickedBtn_plus)
	COMMAND_HANDLER(IDC_BTN_COLLAPSE, BN_CLICKED, OnClickedBtn_collapse)

	NOTIFY_HANDLER(IDC_TREE_CTRL, NM_DBLCLK, OnDblclkTree_ctrl)
	MESSAGE_HANDLER(WM_SHOWWINDOW, OnShowWindow)
	NOTIFY_HANDLER(IDC_TREE_CTRL, TVN_SELCHANGED, OnSelchangedTree_ctrl)
	NOTIFY_HANDLER(IDC_TREE_CTRL, TVN_DELETEITEM, OnDeleteitemTree_ctrl)
	NOTIFY_HANDLER(IDC_TREE_CTRL, NM_CLICK, OnClickTree_ctrl)
	MESSAGE_HANDLER(WM_NCMOUSEMOVE, OnNcMouseMove)
END_MSG_MAP()


// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

BEGIN_SINK_MAP(CNTreeEdit)

//     SINK_ENTRY(IDC_TREE_CTRL, DISPID_MOUSEMOVE, OnMouseMove)
	//Make sure the Event Handlers have __stdcall calling convention
END_SINK_MAP()





BOOL PreTranslateAccelerator(MSG* pMsg,long p)
{
     ATLTRACE(_T("PreTranslateAccelerator\n"));
  // Accelerators are only keyboard or mouse messages
  if ((pMsg->message < WM_KEYFIRST || pMsg->message > WM_KEYLAST) &&
    (pMsg->message < WM_MOUSEFIRST || pMsg->message > WM_MOUSELAST))
    return FALSE;
  
  // Find a direct child of this window from the window that has focus.
  // This will be AxHost window for the hosted control.
  HWND hWndCtl = ::GetFocus();
  if( IsChild(hWndCtl) && ::GetParent(hWndCtl) != m_hWnd )
  {
    do hWndCtl = ::GetParent(hWndCtl);
    while( ::GetParent(hWndCtl) != m_hWnd );
  }
  
  // Give the control (via the AxHost) a chance to translate this message
  if (::SendMessage(hWndCtl, WM_FORWARDMSG, 0, (LPARAM)pMsg) ) return TRUE;
  
  // Check for dialog-type navigation accelerators
  return IsDialogMessage(pMsg);
}





HRESULT InPlaceActivate(LONG iVerb, const RECT* prcPosRect=NULL)
{
	HRESULT hr;
     ATLTRACE(_T("InPlaceActivate\n"));
	hr = CComControlBase::InPlaceActivate(iVerb, prcPosRect);
	if (m_wndToolTip.m_hWnd == NULL)
	{
		// If we're windowless we still need an HWND 
		if (m_bWndLess)
		{
			HDC hDC;
			// Get the HDC from the client
			m_spInPlaceSite->GetDC(NULL, OLEDC_NODRAW, &hDC);
			m_hTheWnd = WindowFromDC(hDC);
			m_spInPlaceSite->ReleaseDC(hDC);
		}
		else
			m_hTheWnd = m_hWnd;

		//Load the Common control library and create tooltip control
		InitCommonControls();
		m_wndToolTip.m_hWnd =
		::CreateWindow(TOOLTIPS_CLASS, (LPTSTR)NULL, TTS_ALWAYSTIP,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			NULL, (HMENU) NULL, _Module.GetModuleInstance(), NULL);

		// Ensure the tooltip always appears above our window
		::SetWindowPos(m_wndToolTip.m_hWnd, HWND_TOPMOST,0,0,0,0,
				SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOREDRAW|SWP_NOSIZE);

		TOOLINFO    ti;
		ti.cbSize = sizeof(TOOLINFO);
		ti.uFlags = 0;
		ti.hwnd   = m_hTheWnd;
		ti.uId    = 1;
		ti.hinst  = NULL;
		ti.lpszText = m_bWndLess ? ti.lpszText = _T("My Windowless Tip") : ti.lpszText = _T("My Windowed Tip");
		m_wndToolTip.SendMessage(TTM_ADDTOOL, 0, (LPARAM)&ti);
	}
	return hr;
} 





DWORD GetActivationPolicy()
{
     ATLTRACE(_T("GetActivationPolicy\n"));
    return POINTERINACTIVE_ACTIVATEONENTRY;
}



void RelayEvent(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (NULL != m_wndToolTip.m_hWnd)
	{
		MSG msg;

		msg.hwnd= m_hTheWnd;
		msg.message= message;
		msg.wParam= wParam;
		msg.lParam= lParam;
		msg.time= 0;
		msg.pt.x= LOWORD (lParam);
		msg.pt.y= HIWORD (lParam);

		::SendMessage(m_wndToolTip.m_hWnd, TTM_RELAYEVENT, 0, (LPARAM)&msg);	
	}
} 



	CNTreeEdit()
	{	CalcExtent(m_sizeExtent);
	    h_tree = NULL ;
		BoolInit = FALSE;
		m_bWindowOnly = TRUE;

		m_BoolSaveFlag = FALSE;
		boolClearAll = TRUE;
		m_SaveCurrentFolder = FALSE;
		m_EditTreeItem = NULL;
		m_bDragging = FALSE;
		m_TreeBkColor = ::GetSysColor(COLOR_WINDOW);
		m_TreeTextColor = ::GetSysColor(COLOR_WINDOWTEXT);
        hPlusBitmap = LoadImage(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_PLUS),IMAGE_BITMAP,16,16,0);
        m_MinusBitmap = LoadImage(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_MINUS),IMAGE_BITMAP,16,16,0);
        hImageList =  ImageList_Create(TCX_ICON, TCY_ICON, ILC_MASK, TNUM_ICONS, 0); 
		mi_nClose =	AddIconsToImageList(IDI_ICON_CLOSE);
		mi_nOpen = 	AddIconsToImageList(IDI_ICON_OPEN);
		mi_Document = AddIconsToImageList(IDI_ICON_LINK);
		mi_RootPersonalLink = AddIconsToImageList(IDI_ICON_PERSONAL_LINK);

	}
	~CNTreeEdit()
	{
   		ImageList_Destroy(hImageList);
		DeleteObject(hPlusBitmap);
		DeleteObject(m_MinusBitmap);
  
	}


// ISupportsErrorInfo
/*	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* arr[] =
		{
			&IID_INTreeEdit,
		};
		for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
		{
			if (InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}
*/

	STDMETHOD(OnAmbientPropertyChange)(DISPID dispid)
	{
        ATLTRACE(_T("OnAmbientPropertyChange\n"));
		if (dispid == DISPID_TEXT)
		{
			SetTextParam();
		}
		if (dispid == DISPID_AMBIENT_BACKCOLOR)
		{
			SetBackgroundColorFromAmbient();
			FireViewChange();
		}
		return IOleControlImpl<CNTreeEdit>::OnAmbientPropertyChange(dispid);
	}



// IViewObjectEx
//	DECLARE_VIEW_STATUS(0)
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

private:
	VOID GetActiveFolderName();
	CComBSTR m_cbstrCurrentURL;
	CComBSTR m_cbstrCurrentName;
	int LenStectItem;
	HTREEITEM SteckItem[20];
	long mi_Document;
	BOOL boolClearAll;
// INTreeEdit
public:
	STDMETHOD(get_TreeTextColor)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_TreeTextColor)(/*[in]*/ long newVal);
	STDMETHOD(get_TreeBkColor)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_TreeBkColor)(/*[in]*/ long newVal);
	STDMETHOD(Refresh)();
	STDMETHOD(get_URL)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_URL)(/*[in]*/ BSTR newVal);
	CComPtr<IPictureDisp> m_pPicture;
	CComBSTR m_bstrText;

	enum { IDD = IDD_NTREEEDIT };
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		ResizeWindowPanel();
		// TODO : Add Code for message handler. Call DefWindowProc if necessary.
		return 0;
	}

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnItemexpandedTree_ctrl(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
	{
	HTREEITEM	hti;

	HWND thWnd = h_tree;
    

	 NMTREEVIEW * pnmtv = (NMTREEVIEW *) pnmh; 
 
       hti = (HTREEITEM)(pnmtv->itemNew).hItem; 

		TestFolderIcon(hti);
		TestChildFolderIcon(hti);
		return 0;
	}
	LRESULT OnClickedBtn_plus(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
        ExpandAllW(TVE_EXPAND);
        ::SetFocus(h_tree);
		return 0;
	}
	LRESULT OnClickedBtn_collapse(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		ExpandAllW(TVE_COLLAPSE);
        ::SetFocus(h_tree);
		return 0;
	}


 


	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{


	if (m_wndToolTip.m_hWnd)
	{
		POINT pt;
		static uId;
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);

		TOOLINFO ti;
		ti.cbSize = sizeof(TOOLINFO);
		ti.hwnd   = m_hTheWnd;
		ti.uId    = 1;
		ti.rect.left   = pt.x;
		ti.rect.right  = pt.x+1;
		ti.rect.top    = pt.y;
		ti.rect.bottom = pt.y+1;
		m_wndToolTip.SendMessage(TTM_NEWTOOLRECT,   0, (LPARAM)&ti);
		
		RelayEvent(uMsg, wParam, lParam);
	}
	return 0;


   #define X_OFFSET 15
   #define Y_OFFSET X_OFFSET      
   POINT pnt ;

   HTREEITEM h_item = NULL ;
   	HWND hwndTV = h_tree;
   long yCur = GET_Y_LPARAM(lParam) ;
   long xCur = GET_X_LPARAM(lParam) ;
   pnt.x = xCur ;
   pnt.y = yCur;
      ::ClientToScreen(hwndTV, &pnt) ;
      TVHITTESTINFO tv_ht ;
      ZeroMemory(&tv_ht, sizeof(TVHITTESTINFO)) ;
      tv_ht.flags = TVHT_ONITEM ;
      tv_ht.pt.x = pnt.x ;
      tv_ht.pt.y = pnt.y ;
      ::ScreenToClient(hwndTV, &(tv_ht.pt)) ;
      h_item = (HTREEITEM)::SendMessage(hwndTV, TVM_HITTEST, 0, (LPARAM)&tv_ht) ;
	  if ( h_item != NULL ) {
		  //  TTM_TRACKPOSITION 
          //  TTM_TRACKACTIVATE 
		  // TTM_UPDATETIPTEXT
		  // TTM_ACTIVATE

// ----- tracking toolstip ------

        SendMessage(h_treeToolTip,
                    TTM_TRACKPOSITION,
                    0,
                    (LPARAM)MAKELPARAM(GET_X_LPARAM(lParam) + X_OFFSET,
                                       GET_Y_LPARAM(lParam) + Y_OFFSET));
      
//-------------------------------

	  }else {
	  }


		return 0;
	}
	LRESULT OnDblclkTree_ctrl(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
	{
//	     m_cbstrCurrentURL = ParStr;
//         m_cbstrCurrentName = strTemp;

		if (m_cbstrCurrentURL.Length() > 2 ){
	    	Fire_DbClick(m_cbstrCurrentURL,m_cbstrCurrentName);
		}

		return 0;
	}

	LRESULT OnShowWindow(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{


		// TODO : Add Code for message handler. Call DefWindowProc if necessary.
		return 0;
	}
	LRESULT OnSelchangedTree_ctrl(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
	{
	 LPNMTREEVIEW lpnmtv = (NMTREEVIEW *) pnmh; 
 

//	*pResult = 0;
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*) pnmh;

	//
	// Do nothing if the user is attempting to drag a top-level item.
	//
	HTREEITEM hItem = pNMTreeView->itemNew.hItem;
         TreeView_SelectDropTarget(h_tree,NULL);
         TreeView_SelectDropTarget(h_tree,pNMTreeView->itemNew.hItem);

//-----

	    TVITEM tvi_Sourse;
		



		char strTemp[255];
		strTemp[0]=0;

        tvi_Sourse.mask = 
            TVIF_IMAGE |  
            TVIF_PARAM |
            TVIF_STATE | TVIF_SELECTEDIMAGE |
            TVIF_TEXT ;


        tvi_Sourse.hItem = hItem; 
        tvi_Sourse.pszText = strTemp; 
        tvi_Sourse.cchTextMax = 250; 
		TreeView_GetItem(h_tree, &tvi_Sourse); 
//-----
		 m_EditTreeItem = hItem;
        char * ParStr = (LPSTR)tvi_Sourse.lParam;
	     m_cbstrCurrentURL = ParStr;
         m_cbstrCurrentName = strTemp;
		 Fire_SelectItem(m_cbstrCurrentURL,m_cbstrCurrentName);
		 GetActiveFolderName();

		return 0;
	}
	LRESULT OnDeleteitemTree_ctrl(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
	{
	m_EditTreeItem = NULL;
	 LPNMTREEVIEW lpnmtv = (NMTREEVIEW *) pnmh; 
 

//	*pResult = 0;
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*) pnmh;

	//
	// Do nothing if the user is attempting to drag a top-level item.
	//
	HTREEITEM hItem = pNMTreeView->itemOld.hItem;
//         TreeView_SelectDropTarget(h_tree,NULL);

//-----

	    TVITEM tvi_Sourse;
		



		char strTemp[255];
		strTemp[0]=0;

        tvi_Sourse.mask = 
            TVIF_IMAGE |  
            TVIF_PARAM |
            TVIF_STATE | TVIF_SELECTEDIMAGE |
            TVIF_TEXT ;


        tvi_Sourse.hItem = hItem; 
        tvi_Sourse.pszText = strTemp; 
        tvi_Sourse.cchTextMax = 250; 
		TreeView_GetItem(h_tree, &tvi_Sourse); 
//-----
        LPSTR ParStr = (LPSTR)tvi_Sourse.lParam;
        free(ParStr);

		return 0;
	}
	LRESULT OnClickTree_ctrl(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
	{
		// TODO : Add Code for control notification handler.
		return 0;
	}
	LRESULT OnNcMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
        ATLTRACE(_T("OnNcMouseMove\n"));
		return 0;
	}
};

#endif //__NTREEEDIT_H_
