// MSystemConfig.h: interface for the CMSystemConfig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSYSTEMCONFIG_H__DB5AE651_1F8D_11D4_86C9_00409501EE6E__INCLUDED_)
#define AFX_MSYSTEMCONFIG_H__DB5AE651_1F8D_11D4_86C9_00409501EE6E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMSystemConfig  
{
public:
	BOOL LineACCELERATE;
	BOOL LockLine;
	VOID Load(VOID);
	CMSystemConfig();
	virtual ~CMSystemConfig();

};

#endif // !defined(AFX_MSYSTEMCONFIG_H__DB5AE651_1F8D_11D4_86C9_00409501EE6E__INCLUDED_)
