class TermsLIST;

#pragma once
#include "TermsBSTNode.h"
#include "NameBST.h"
#include <fstream>

class TermsBST
{
private:
	TermsBSTNode* root;

public:
	TermsBST();
	~TermsBST();

	TermsBSTNode* getRoot();
	void setRoot(TermsBSTNode* root);

	// insert
	void insert(TermsBSTNode* newNode);

	// print
	void print(TermsBSTNode* curNode, ofstream& flog);

	// delete
	bool del_Name(char* name, char* end_date);
	void del_Date(TermsBSTNode* curNode, char* end_date, NameBST* nameBST, TermsLIST* termsList);
};