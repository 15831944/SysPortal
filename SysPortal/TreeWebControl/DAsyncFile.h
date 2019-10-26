// DAsyncFile.h: interface for the CDAsyncFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DASYNCFILE_H__1C1B5A06_5AFC_11D4_9F4B_005004816FFF__INCLUDED_)
#define AFX_DASYNCFILE_H__1C1B5A06_5AFC_11D4_9F4B_005004816FFF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDAsyncFile : public CAsyncMonikerFile  
{
public:
	CDAsyncFile();
	virtual void CDAsyncFile::OnDataAvailable(DWORD dwSize, DWORD bscfFlag)
	virtual ~CDAsyncFile();

};

#endif // !defined(AFX_DASYNCFILE_H__1C1B5A06_5AFC_11D4_9F4B_005004816FFF__INCLUDED_)
