// MSteck.h: interface for the CMSteck class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSTECK_H__206A1E30_E2C0_11D3_9F4B_005004816FFF__INCLUDED_)
#define AFX_MSTECK_H__206A1E30_E2C0_11D3_9F4B_005004816FFF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define MAX_MSTECK 500
class CMSteck  
{
public:
	struct Arr{
		char name[255];
	};
	BOOL Restore(char *var);
	BOOL Save(char *var);
	CMSteck();
	virtual ~CMSteck();

private:
	Arr Buf[MAX_MSTECK];
	long stkLen;
};

#endif // !defined(AFX_MSTECK_H__206A1E30_E2C0_11D3_9F4B_005004816FFF__INCLUDED_)
