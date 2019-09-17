#ifndef _LIST_CIRCULAR_H
#define  _LIST_CIRCULAR_H

#include "Employment.h"
#include <iostream>

class List_Circular
{
private:
	Employment* pHead;  // Employment's Head Node
	Employment* pNext;  // Employment's Next Node
public:
	List_Circular();
	~List_Circular();

	void SetHead(Employment* pNode);  // set Head Node
	Employment* GetHead();  // return Head Node
	void Insert(Employment* pNode);  // Insert Node in m_2DLL
	Employment* Delete(Employment* pNode);  // Delete Node in m_2DLL
};
#endif