#include "List_2D.h"

List_2D::List_2D()
{
	this->pHead = NULL;
}

List_2D::~List_2D()
{
	/* You must fill in here */
	delete pHead;
}

/* You must fill in the member function definitions of the List_2D class here */

void List_2D::SetHead(Region* pNode)  // set Head Node
{
	pHead = pNode;
}

Region* List_2D::GetHead()  // reutnr Head Node
{
	return pHead;
}

void List_2D::Insert(Region* pNode)
{
	Region* currentNode = pHead;

	// if there's any Node, pNode is Head Node
	if (currentNode == NULL)
	{
		SetHead(pNode);
		pHead->SetNext(NULL);
	}

	// if there's other Node
	else
	{
		// redundacy Node check
		Region* cNode = pHead;
		Region* parentNode = NULL;
		while (cNode != NULL)
		{
			// if cNode has same code with pNode, break
			if (strcmp(pNode->GetRegionCode(), cNode->GetRegionCode()) == 0)
				break;
			parentNode = cNode;
			cNode = cNode->GetNext();
		}
		
		// if there's no redundancy Node
		if (cNode == NULL)
			parentNode->SetNext(pNode);
	}
}

void List_2D::Insert(Employment* pNode)
{
	Region* currentNode_Re = pHead;

	// find Node has same region code
	while (strcmp(currentNode_Re->GetRegionCode(), pNode->GetRegionCode()) != 0)
		currentNode_Re = currentNode_Re->GetNext();

	// if Region Node has any Employment Node
	if (currentNode_Re->GetDown() == NULL)
		currentNode_Re->SetDown(pNode);
	
	// if Region Node has other Employment Node, set ascending order for company name
	else
	{
		Employment* cEm = currentNode_Re->GetDown();  // pNode's Down Node
		Employment* pEm = NULL;  // pNode's Up Node
		// find position to insert
		while (cEm != NULL)
		{
			if (strcmp(pNode->GetCompany(), cEm->GetCompany()) < 0)
				break;
			pEm = cEm;
			cEm = cEm->GetDown();
		}
		// if pNode insert at first node
		if (pEm == NULL)
		{
			currentNode_Re->SetDown(pNode);
			pNode->SetDown(cEm);
		}
		// if pNode insert at second ~ last node
		else
		{
			pEm->SetDown(pNode);
			pNode->SetDown(cEm);
		}
	}
}

bool List_2D::Delete(Employment* pNode)
{
	// search Node to delete(Region Node)
	Region* cRe = pHead;
	while (cRe != NULL)
	{
		// if pNode and current Node has same region code, break
		if (strcmp(cRe->GetRegionCode(), pNode->GetRegionCode()) == 0)
			break;

		cRe = cRe->GetNext();
	}
	// if there's no Node to delete, return false
	if (cRe == NULL)
		return false;

	// search Node to delete(Employment)
	Employment* cEm = cRe->GetDown();
	Employment* prevEm = NULL;
	while (cEm != NULL)
	{
		// if pNode and current Node has same information (without TO), break
		if (strcmp(cEm->GetCompany(), pNode->GetCompany()) == 0 && strcmp(cEm->GetQualification(), pNode->GetQualification()) == 0 && strcmp(cEm->GetRegionName(), pNode->GetRegionName()) == 0 && strcmp(cEm->GetWorkingCondition(), pNode->GetWorkingCondition()) == 0)
			break;

		prevEm = cEm;
		cEm = cEm->GetDown();
	}

	// link Node
	// if cEm Node is first Node
	if (cEm == cRe->GetDown())
		cRe->SetDown(cEm->GetDown());

	// if cEm Node isn't first Node
	else
		prevEm->SetDown(cEm->GetDown());
	// if there's no find Node
	if (cEm == NULL)
		return false;

	return true;
}