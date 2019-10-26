<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl">

<xsl:template match="/">
	<HTML>
	<HEAD>
	<TITLE>List <xsl:value-of select="TOPICLIST/@TYPE" /></TITLE>

	<LINK REL="stylesheet" TYPE="text/css" HREF="listspan.css" />
	<SCRIPT TYPE="text/javascript" LANGUAGE="javascript" SRC="listspan.js"> </SCRIPT>

	</HEAD>
	<BODY>
	<BUTTON ONCLICK="ShowAll('UL')">Show All</BUTTON>
	<BUTTON ONCLICK="HideAll('UL')">Hide All</BUTTON>
	<H1>List <xsl:value-of select="TOPICLIST/@TYPE" /></H1>
	<UL><xsl:apply-templates select="TOPICLIST/TOPICS" />	</UL>
	<P><BUTTON><xsl:attribute name="ONCLICK">window.alert(document.body.innerHTML);</xsl:attribute>View HTML</BUTTON></P>
	</BODY>
	</HTML>
</xsl:template>

<xsl:template match="TOPICS">
	<LI CLASS="clsHasKids"><SPAN><xsl:value-of select="@TYPE" /></SPAN>
	<UL>
	<xsl:for-each select="TOPIC">
		<LI>
			<A TARGET="_new">
				<xsl:attribute name="HREF">http://msdn.microsoft.com<xsl:value-of select="URL" /></xsl:attribute>
				<xsl:value-of select="TITLE" />
			</A>
		</LI>
	</xsl:for-each>
	<xsl:apply-templates select="TOPICS" />
	</UL>
	</LI>
</xsl:template>

</xsl:stylesheet>