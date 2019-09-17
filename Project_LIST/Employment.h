#ifndef _EMPLOYMENT_H_
#define _EMPLOYMENT_H_

#include <cstring>
#include <utility>

#define STR_MAX 60

class Employment
{
private:
	std::pair<char[STR_MAX], char[STR_MAX]> rCodeName;  // Employment's region_code, region_name
	char company[STR_MAX];  // Employment's company 
	char qualification[STR_MAX];  // Employment's  qualification
	char working_condition[STR_MAX];  // Employment's  working_condition
	char to[STR_MAX];  // Employment's TO
	Employment* pDown;	//Employment node in 2D Linked List
	Employment* pNext;	//Employment node in Circular Linked List pointer

public:
	Employment();
	~Employment();

	//Getter,Setter Methods
	void SetRegionCode(char* region_code);  // set region code
	void SetRegionName(char* region_name);  // set region name
	void SetCompany(char* company);  // set company
	void SetQualification(char* qualification);  // set qualification
	void SetWorkingCondition(char* working_condition);  // set working condition
	void SetTo(char* to);  // set TO
	void SetDown(Employment* pDown);  // set Down
	void SetNext(Employment* pNext);  // set Next

	char* GetRegionCode();  // return region code
	char* GetRegionName();  // return region name
	char* GetCompany();  // return company
	char* GetQualification();  // return qualification
	char* GetWorkingCondition();  // return working condition
	char* GetTo();  // return TO
	Employment* GetDown();  // return Down Node
	Employment* GetNext();  // returnr Next Node
};
#endif