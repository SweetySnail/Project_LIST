#include "BST.h"

BST::BST()
{
	this->root = NULL;
}

BST::~BST()
{
	delete this->root;
}

/* You must fill in the member function definitions of the BST class here */

void BST::SetRoot(Region* root) { this->root = root; }  // set root
Region* BST::GetRoot() { return root; }  // return root

bool BST::Insert(Region* rNode)
{
	Region* cNode = root;  // current Node
	Region* pNode = NULL;  // prev Node

	// find insert node's position
	while (cNode)
	{
		pNode = cNode; 
		// if rNode is smaller than cNode, cNode move Left Child
		if (strcmp(rNode->GetRegionCode(), cNode->GetRegionCode())<0)
			cNode = cNode->GetLeft();
		// if rNode is bigger than cNode, cNode move Right Child
		else if (strcmp(rNode->GetRegionCode(), cNode->GetRegionCode())>0)
			cNode = cNode->GetRight();
	}
	
	// if rNode is smaller than pNode, pNode's LeftChild is rNode
	if (strcmp(rNode->GetRegionCode(), pNode->GetRegionCode()) < 0)
		pNode->SetLeft(rNode);
	// if rNode is bigger than pNode, pNode's RightChild is rNode
	else if (strcmp(rNode->GetRegionCode(), pNode->GetRegionCode()) > 0)
		pNode->SetRight(rNode);
	
	return true;
}

bool BST::Delete(Region* eNode)
{
	Region* cNode = root;
	Region* pNode = NULL;
	// find Node that has same region code
	while (strcmp(eNode->GetRegionCode(), cNode->GetRegionCode()) != 0 && cNode != NULL)
	{
		pNode = cNode;
		// if eNode is smaller than cNode, cNode move cNode's LeftChild
		if (eNode->GetRegionCode() > cNode->GetRegionCode())
			cNode = cNode->GetLeft();
		// if eNode is bigger than cNode, cNode move cNode's RightChild
		else if (eNode->GetRegionCode() < cNode->GetRegionCode())
			cNode = cNode->GetRight();
	}
	// if find Node is Leaf Node
	if (cNode->GetLeft() == NULL && cNode->GetRight() == NULL)
	{
		// if find Node is Root Node
		if (pNode == NULL)
			root = NULL;
		// if find Node is pNode's Left Child
		else if (pNode->GetLeft() == cNode)
			pNode->SetLeft(NULL);
		// if find Node is pNode's Right Child
		else
			pNode->SetRight(NULL);
		delete[] cNode;  // memmory clear
		return true;
	}

	// if find Node has Only Left Child
	if (cNode->GetLeft() == NULL)
	{
		// if find Node is Root Node
		if (pNode == NULL)
			SetRoot(cNode->GetRight());
		// if find Node is pNode's LeftChild
		else if (pNode->GetLeft() == cNode)
			pNode->SetLeft(cNode->GetRight());
		// if find Node is pNode's RightChild
		else
			pNode->SetRight(pNode->GetRight());
		delete[] cNode;  // memmory clear
		return true;
	}

	// if find Node has Only Right Child
	if (cNode->GetRight() == NULL)
	{
		// if find Node is Root Node
		if (pNode == NULL)
			SetRoot(cNode->GetLeft());
		// if find Node is pNode's LeftChild
		else if (pNode->GetLeft() == cNode)
			pNode->SetLeft(cNode->GetLeft());
		// if find Node is pNode's RightChild
		else
			pNode->SetRight(pNode->GetLeft());
		delete[] cNode;  // memmory clear
		return true;
	}

	// if find Node has Right and Left Child
	if (cNode->GetLeft() != NULL && cNode->GetRight() != NULL)
	{
		Region* prevprev = cNode;
		Region* prev = cNode->GetLeft();
		Region* curr = cNode->GetLeft()->GetRight();

		// move prevprev, prev, curr until curr has NULL
		while (curr != NULL)
		{
			prevprev = prev;
			prev = curr;
			curr = curr->GetRight();
		}
		prevprev->SetRight(prev->GetLeft());
		
		// if find Node is Root Node
		if (pNode == NULL)
			SetRoot(prev);
		// if find Node is pNode's LeftChild
		else if (pNode->GetLeft() == cNode)
			pNode->SetLeft(prev);
		// if find Node is pNode's RightChild
		else
			pNode->SetRight(prev);
		
		return true;
	}
	return false;
}

Employment* BST::Search(char* region_code)
{
	Region* currentNode = root;
	// if BST has any Node, return NULL
	if (currentNode == NULL)
		return NULL;
	
	// Compare currentNode and region_code
	while (strcmp(currentNode->GetRegionCode(), region_code) != 0)
	{
		// if currentNode is bigger than region_code
		if (strcmp(currentNode->GetRegionCode(), region_code) > 0)
			currentNode = currentNode->GetLeft();
		// if currentNode is smaller than region_code
		if (strcmp(currentNode->GetRegionCode(), region_code) < 0)
			currentNode = currentNode->GetRight();
		// if there's no find Node
		if (currentNode == NULL)
			return NULL;
	}
	return currentNode->GetDown();
}