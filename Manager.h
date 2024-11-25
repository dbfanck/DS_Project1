#pragma once
#include "MemberQueue.h"
#include "TermsList.h"
#include "TermsBST.h"
#include "NameBST.h"
#include <fstream>
using namespace std;

class Manager
{
private:

	ifstream	fcmd;
	ofstream	flog;
	MemberQueue memberQueue; //MemberQueue
	TermsLIST termsList; //Terms LinkedList
	NameBST nameBST; //NameBST

public:
	Manager();
	~Manager();

	void run(const char* command);
	
	void PrintSuccess(const char* cmd);
	void PrintErrorCode(int num);

	// LOAD
	void LOAD(void);

	// ADD
	void ADD(char* member_info);

	// QPOP
	void QPOP(void);

	// SEARCH
	void SEARCH(char* member_name);

	// PRINT
	void PRINT(char* BST);

	// DELETE
	void DELETE(char* delInfo);
};
