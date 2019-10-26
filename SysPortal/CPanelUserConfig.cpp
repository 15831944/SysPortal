// CPanelUserConfig.cpp : Implementation of CCPanelUserConfig
#include "stdafx.h"
#include "CPanelUserConfig.h"
#include "RegisterSave.h"

/////////////////////////////////////////////////////////////////////////////
// CCPanelUserConfig
LRESULT CCPanelUserConfig::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{

  CRegisterSave Reg;
char AccountName[255];

DWORD cbDomainName;
char DomainName[255];
SID_NAME_USE SIDType = SidTypeUser;
unsigned long lSid = 255;

cbDomainName = 255;
DomainName[0]=0;


GetUserName(AccountName,&cbDomainName);
  

HWND hWndDlg;
hWndDlg = GetDlgItem(IDC_USER_NAME);

       ::SetWindowText(hWndDlg,AccountName);

DomainName[0]=0;

cbDomainName = 255;
 GetComputerName(
  DomainName,  
  &cbDomainName);

 hWndDlg = GetDlgItem(IDC_EDIT_COMPUTER_NAME);
       ::SetWindowText(hWndDlg,DomainName);


cbDomainName = 255;
DomainName[0]=0;

//  Workgroup
//  Comment

        char s_cszDebugKey[255];
		char CommentVal[255];
   		HKEY hkeyRun;
		DWORD dwType;
		const char s_ValueName[] = _T("Workgroup");
		const char s_Comment[] = _T("Comment");
		unsigned long LenRead;
		LenRead = 200;
  strcpy((char *)s_cszDebugKey,_T("System\\CurrentControlSet\\Services\\VxD\\VNETSUP"));
  RegOpenKeyEx(HKEY_LOCAL_MACHINE,s_cszDebugKey,0,KEY_READ,&hkeyRun);
  RegQueryValueEx(hkeyRun,s_ValueName,NULL,&dwType,(unsigned char *)DomainName,&LenRead);
  LenRead = 200;
  RegQueryValueEx(hkeyRun,s_Comment,NULL,&dwType,(unsigned char *)CommentVal,&LenRead);
  RegCloseKey(hkeyRun);




 hWndDlg = GetDlgItem(IDC_EDIT_HOST_NAME);
       ::SetWindowText(hWndDlg,DomainName);


 		return 1;  // Let the system set the focus
	}


VOID CCPanelUserConfig::SaveParameters(VOID)
{

}
