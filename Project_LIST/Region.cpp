#include"Region.h"

Region::Region()
{
	memset(this->rCodeName.first, 0, sizeof(char) * STR_MAX);
	memset(this->rCodeName.second, 0, sizeof(char) * STR_MAX);
	this->pNext = NULL;
	this->pLeft = NULL;
	this->pRight = NULL;
	this->pDown = NULL;
}

Region::~Region()
{
	/* You must fill in here */
	// memmory clear
	delete pNext;
	delete pLeft;
	delete pRight;
	delete pDown;
}

/* You must fill in the member function definitions of the Region class here */

void Region::SetRegionCode(char* region_code)
{
	// set region code in pair
	strcpy(rCodeName.first, region_code);
}

void Region::SetRegionName(char* region_name)
{
	// set region_name in pair
	strcpy(rCodeName.second, region_name);
}
void Region::SetNext(Region* pNext) { this->pNext = pNext; }  // set Next Node(m_Circular)
void Region::SetLeft(Region* pLeft) { this->pLeft = pLeft; }  // set Left Node(m_BST)
void Region::SetRight(Region* pRight) { this->pRight = pRight; }  // set Right Node(m_BST)
void Region::SetDown(Employment* pDown) { this->pDown = pDown; }  // set Down Node(m_2DLL)
char* Region::GetRegionCode() { return rCodeName.first; }  // get region code
char* Region::GetRegionName() { return rCodeName.second; }  // get region name
Region* Region::GetNext() { return pNext; };  // get Next Node
Region* Region::GetLeft() { return pLeft; };  // get Left Node
Region* Region::GetRight() { return pRight; };  // get Right Node
Employment* Region::GetDown() { return pDown; };  // get Down Node