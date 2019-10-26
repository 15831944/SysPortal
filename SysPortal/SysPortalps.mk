
SysPortalps.dll: dlldata.obj SysPortal_p.obj SysPortal_i.obj
	link /dll /out:SysPortalps.dll /def:SysPortalps.def /entry:DllMain dlldata.obj SysPortal_p.obj SysPortal_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del SysPortalps.dll
	@del SysPortalps.lib
	@del SysPortalps.exp
	@del dlldata.obj
	@del SysPortal_p.obj
	@del SysPortal_i.obj
