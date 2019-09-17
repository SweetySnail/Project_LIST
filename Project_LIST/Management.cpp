#include "Management.h"
#include <string>

Management::Management()
{
	// make List_2D, List_Circular, BST class
	this->m_2DLL = new List_2D();
	this->m_Circular = new List_Circular();
	this->m_BST = new BST();

	//Clear existing out file contents
	ofstream fout1, fout2, fout3;
	fout1.open("OUT_FIND.txt", ios::trunc);
	fout2.open("OUT_DELETE.txt", ios::trunc);
	fout3.open("OUT_PRINT.txt", ios::trunc);
	fout1.close();
	fout2.close();
	fout3.close();
}

Management::~Management()
{
	/* You must fill in here */
}

/* You must fill in the member function definitions of the Management class here */
bool Management::ReadCommand()
{
	// open and read IN_Command text file
	ifstream read("IN_Command.txt");

	// if it can't open, return false
	if (read.is_open() == false)
		return false;
	// if it can open
	else
	{
		string cmd;
		// read the text file a line until file end
		while (getline(read, cmd))
		{
			char cmdbuff[512];
			// change string type to char type and copy in cmdbuff
			strcpy(cmdbuff, cmd.c_str());  // c_str -> stringÇüÀ» charÇüÀž·Î º¯È¯

			char* token1 = strtok(cmdbuff, " ");  // save command in token1
			char* token2 = strtok(NULL, " ");  // save values to need process command in token2

			if (!strcmp(token1, "LOAD"))  // if token1 is LOAD
				LOAD(token2);  // process LOAD to use token2

			else if (!strcmp(token1, "UPDATE"))  // if token1 is UPDATE
				UPDATE(token2);  // process UPDATE to use token2

			else if (!strcmp(token1, "FIND"))  // if token1 is UPDATE
				FIND(token2);  // process FIND to use token2

			else if (!strcmp(token1, "DELETE"))  // if token1 is DELETE
				DELETE(token2);  // process DELETE to use token2

			else if (!strcmp(token1, "PRINT"))  // if token1 is PRINT
				PRINT();  // process PRINT

			else if (!strcmp(token1, "EXIT"))  // if token1 is EXIT
				EXIT();  // process EXIT
		}
		read.close();  // close read
		return true;
	}
}

bool Management::LOAD(char* filename)
{
	if (strcmp(filename, "IN_LOAD.txt") != 0)  // if there is no IN_LOAD.txt, output Error messages
	{
		cout << "======= ERROR =======" << endl;
		cout << "100-1" << endl;
		cout << "=====================" << endl;

		return false;
	}

	else
	{
		ifstream read;
		read.open("IN_LOAD.txt");

		char cmd[100];  // temporary save values about Employment's information
		read.getline(cmd, 100);  // 1 ~ 3 lines have useless informations
		read.getline(cmd, 100);
		read.getline(cmd, 100);

		while (read.getline(cmd, 100))  // read the text file a line until file end
		{
			char cmdbuff[512];
			strcpy(cmdbuff, cmd);

			// save values to use strtok function
			char* Region_Code = strtok(cmdbuff, ",");
			char* Region_Name = strtok(NULL, ",");
			char* Company = strtok(NULL, ",");
			char* Qualification = strtok(NULL, ",");
			char* WorkingCondition = strtok(NULL, ",");
			char* TO = strtok(NULL, ",");

			// make Employment Node and save values
			Employment* Em = new Employment;
			Em->SetRegionCode(Region_Code);
			Em->SetRegionName(Region_Name);
			Em->SetCompany(Company);
			Em->SetQualification(Qualification);
			Em->SetWorkingCondition(WorkingCondition);
			Em->SetTo(TO);

			// Make m_2DLL & m_Circular
			// if Em's TO is E
			if (strcmp(Em->GetTo(), "E") == 0)
			{
				// make Region Node and save values
				Region* Re = new Region;
				Re->SetRegionCode(Region_Code);
				Re->SetRegionName(Region_Name);

				// create m_2DLL to use Region Node and Employment Node
				m_2DLL->Insert(Re);
				m_2DLL->Insert(Em);
			}
			// if Em's To is NE
			else
				// create m_Circular to use Employment Node
				m_Circular->Insert(Em);
		}

		// Make m_BST
		// m_2DLL's first Node is m_BST's root
		m_BST->SetRoot(m_2DLL->GetHead());

		// insert Region Node in m_BST until there is no values in current Node
		Region* current_Re = m_2DLL->GetHead()->GetNext();
		while (current_Re != NULL)
		{
			m_BST->Insert(current_Re);
			current_Re = current_Re->GetNext();
		}
		read.close();
		cout << "================ LOAD =====================" << endl;
		cout << "IN_LOAD.txt LOAD Successful" << endl;
		cout << "===========================================" << endl << endl;
	}
}

