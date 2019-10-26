<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl">

<xsl:template match="/">
<HTML>
  <HEAD>
  <TITLE>List </TITLE>
  <LINK REL="stylesheet" TYPE="text/css" HREF="MenuXML.css" />
  <SCRIPT TYPE="text/javascript" LANGUAGE="javascript" SRC="MenuXML.js"></SCRIPT>
  </HEAD>
  <BODY>

          <IMG src = "outplus.jpg" border = "0" ONCLICK="ShowAll('UL')" alt="Show All"></IMG>
         <IMG src = "outminus.jpg" border = "0"  ONCLICK="HideAll('UL')" alt ="Hide All"></IMG>
         <IMG src = "Home.gif" border = "0"></IMG>


  <UL><xsl:apply-templates select="TOPICLIST/TOPICS" /></UL>

  </BODY>
  </HTML>
 
</xsl:template>

<xsl:template match="TOPICS">
  <LI CLASS="clsHasKids"><xsl:value-of select="@TYPE" />
  <UL>
  <xsl:for-each select="TOPIC">
    <LI>
    <A TARGET="MainFrame">
      <xsl:attribute name="HREF">
       <xsl:value-of select="URL" />
      </xsl:attribute>
      <xsl:value-of select="TITLE" />
    </A>
    </LI>
  </xsl:for-each>
  <xsl:if test="TOPICS"><xsl:apply-templates /></xsl:if>
  </UL>
  </LI>
</xsl:template>

</xsl:stylesheet>

