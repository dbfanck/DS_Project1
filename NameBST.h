#pragma once
#include "MemberQueueNode.h"
#include "NameBSTNode.h"
#include <fstream>

class NameBST
{
private:
	NameBSTNode* root;

public:
	NameBST();
	~NameBST();

	NameBSTNode* getRoot();

	// insert
	void insert(MemberQueueNode* popNode);
	
	// search
	NameBSTNode* search(NameBSTNode* curNode, char* key_name);

	// print
	void print(NameBSTNode* curNode, ofstream& flog);

	// delete
	bool del_Name(char* del_name);
};