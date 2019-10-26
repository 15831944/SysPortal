function GetChildElem(eSrc,sTagName)
{
  var cKids = eSrc.children;
  for (var i=0;i<cKids.length;i++)
  {
    if (sTagName == cKids[i].tagName) return cKids[i];
  }
  return false;
}

function document.onclick()
{
  var eSrc = window.event.srcElement;
  if ("clsHasKids" == eSrc.className && (eChild = GetChildElem(eSrc,"UL")))
  {
    eChild.style.display = ("block" == eChild.style.display ? "none" : "block");
  }
}

function ShowAll(sTagName)
{
  var cElems = document.all.tags(sTagName);
  var iNumElems = cElems.length;
  for (var i=1;i<iNumElems;i++) cElems[i].style.display = "block";
}

function HideAll(sTagName)
{
  var cElems = document.all.tags(sTagName);
  var iNumElems = cElems.length;
  for (var i=1;i<iNumElems;i++) cElems[i].style.display = "none";
}

