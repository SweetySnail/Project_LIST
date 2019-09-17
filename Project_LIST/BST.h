#ifndef _BST_H_
#define _BST_H_

#include "Employment.h"
#include "Region.h"
class BST
{
private:
	Region* root;  // Region's root Node

public:	
	BST();
	~BST();

	void SetRoot(Region*);  // set Root Node
	Region* GetRoot();  // return Root Node

	bool Insert(Region* rNode);  // Insert Node
	bool Delete(Region* eNode);  // Delete Node
	Employment* Search(char* region_code);  // Search Node
};
#endif