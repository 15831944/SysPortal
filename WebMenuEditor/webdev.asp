<% @LANGUAGE="JScript" %>
<%
	var sXml = "webdev.xml"
	var sXsl = new String(Request.QueryString("xsl"));
	if ("undefined" == sXsl) sXsl = "list.xsl"
	
	var oXmlDoc = Server.CreateObject("MICROSOFT.XMLDOM");
	var oXslDoc = Server.CreateObject("MICROSOFT.XMLDOM");
	oXmlDoc.async = false;
	oXslDoc.async = false;
	oXmlDoc.load(Server.MapPath(sXml));
	oXslDoc.load(Server.MapPath(sXsl));
	Response.Write(oXmlDoc.transformNode(oXslDoc));	
%>