bool Management::UPDATE(char* filename)
{
	if (strcmp(filename, "IN_UPDATE.txt"))  // if there is no file name is IN_UPDATE, output Error messages
	{
		cout << "======= ERROR =======" << endl;
		cout << "200-1" << endl;
		cout << "=====================" << endl;

		return false;
	}

	else
	{
		ifstream read1;
		read1.open("IN_UPDATE.txt");  // read the text file a line until file end

		char cmd1[100] = { NULL };
		read1.getline(cmd1, 100);  // read text file and save in cmd1
		read1.getline(cmd1, 100);
		read1.getline(cmd1, 100);

		while (read1.getline(cmd1, 100))
		{
			char cmdbuff1[512];
			strcpy(cmdbuff1, cmd1);

			// read cmdbuff if cursor meet ',' save values
			char* Region_Code = strtok(cmdbuff1, ",");
			char* Region_Name = strtok(NULL, ",");
			char* Company = strtok(NULL, ",");
			char* Qualification = strtok(NULL, ",");
			char* WorkingCondition = strtok(NULL, ",");
			char* TO = strtok(NULL, ",");

			// make Em class
			Employment* Em = new Employment;
			Em->SetRegionCode(Region_Code);
			Em->SetRegionName(Region_Name);
			Em->SetCompany(Company);
			Em->SetQualification(Qualification);
			Em->SetWorkingCondition(WorkingCondition);
			Em->SetTo(TO);

			// if Em class's TO is NE
			if (strcmp(Em->GetTo(), "NE") == 0)
			{
				// Delete in m_2DLL
				// if is fail, output Error messages
				if (m_2DLL->Delete(Em) == false)
				{
					cout << "======= ERROR =======" << endl;
					cout << "200-2" << endl;
					cout << "=====================" << endl << endl;
				}

				// Insert in m_Circular
				m_Circular->Insert(Em);
			}

			// if Em class's TO is E
			else
			{
				// Delete in m_Circular
				Employment* pNode = NULL;
				Employment* cNode = m_Circular->GetHead();
				Employment* pDel = m_Circular->Delete(Em);

				// if there's no Node to delete, output Error messages
				if (pDel == NULL)
				{
					cout << "======= ERROR =======" << endl;
					cout << "200-2" << endl;
					cout << "=====================" << endl << endl;
				}
				else  // if there's Node to delete
				{
					// Search cNode until meet final Node
					while (cNode != m_Circular->GetHead() || pNode == NULL)
					{
						if (cNode == pDel)
						{
							pNode->SetNext(cNode->GetNext());
							break;
						}
						pNode = cNode;
						cNode = cNode->GetNext();
					}

					// Insert in m_2DLL
					m_2DLL->Insert(Em);
				}
			}
		}
		read1.close();  // stop use read1
		ifstream read2;
		read2.open("IN_UPDATE.txt");  // read the text file a line until file end

		char cmd2[100] = { NULL };
		// read and write read2, in console
		while (read2.getline(cmd2, 100))
			cout << cmd2 << endl;
		cout << endl;
	}
}

bool Management::FIND(char* region_code)
{
	Employment* fNode = m_BST->Search(region_code);  // Search fNode in m_BST

	if (fNode == NULL)  // if there's no fNode, output Error messages and return false
	{
		cout << "======= ERROR =======" << endl;
		cout << "300-1" << endl;
		cout << "=====================" << endl << endl;

		return false;
	}

	else  // if there's fNode
	{
		ofstream write("OUT_FIND.txt", ios::app);  // open OUT_FIND.txt and write
		write << "====== OUT_FIND - " << region_code << " 지역의 채용중인 기업 ======" << endl;
		write << "지역코드, 지역명, 기업명, 지원자격, 근무조건, TO" << endl;
		write << "=================================================" << endl;
		cout << "====== OUT_FIND - " << region_code << " 지역의 채용중인 기업 ======" << endl;
		cout << "지역코드, 지역명, 기업명, 지원자격, 근무조건, TO" << endl;
		cout << "=================================================" << endl;
		while (fNode != NULL)  // until fNode is NULL
		{
			// write in text file about fNode's information
			write << fNode->GetRegionCode() << "," << fNode->GetRegionName() << "," << fNode->GetCompany()
				<< "," << fNode->GetQualification() << "," << fNode->GetWorkingCondition() << "," << fNode->GetTo() << endl;
			cout << fNode->GetRegionCode() << "," << fNode->GetRegionName() << "," << fNode->GetCompany()
				<< "," << fNode->GetQualification() << "," << fNode->GetWorkingCondition() << "," << fNode->GetTo() << endl;
			fNode = fNode->GetDown();
		}
		write << endl;
		cout << endl;
		write.close();  // stop use write
		return true;
	}
}

