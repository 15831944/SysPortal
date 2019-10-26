// DownloadData.h: interface for the CDownloadData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOWNLOADDATA_H__8F757521_DFC4_11D3_9F4B_005004816FFF__INCLUDED_)
#define AFX_DOWNLOADDATA_H__8F757521_DFC4_11D3_9F4B_005004816FFF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include<wininet.h>

class CDownloadData  
{
public:
	long LenData;
	long GetURL_ASP(LPSTR lpstrHost,LPSTR lpstrURL);
	CDownloadData();
	char *pData;
	virtual ~CDownloadData();

};

#endif // !defined(AFX_DOWNLOADDATA_H__8F757521_DFC4_11D3_9F4B_005004816FFF__INCLUDED_)
