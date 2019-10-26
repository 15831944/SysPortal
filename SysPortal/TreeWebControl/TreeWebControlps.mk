
TreeWebControlps.dll: dlldata.obj TreeWebControl_p.obj TreeWebControl_i.obj
	link /dll /out:TreeWebControlps.dll /def:TreeWebControlps.def /entry:DllMain dlldata.obj TreeWebControl_p.obj TreeWebControl_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del TreeWebControlps.dll
	@del TreeWebControlps.lib
	@del TreeWebControlps.exp
	@del dlldata.obj
	@del TreeWebControl_p.obj
	@del TreeWebControl_i.obj