bool Management::DELETE(char* region_code)
{
	// Search delete Node in m_2DLL
	Region* two_Re = m_2DLL->GetHead();
	Region* pNode = NULL;
	// until two_Re has NULL
	while (two_Re != NULL)
	{
		// if two_Re's Region Code and region_code is same, break
		if (strcmp(two_Re->GetRegionCode(), region_code) == 0)
			break;

		// if there's no find Node, two_Re has NULL
		if (two_Re->GetNext() == NULL && strcmp(two_Re->GetRegionCode(), region_code) != 0)
			two_Re = NULL;

		pNode = two_Re; // pNode is two_Re's prev Node
		two_Re = two_Re->GetNext();  // two_Re is current Node
	}

	// if two_Re isn't NULL
	if (two_Re != NULL)
	{
		// link two_Re's prev Node and next Node
		pNode->SetNext(two_Re->GetNext());

		// write in OUT_DELETE.txt
		ofstream write("OUT_DELETE.txt", ios::app);
		write << "====== OUT_DELETE - " << region_code << " 지역의 삭제된 채용중인 기업 ======" << endl;
		write << "지역코드, 지역명, 기업명, 지원자격, 근무조건, TO" << endl;
		write << "=========================================================" << endl;
		cout << "====== OUT_DELETE - " << region_code << " 지역의 삭제된 채용중인 기업 ======" << endl;
		cout << "지역코드, 지역명, 기업명, 지원자격, 근무조건, TO" << endl;
		cout << "=========================================================" << endl;

		Employment* wNode = two_Re->GetDown();
		while (wNode != NULL)
		{
			//write in OUT_DELETE.txt about wNode's  information until wNode is NULL
			write << wNode->GetRegionCode() << "," << wNode->GetRegionName() << "," << wNode->GetCompany()
				<< "," << wNode->GetQualification() << "," << wNode->GetWorkingCondition() << "," << wNode->GetTo() << endl;
			cout << wNode->GetRegionCode() << "," << wNode->GetRegionName() << "," << wNode->GetCompany()
				<< "," << wNode->GetQualification() << "," << wNode->GetWorkingCondition() << "," << wNode->GetTo() << endl;
			wNode = wNode->GetDown();
		}
		write << endl;
		cout << endl;
		// Delete in m_BST
		m_BST->Delete(two_Re);
	}

	// Search in m_Circular
	ofstream write("OUT_DELETE.txt", ios::app);
	write << "====== OUT_DELETE - " << region_code << " 지역의 삭제된 채용마감 기업 ======" << endl;
	write << "지역코드, 지역명, 기업명, 지원자격, 근무조건, TO" << endl;
	write << "=========================================================" << endl;
	cout << "====== OUT_DELETE - " << region_code << " 지역의 삭제된 채용마감 기업 ======" << endl;
	cout << "지역코드, 지역명, 기업명, 지원자격, 근무조건, TO" << endl;
	cout << "=========================================================" << endl;

	Employment* circular_Em = m_Circular->GetHead();  // current Node
	Employment* p_Em = NULL;  // prev Node

							  // Search Node that has same Region Code
	while (circular_Em != m_Circular->GetHead() || p_Em == NULL)
	{
		// if find what we want and it isn't head Node
		if (strcmp(circular_Em->GetRegionCode(), region_code) == 0 && circular_Em != m_Circular->GetHead())
		{
			// write in OUT_DELETE.txt
			write << circular_Em->GetRegionCode() << "," << circular_Em->GetRegionName() << "," << circular_Em->GetCompany()
				<< "," << circular_Em->GetQualification() << "," << circular_Em->GetWorkingCondition() << "," << circular_Em->GetTo() << endl;
			cout << circular_Em->GetRegionCode() << "," << circular_Em->GetRegionName() << "," << circular_Em->GetCompany()
				<< "," << circular_Em->GetQualification() << "," << circular_Em->GetWorkingCondition() << "," << circular_Em->GetTo() << endl;
			// link prev Node and next Node
			p_Em->SetNext(circular_Em->GetNext());
		}

		// if find Node is head
		if (strcmp(circular_Em->GetRegionCode(), region_code) == 0 && circular_Em == m_Circular->GetHead())
		{
			// write in OUT_DELETE.txt
			write << circular_Em->GetRegionCode() << "," << circular_Em->GetRegionName() << "," << circular_Em->GetCompany()
				<< "," << circular_Em->GetQualification() << "," << circular_Em->GetWorkingCondition() << "," << circular_Em->GetTo() << endl;
			cout << circular_Em->GetRegionCode() << "," << circular_Em->GetRegionName() << "," << circular_Em->GetCompany()
				<< "," << circular_Em->GetQualification() << "," << circular_Em->GetWorkingCondition() << "," << circular_Em->GetTo() << endl;

			// move p_Em Node until p_Em's next Node is head
			p_Em = m_Circular->GetHead();
			while (p_Em->GetNext() != m_Circular->GetHead())
				p_Em = p_Em->GetNext();
			// link prev Node and next Node
			p_Em->SetNext(circular_Em->GetNext());
			m_Circular->SetHead(circular_Em->GetNext());
		}
		p_Em = circular_Em;
		circular_Em = circular_Em->GetNext();
	}
	write << endl;
	cout << endl;

	// if there's no search node, circular_Em is NULL
	if (strcmp(circular_Em->GetRegionCode(), region_code) != 0 && circular_Em->GetNext() == m_Circular->GetHead())
		circular_Em = NULL;

	// if m_2DLL and m_Circular hasn't find Node, output Error messages
	if (circular_Em == NULL && two_Re == NULL)
	{
		cout << "======= ERROR =======" << endl;
		cout << "400-1" << endl;
		cout << "=====================" << endl;
		return false;
	}
	return true;
}

