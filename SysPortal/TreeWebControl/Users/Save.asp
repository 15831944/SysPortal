<%@ LANGUAGE="VBSCRIPT" %>
<% 
   'Increase Script Timeout to 10 hours
   Server.ScriptTimeout = 36000

   'Get size of POST data
   PostSize = Request.TotalBytes
  dim allpost
  allpost = ""
   'Read POST data in 1K chunks
   BytesRead = 0	
   For i = 0 to (PostSize/1024)
     if ((i+1)*1024) > PostSize then
       ReadSize=PostSize - i*1024
     else
       ReadSize=1024
     end if
     PostData = Request.BinaryRead(ReadSize)
     BytesRead = BytesRead + ReadSize	
'     allpost = allpost & PostData 
   Next
   
   

   ' Send results back to client
   Response.Write PostSize
   Response.Write " all size, "
   Response.Write BytesRead
   Response.Write " bytes were read." & chr(13)
  ' Response.Write allpost
%>
