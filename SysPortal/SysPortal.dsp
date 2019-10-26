# Microsoft Developer Studio Project File - Name="SysPortal" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=SysPortal - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SysPortal.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SysPortal.mak" CFG="SysPortal - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SysPortal - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "SysPortal - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE "SysPortal - Win32 Release MinSize" (based on "Win32 (x86) Application")
!MESSAGE "SysPortal - Win32 Release MinDependency" (based on "Win32 (x86) Application")
!MESSAGE "SysPortal - Win32 Unicode Release MinSize" (based on "Win32 (x86) Application")
!MESSAGE "SysPortal - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SysPortal - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x40d /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib Ws2_32.lib comctl32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wininet.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Install/SysPortal.exe" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Performing registration
OutDir=.\Debug
TargetPath=.\Install\SysPortal.exe
InputPath=.\Install\SysPortal.exe
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "SysPortal - Win32 Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugU"
# PROP BASE Intermediate_Dir "DebugU"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugU"
# PROP Intermediate_Dir "DebugU"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x40d /d "_DEBUG"
# ADD RSC /l 0x40d /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /pdbtype:sept
# Begin Custom Build - Performing registration
OutDir=.\DebugU
TargetPath=.\DebugU\SysPortal.exe
InputPath=.\DebugU\SysPortal.exe
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode EXE on Windows 95 
	:end 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "SysPortal - Win32 Release MinSize"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinSize"
# PROP BASE Intermediate_Dir "ReleaseMinSize"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMinSize"
# PROP Intermediate_Dir "ReleaseMinSize"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x40d /d "NDEBUG"
# ADD RSC /l 0x40d /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib comctl32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wininet.lib /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Performing registration
OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\SysPortal.exe
InputPath=.\ReleaseMinSize\SysPortal.exe
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "SysPortal - Win32 Release MinDependency"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinDependency"
# PROP BASE Intermediate_Dir "ReleaseMinDependency"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMinDependency"
# PROP Intermediate_Dir "ReleaseMinDependency"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x40d /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib comctl32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wininet.lib /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Performing registration
OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\SysPortal.exe
InputPath=.\ReleaseMinDependency\SysPortal.exe
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "SysPortal - Win32 Unicode Release MinSize"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseUMinSize"
# PROP BASE Intermediate_Dir "ReleaseUMinSize"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseUMinSize"
# PROP Intermediate_Dir "ReleaseUMinSize"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x40d /d "NDEBUG"
# ADD RSC /l 0x40d /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# Begin Custom Build - Performing registration
OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\SysPortal.exe
InputPath=.\ReleaseUMinSize\SysPortal.exe
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode EXE on Windows 95 
	:end 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "SysPortal - Win32 Unicode Release MinDependency"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseUMinDependency"
# PROP BASE Intermediate_Dir "ReleaseUMinDependency"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseUMinDependency"
# PROP Intermediate_Dir "ReleaseUMinDependency"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x40d /d "NDEBUG"
# ADD RSC /l 0x40d /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# Begin Custom Build - Performing registration
OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\SysPortal.exe
InputPath=.\ReleaseUMinDependency\SysPortal.exe
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode EXE on Windows 95 
	:end 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "SysPortal - Win32 Debug"
# Name "SysPortal - Win32 Unicode Debug"
# Name "SysPortal - Win32 Release MinSize"
# Name "SysPortal - Win32 Release MinDependency"
# Name "SysPortal - Win32 Unicode Release MinSize"
# Name "SysPortal - Win32 Unicode Release MinDependency"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CPanelUserConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogProp.cpp
# End Source File
# Begin Source File

SOURCE=.\DownloadData.cpp
# End Source File
# Begin Source File

SOURCE=.\Exit.cpp
# End Source File
# Begin Source File

SOURCE=.\MServerComponent.cpp
# End Source File
# Begin Source File

SOURCE=.\MSteck.cpp
# End Source File
# Begin Source File

SOURCE=.\MSystemConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\PanelInternetOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\PanelMenuProp.cpp
# End Source File
# Begin Source File

SOURCE=.\RegisterSave.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SysPortal.cpp
# End Source File
# Begin Source File

SOURCE=.\SysPortal.idl
# ADD MTL /tlb ".\SysPortal.tlb" /h "SysPortal.h" /iid "SysPortal_i.c" /Oicf
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CPanelUserConfig.h
# End Source File
# Begin Source File

SOURCE=.\DialogProp.h
# End Source File
# Begin Source File

SOURCE=.\DownloadData.h
# End Source File
# Begin Source File

SOURCE=.\Exit.h
# End Source File
# Begin Source File

SOURCE=.\MServerComponent.h
# End Source File
# Begin Source File

SOURCE=.\MSteck.h
# End Source File
# Begin Source File

SOURCE=.\MSystemConfig.h
# End Source File
# Begin Source File

SOURCE=.\PanelInternetOptions.h
# End Source File
# Begin Source File

SOURCE=.\PanelMenuProp.h
# End Source File
# Begin Source File

SOURCE=.\RegisterSave.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\StructMenu.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\images\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\images\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\images\bitmap_t.bmp
# End Source File
# Begin Source File

SOURCE=.\images\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\images\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\images\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\images\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=.\images\bmp00005.bmp
# End Source File
# Begin Source File

SOURCE=.\images\bmp00006.bmp
# End Source File
# Begin Source File

SOURCE=.\IMAGES\bollon.bmp
# End Source File
# Begin Source File

