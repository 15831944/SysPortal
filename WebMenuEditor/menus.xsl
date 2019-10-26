<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl">

<!-- MENUS.XSL -->

<xsl:template match="/">
	<HTML>
	<HEAD>
	<TITLE>Menu <xsl:value-of select="TOPICLIST/@TYPE" /></TITLE>
	<LINK REL="stylesheet" TYPE="text/css" HREF="menus.css" />
	<SCRIPT LANGUAGE="JScript" SRC="menus.js"></SCRIPT>
	</HEAD>
	<BODY>
	<H1>Menu <xsl:value-of select="TOPICLIST/@TYPE" /></H1>
	
	<!-- BUILD MENUBAR -->

	<DIV ID="divMenuBar">
	<TABLE ID="tblMenuBar" BORDER="0">
	<TR>
	<xsl:for-each select="//TOPICS[TOPIC]">
		<TD CLASS="clsMenuBarItem">
			<xsl:attribute name="ID">tdMenuBarItem<xsl:value-of select="@TYPE" /></xsl:attribute>
			<xsl:value-of select="@TYPE" />
		</TD>
		<xsl:if test="context()[not(end())]">
		<TD>|</TD>
		</xsl:if>
	</xsl:for-each>
	</TR>
	</TABLE>
	</DIV>
		
	<!-- BUILD INDIVIDUAL MENUS -->

	<xsl:for-each select="//TOPICS[TOPIC]">
		<DIV CLASS="clsMenu">
		<xsl:attribute name="ID">divMenu<xsl:value-of select="@TYPE" /></xsl:attribute>
			<DIV CLASS="clsMenuSpacer"></DIV>
			<xsl:for-each select="TOPIC">
			<DIV>
			<A TARGET="_new">
				<xsl:attribute name="HREF">http://msdn.microsoft.com<xsl:value-of select="URL" /></xsl:attribute>
				<xsl:value-of select="TITLE" />
			</A>
			</DIV>
			</xsl:for-each>
		</DIV>
	</xsl:for-each>

	<P><BUTTON ONCLICK="window.alert(document.body.innerHTML);">View HTML</BUTTON></P>
	</BODY>
	</HTML>
</xsl:template>

</xsl:stylesheet>