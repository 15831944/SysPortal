// DAsyncFile.cpp: implementation of the CDAsyncFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <afxole.h>
#include "DAsyncFile.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDAsyncFile::CDAsyncFile()
{

}

CDAsyncFile::~CDAsyncFile()
{

}

void CDAsyncFile::OnDataAvailable(DWORD dwSize, DWORD bscfFlag)
{
   if ((bscfFlag & BSCF_FIRSTDATANOTIFICATION) != 0)
   {
      m_dwReadBefore = 0;
      m_strText.Empty();
   }

   DWORD dwArriving = dwSize - m_dwReadBefore;

   if (dwArriving > 0)
   {
      int nLen = m_strText.GetLength();
      ASSERT(nLen == m_dwReadBefore);
      LPTSTR psz = m_strText.GetBuffer(nLen + dwArriving);
      Read(psz + nLen, dwArriving);
      m_strText.ReleaseBuffer(nLen + dwArriving);
      m_dwReadBefore = dwSize;
      GetControl()->Invalidate();
   }
}