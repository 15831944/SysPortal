//---------------------------------------------------------------------------
//  DLLSTUFF - Windows DLL support functions
//
//---------------------------------------------------------------------------


#include "windows.h"

//---------------------------------------------------------------------------
// Function declarations
//---------------------------------------------------------------------------

int   #ifdef WIN32
BOOL CALLBACK LibMain(HANDLE hModule, DWORD dwReason, LPVOID lpReserved);
#else
int FAR PASCAL LibMain(HANDLE hModule, WORD wDataSeg, WORD cbHeapSize, LPSTR lpszCmdLine);
#endif

int   FAR PASCAL WEP (int bSystemExit);

//---------------------------------------------------------------------------
// Global Variables...
//---------------------------------------------------------------------------

HANDLE	hInstance;		// Global instance handle for  DLL

//---------------------------------------------------------------------------
// LibMain
//---------------------------------------------------------------------------
int   #ifdef WIN32
BOOL CALLBACK LibMain(HANDLE hModule, DWORD dwReason, LPVOID lpReserved)
#else
int FAR PASCAL LibMain(HANDLE hModule, WORD wDataSeg, WORD cbHeapSize, LPSTR lpszCmdLine);
#endif
{
    hInstance = hModule;
    return 1;
}

#pragma alloc_text(FIXEDSEG, WEP)

//---------------------------------------------------------------------------
// WEP
//---------------------------------------------------------------------------
int FAR PASCAL WEP (int bSystemExit)
{
    return(1);
}
