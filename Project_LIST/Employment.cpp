#include "Employment.h"

Employment::Employment()
{
	memset(this->rCodeName.first, 0, sizeof(char) * STR_MAX);
	memset(this->rCodeName.second, 0, sizeof(char) * STR_MAX);
	memset(this->company, 0, sizeof(char) * STR_MAX);
	memset(this->qualification, 0, sizeof(char) * STR_MAX);
	memset(this->working_condition, 0, sizeof(char) * STR_MAX);
	memset(this->to, 0, sizeof(char) * STR_MAX);
	this->pDown = NULL;
	this->pNext = NULL;
}

Employment::~Employment()
{
	/* You must fill in here */
	delete company;
	delete qualification;
	delete working_condition;
	delete to;
}

/* You must fill in the member function definitions of the Employment class here */

void Employment::SetRegionCode(char* region_code)
{
	// set region_code in pair
	strcpy(rCodeName.first, region_code);
}

void Employment::SetRegionName(char* region_name)
{
	// set region_name in pair
	strcpy(rCodeName.second, region_name);
}

void Employment::SetCompany(char* company) 
{ 
	// set company
	strcpy(this->company, company);
}
void Employment::SetQualification(char* qualification)
{
	// set qualification
	strcpy(this->qualification, qualification);
}
void Employment::SetWorkingCondition(char* working_condition)
{
	// set working_condition
	strcpy(this->working_condition, working_condition);
}
void Employment::SetTo(char* to)
{
	// set TO
	strcpy(this->to, to);
}
void Employment::SetDown(Employment* pDown) { this->pDown = pDown; }  // set down Node(m_2DLL)
void Employment::SetNext(Employment* pNext) { this->pNext = pNext; }  // set next Node(m_Circular)

char* Employment::GetRegionCode() { return this->rCodeName.first; }  // return pair's first
char* Employment::GetRegionName() { return this->rCodeName.second; }  // return pair's second
char* Employment::GetCompany() { return this->company; }  // return company
char* Employment::GetQualification() { return this->qualification; }  // return qualification
char* Employment::GetWorkingCondition() { return this->working_condition; }  // return working_condition
char* Employment::GetTo() { return this->to; } // return TO
Employment* Employment::GetDown() { return pDown; }  // return down Node
Employment* Employment::GetNext() { return pNext; }  // reutnr next Node
