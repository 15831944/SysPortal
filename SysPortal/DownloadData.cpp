// DownloadData.cpp: implementation of the CDownloadData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DownloadData.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


    



CDownloadData::CDownloadData()
{
 pData = NULL;
 LenData = 0;
}

CDownloadData::~CDownloadData()
{
	if (pData != NULL){
		GlobalFree(pData);
	}
}

long CDownloadData::GetURL_ASP(LPSTR lpstrHost,LPSTR lpstrURL)
{

    HINTERNET hSession = InternetOpen("SysPortal",
                                      INTERNET_OPEN_TYPE_PRECONFIG,
                                      NULL,
                                      NULL,
                                      0);

	if (hSession == NULL){return 0;}
    HINTERNET hConnection = InternetConnect(hSession, 
                                            lpstrHost,  // Server
                                            INTERNET_DEFAULT_HTTP_PORT,
                                            NULL,     // Username
                                            NULL,     // Password
                                            INTERNET_SERVICE_HTTP,
                                            0,        // Synchronous
                                            NULL);    // No Context

	if (hConnection == NULL){return 0;}
    HINTERNET hRequest = HttpOpenRequest(hConnection, 
                                         "GET",
                                         lpstrURL,
                                         NULL,    // Default HTTP Version
                                         NULL,    // No Referer
                                         (const char**)"*/*\0", // Accept
                                                                // anything
                                         0,       // Flags
                                         NULL);   // No Context
	if (hRequest == NULL){return 0;}
    HttpSendRequest(hRequest,
                    NULL,    // No extra headers
                    0,       // Header length
                    NULL,    // No Body
                    0);      // Body length

	char *pCopyPtr;

	if (pData != NULL){
		GlobalFree(pData);
	}

        pData = (char*)GlobalAlloc(GMEM_FIXED, 1500);
		long MaxBuf;
		MaxBuf = 1500;
		LenData = 0;
        DWORD dwBytesRead = 1;
        while (dwBytesRead)
        {
			if ((MaxBuf - LenData) < 1024){
				pCopyPtr = pData;
				MaxBuf +=2048;
                pData = (char*)GlobalAlloc(GMEM_FIXED, MaxBuf);
				strncpy(pData,pCopyPtr,LenData);
				pData[LenData]=0;
				GlobalFree(pCopyPtr);
			}
            InternetReadFile(hRequest, &pData[LenData], 1024, &dwBytesRead);
			LenData = LenData + dwBytesRead;
            pData[LenData] = 0;
        }

		InternetCloseHandle(hRequest);
		InternetCloseHandle(hConnection);
		InternetCloseHandle(hSession);

  		return LenData;

}