SOURCE=.\Images\books.bmp
# End Source File
# Begin Source File

SOURCE=.\images\cabview.ico
# End Source File
# Begin Source File

SOURCE=.\images\check.bmp
# End Source File
# Begin Source File

SOURCE=.\IMAGES\close.bmp
# End Source File
# Begin Source File

SOURCE=.\Images\comment.bmp
# End Source File
# Begin Source File

SOURCE=.\IMAGES\config.bmp
# End Source File
# Begin Source File

SOURCE=.\IMAGES\DATABASE.BMP
# End Source File
# Begin Source File

SOURCE=.\Images\default_.bmp
# End Source File
# Begin Source File

SOURCE=.\DispRes.ico
# End Source File
# Begin Source File

SOURCE=.\IMAGES\edit_per.bmp
# End Source File
# Begin Source File

SOURCE=.\Images\Entirnet.ico
# End Source File
# Begin Source File

SOURCE=.\Images\explorer.bmp
# End Source File
# Begin Source File

SOURCE=.\Images\find_dlg.bmp
# End Source File
# Begin Source File

SOURCE=.\Images\FindLink.bmp
# End Source File
# Begin Source File

SOURCE=.\Images\handico.bmp
# End Source File
# Begin Source File

SOURCE=.\images\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\Images\icon3.ico
# End Source File
# Begin Source File

SOURCE=.\IMAGES\IDB_CHECK.bmp
# End Source File
# Begin Source File

SOURCE=.\IMAGES\IDB_ITEMDEFAULT_N.bmp
# End Source File
# Begin Source File

SOURCE=.\IMAGES\IDB_NEXT.bmp
# End Source File
# Begin Source File

SOURCE=.\IMAGES\iIDB_ITEMDEFAULT.bmp
# End Source File
# Begin Source File

SOURCE=.\Images\internet.bmp
# End Source File
# Begin Source File

SOURCE=.\images\intranet.bmp
# End Source File
# Begin Source File

SOURCE=.\Images\isdn_fix.bmp
# End Source File
# Begin Source File

SOURCE=.\Images\israel.bmp
# End Source File
# Begin Source File

SOURCE=.\images\itemdefa.bmp
# End Source File
# Begin Source File

SOURCE=.\images\itemmask.bmp
# End Source File
# Begin Source File

SOURCE=.\Images\Link.ico
# End Source File
# Begin Source File

SOURCE=.\IMAGES\liveupda.bmp
# End Source File
# Begin Source File

SOURCE=.\images\localmen.bmp
# End Source File
# Begin Source File

SOURCE=.\IMAGES\menu_sam.bmp
# End Source File
# Begin Source File

SOURCE=.\Images\MenuOpt.ico
# End Source File
# Begin Source File

SOURCE=.\images\mercury.ico
# End Source File
# Begin Source File

SOURCE=.\IMAGES\minus.bmp
# End Source File
# Begin Source File

SOURCE=.\Images\netscape.bmp
# End Source File
# Begin Source File

SOURCE=.\IMAGES\next.bmp
# End Source File
# Begin Source File

SOURCE=.\IMAGES\next_s.bmp
# End Source File
# Begin Source File

SOURCE=.\Images\Nodrop01.cur
# End Source File
# Begin Source File

SOURCE=.\Images\Nodrop02.cur
# End Source File
# Begin Source File

SOURCE=.\Images\Openfold.ico
# End Source File
# Begin Source File

SOURCE=.\Images\personal.bmp
# End Source File
# Begin Source File

SOURCE=.\Images\PLinkDLG.bmp
# End Source File
# Begin Source File

SOURCE=.\IMAGES\plus.bmp
# End Source File
# Begin Source File

SOURCE=.\IMAGES\Postl.ico
# End Source File
# Begin Source File

SOURCE=.\IMAGES\prev.bmp
# End Source File
# Begin Source File

SOURCE=.\Images\public_l.bmp
# End Source File
# Begin Source File

SOURCE=.\Images\Remteacc.ico
# End Source File
# Begin Source File

SOURCE=.\IMAGES\selectin.bmp
# End Source File
# Begin Source File

SOURCE=.\IMAGES\SysPortal.ICO
# End Source File
# Begin Source File

SOURCE=.\SysPortal.rc
# End Source File
# Begin Source File

SOURCE=.\SysPortal.rgs
# End Source File
# Begin Source File

SOURCE=.\Images\usa.bmp
# End Source File
# Begin Source File

SOURCE=.\Images\user.bmp
# End Source File
# Begin Source File

SOURCE=.\IMAGES\user_opt.ico
# End Source File
# Begin Source File

SOURCE=.\Images\workgr_dlg.bmp
# End Source File
# Begin Source File

SOURCE=.\Images\workgrou.bmp
# End Source File
# End Group
# End Target
# End Project
# Section SysPortal : {002F59CC-7463-006C-6C00-2E0063007400}
# 	1:20:IDD_CPANELUSERCONFIG:107
# End Section
# Section SysPortal : {006941C8-7463-006C-2D00-2D007E490000}
# 	1:14:IDD_TREEEDITOR:108
# End Section
# Section SysPortal : {00691570-7463-006C-005C-47616C6C6572}
# 	1:14:IDD_DIALOGPROP:101
# End Section
# Section SysPortal : {00000000-0000-0000-0000-800000800000}
# 	1:8:IDD_EXIT:109
# End Section
# Section SysPortal : {74632E6E-006C-002E-6300-74006C000000}
# 	1:24:IDD_PANELINTERNETOPTIONS:106
# End Section
