// PanelMenuProp.cpp : Implementation of CPanelMenuProp
#include "stdafx.h"
#include "PanelMenuProp.h"






/////////////////////////////////////////////////////////////////////////////
// CPanelMenuProp

VOID CPanelMenuProp::SaveParameters(VOID)
{
	char BufText[255];
  CRegisterSave Reg;


	HWND hWndDlg;
	hWndDlg = GetDlgItem(IDC_EDIT_GROUP_FOLDER);

    ::GetWindowText(hWndDlg,BufText,254);

  Reg.UserKeyStore("Group folder",BufText,strlen(BufText),CRegisterSave::WRITE);

	hWndDlg = GetDlgItem(IDC_COMBO_UPDATE);


	  int CurSel = ::SendMessage(GetDlgItem(IDC_COMBO_UPDATE), CB_GETCURSEL, 
            0, (LPARAM) 0); 

    char M[2];
	M[0]='0'+CurSel;
	M[1]=0;
    Reg.UserKeyStore("Time update",M,1,CRegisterSave::WRITE);

	int ret;
	  ret = SendDlgItemMessage(IDC_RADIO_INTERNET_EXPLORER, BM_GETCHECK , 0, 0);
  if (ret == 0 ){
	  Reg.UserKeyStore("IExplorer",_T("false"),5,CRegisterSave::WRITE);
  }else {
	  Reg.UserKeyStore("IExplorer",_T("true"),4,CRegisterSave::WRITE);
  }



	  ret = SendDlgItemMessage(IDC_RADIO_NETSCAPE, BM_GETCHECK , 0, 0);
  if (ret == 0 ){
	  Reg.UserKeyStore("Netscape",_T("false"),5,CRegisterSave::WRITE);
  }else {
	  Reg.UserKeyStore("Netscape",_T("true"),4,CRegisterSave::WRITE);
  }



	  ret = SendDlgItemMessage(IDC_RADIO_SYSTEM_DEFAULT_BROWSER, BM_GETCHECK , 0, 0);
  if (ret == 0 ){
	  Reg.UserKeyStore("Default browser",_T("false"),5,CRegisterSave::WRITE);
  }else {
	  Reg.UserKeyStore("Default browser",_T("true"),4,CRegisterSave::WRITE);
  }



	  ret = SendDlgItemMessage(IDC_RADIO_NEW_WINDOW, BM_GETCHECK , 0, 0);
  if (ret == 0 ){
	  Reg.UserKeyStore("New Window",_T("false"),5,CRegisterSave::WRITE);
  }else {
	  Reg.UserKeyStore("New Window",_T("true"),4,CRegisterSave::WRITE);
  }

	  ret = SendDlgItemMessage(IDC_RADIO_ACTIVE_WINDOW, BM_GETCHECK , 0, 0);
  if (ret == 0 ){
	  Reg.UserKeyStore("Active Window",_T("false"),5,CRegisterSave::WRITE);
  }else {
	  Reg.UserKeyStore("Active Window",_T("true"),4,CRegisterSave::WRITE);
  }


	  ret = SendDlgItemMessage(IDC_CHECK_RANDOM, BM_GETCHECK , 0, 0);
  if (ret == 0 ){
	  Reg.UserKeyStore("Random Update",_T("false"),5,CRegisterSave::WRITE);
  }else {
	  Reg.UserKeyStore("Random Update",_T("true"),4,CRegisterSave::WRITE);
  }




}
