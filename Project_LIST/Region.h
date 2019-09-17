#ifndef _REGION_H_
#define _REGION_H_

#include<utility>
#include <cstring>
#include "Employment.h"

#define STR_MAX 60

class Region
{
private:
	std::pair<char[STR_MAX], char[STR_MAX]> rCodeName;
	Region* pNext;		//Next Region node in 2D Linked List
	Region* pLeft;		//Left region node in Binary Search Tree 
	Region* pRight;		//Right region node in Binary Search Tree
	Employment* pDown;	//Employment node in 2D Linked List

public:
	Region();
	~Region();

	//Getter,Setter Methods
	void SetRegionCode(char* region_code);  // set region code
	void SetRegionName(char* region_name);  // set region name
	void SetNext(Region* pNext);  // set Next Node in m_2DLL
	void SetLeft(Region* pLeft);  // set Left Node in m_BST
	void SetRight(Region* pRight);  // set Right Node in m_BST
	void SetDown(Employment* pDown);  // set Down Node in m_2DLL

	char* GetRegionCode();  // return region code
	char* GetRegionName();  // return region name
	Region* GetNext();  // return Next Node
	Region* GetLeft();  // return Left Node
	Region* GetRight();  // return Right Node
	Employment* GetDown();  // return Down Node
};
#endif