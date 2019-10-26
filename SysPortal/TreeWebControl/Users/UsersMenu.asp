<%@ LANGUAGE="VBSCRIPT" %>
<% 
   'Increase Script Timeout to 10 hours
   Server.ScriptTimeout = 36000
   User = Request.QueryString 
   Const ForReading = 1, ForWriting = 2, ForAppending = 8
   Dim fso, MyFile
   Set fso = CreateObject("Scripting.FileSystemObject")
   'Set MyFile = fso .CreateTextFile("testfile.txt", True)
   Set MyFile = fso.OpenTextFile("c:\testfile.txt", ForWriting,True)
  
'   MyFile.WriteLine("This is a test.")
   MyFile.Close

%>