bool Management::PRINT() // Inorder¹æœÄÀž·Î ÇÁž°Æ®  //******************//
{
	ofstream write("OUT_PRINT.txt", ios::app);
	write << "==== OUT_PRINT - 모든 지역의 채용중인 기업 ====" << endl;
	write << "지역코드,지역명,기업명,지원자격,근무조건,TO" << endl;
	write << "================================================" << endl;
	cout << "==== OUT_PRINT - 모든 지역의 채용중인 기업 ====" << endl;
	cout << "지역코드,지역명,기업명,지원자격,근무조건,TO" << endl;
	cout << "===============================================" << endl;
	if (m_BST == NULL)
		return false;
	else
	{
		Region* cNode = m_BST->GetRoot();
		stack <Region*> stack;

		// reapeat until meet break;
		while (1)
		{
			// cNode has Left LeafNode
			while (cNode != NULL)
			{
				stack.push(cNode);
				cNode = cNode->GetLeft();
			}
			// if stack isn't empty
			if (stack.size() != 0)
			{
				// set cNode stack's top and pop
				cNode = stack.top();
				stack.pop();
			}
			// if cNode is NULL, break
			if (cNode == NULL)
				break;

			// write in OUT_PRINT.txt file and console
			Employment* cEm = cNode->GetDown();
			while (cEm != NULL)
			{
				write << cEm->GetRegionCode() << "," << cEm->GetRegionName() << "," << cEm->GetCompany() << ","
					<< cEm->GetQualification() << "," << cEm->GetWorkingCondition() << "," << cEm->GetTo() << endl;
				cout << cEm->GetRegionCode() << "," << cEm->GetRegionName() << "," << cEm->GetCompany() << ","
					<< cEm->GetQualification() << "," << cEm->GetWorkingCondition() << "," << cEm->GetTo() << endl;
				cEm = cEm->GetDown();
			}
			cNode = cNode->GetRight();
		}
		write.close();
	}
}

bool Management::EXIT()
{
	//delete m_2DLL;  // memory clear for m_2DLL
	//delete m_BST;  // memory clear for m_BST
	//delete m_Circular;  // memory clear for m_Circular

	return true;
}