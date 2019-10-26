// MSystemConfig.cpp: implementation of the CMSystemConfig class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sysportal.h"
#include "MSystemConfig.h"
#include "RegisterSave.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMSystemConfig::CMSystemConfig()
{

}

CMSystemConfig::~CMSystemConfig()
{

}

VOID CMSystemConfig::Load(VOID)
{

  CRegisterSave Reg;
  char BufR[100];


Reg.UserKeyStore("Lock line",BufR,50,CRegisterSave::READ);
  if (strcmp(BufR,_T("true"))== 0 ) {
	LockLine = TRUE;
  } else {
	LockLine = FALSE;
  }

  Reg.UserKeyStore("Line ACCELERATE",BufR,50,CRegisterSave::READ);
  if (strcmp(BufR,_T("true"))== 0 ) {
      LineACCELERATE = TRUE;
  } else {
      LineACCELERATE = FALSE;
  }

}
