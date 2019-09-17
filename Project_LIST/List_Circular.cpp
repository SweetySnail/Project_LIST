#include "List_Circular.h"

List_Circular::List_Circular()
{
	this->pHead = NULL;
}

List_Circular::~List_Circular()
{
	delete pHead;
	/* You must fill in here */
}

/* You must fill in the member function definitions of the List_Circular class here */

void List_Circular::SetHead(Employment* pNode) { pHead = pNode; pHead->SetNext(pNode); }  // set head Node
Employment* List_Circular::GetHead(){return pHead;}  // return head Node

void List_Circular::Insert(Employment* pNode)
{
	// if m_Circular has any Node
	if (pHead == NULL)
	{
		SetHead(pNode);
		pHead->SetNext(pNode);
	}

	// if m_Circular has other Node
	else
	{
		Employment* currentNode = pHead;
		// find last Node
		while (currentNode->GetNext() != pHead)
			currentNode = currentNode->GetNext();

		// link Node
		currentNode->SetNext(pNode);
		pNode->SetNext(pHead);
	}
}

Employment* List_Circular::Delete(Employment* pNode)
{
	Employment* cEm = pHead;
	do
	{
		// if cEm and pNode's information are same
		if (strcmp(cEm->GetCompany(), pNode->GetCompany()) == 0 && strcmp(cEm->GetQualification(), pNode->GetQualification()) == 0 && strcmp(cEm->GetRegionName(), pNode->GetRegionName()) == 0 && strcmp(cEm->GetWorkingCondition(), pNode->GetWorkingCondition()) == 0)
			return cEm;
		cEm = cEm->GetNext();
	} while (cEm != pHead);
	return NULL;
}