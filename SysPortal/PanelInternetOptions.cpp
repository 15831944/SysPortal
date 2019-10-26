// PanelInternetOptions.cpp : Implementation of CPanelInternetOptions
#include "stdafx.h"
#include "PanelInternetOptions.h"

/////////////////////////////////////////////////////////////////////////////
// CPanelInternetOptions

extern HANDLE threadDD;
extern VOID ThreadFunc(LPVOID);

extern DWORD threadID;

VOID CPanelInternetOptions::SavePatameters()
{
  CRegisterSave Reg;
  LRESULT ret;
  ret = SendDlgItemMessage(IDC_CHECKISDN, BM_GETCHECK , 0, 0);
  if (ret == 0 ){
	  Reg.UserKeyStore("Lock line",_T("false"),5,CRegisterSave::WRITE);
	  if (threadDD != NULL ){
          TerminateThread(
            threadDD,    // handle to the thread
           0 );
		  threadDD = NULL;
	  }

  }else {
	  Reg.UserKeyStore("Lock line",_T("true"),4,CRegisterSave::WRITE);
	     if ( threadDD == NULL ){
	        threadDD = CreateThread(0, 0,(LPTHREAD_START_ROUTINE) ThreadFunc,
                     0, 0, &threadID);
		 }

  }


  ret = SendDlgItemMessage(IDC_ACCELERATE, BM_GETCHECK , 0, 0);
  if (ret == 0 ){
	  Reg.UserKeyStore("Line ACCELERATE",_T("false"),5,CRegisterSave::WRITE);
  }else {
	  Reg.UserKeyStore("Line ACCELERATE",_T("true"),4,CRegisterSave::WRITE);
  }

}
