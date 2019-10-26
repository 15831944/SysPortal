// MSteck.cpp: implementation of the CMSteck class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MSteck.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMSteck::CMSteck()
{
 stkLen = 0;
}

CMSteck::~CMSteck()
{

}

BOOL CMSteck::Save(char *var)
{
	if (stkLen == MAX_MSTECK){
		return FALSE;
	} else {
      stkLen++;
      strcpy(Buf[stkLen-1].name,var);
	return TRUE;
	}
}

BOOL CMSteck::Restore(char *var)
{
	if (stkLen > 0 ){
		strcpy(var,Buf[stkLen-1].name);
		stkLen--;
      return TRUE;
	}else
	{ return FALSE;
	}
}
