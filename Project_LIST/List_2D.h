#ifndef _LIST_2D_H
#define _LIST_2D_H

#include "Employment.h"
#include "Region.h"
#include <cstring>

class List_2D
{
private:
	Region* pHead;  // Reigon's Head Node
public:
	List_2D();
	~List_2D();

	void SetHead(Region* pNode);  // set Head Node
	Region* GetHead();  // return Head Node
	void Insert(Region* pNode);  // Insert Node in m_2DLL
	void Insert(Employment* pNode);  // Insert Node in m_2DLL
	bool Delete(Employment* pNode);  // Delete Node in m_2DLL
};
#endif