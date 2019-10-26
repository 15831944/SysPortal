// ListItem.h: interface for the ListItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISTITEM_H__605D4101_37CB_11D4_9F4B_005004816FFF__INCLUDED_)
#define AFX_LISTITEM_H__605D4101_37CB_11D4_9F4B_005004816FFF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CListItem  
{
public:
	void GetItem(int Num);
	void DeleteItem(int NumItem);
	int InsertItem(char *NewItem);
	ListItem();
	virtual ~ListItem();
	virtual ListItem();
private:
	int LenItems;
	char * ListItem[

};

#endif // !defined(AFX_LISTITEM_H__605D4101_37CB_11D4_9F4B_005004816FFF__INCLUDED_)
