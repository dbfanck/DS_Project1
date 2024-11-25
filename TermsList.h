#pragma once
#include "MemberQueueNode.h"
#include "TermsListNode.h"

class TermsLIST
{
private:
	TermsListNode* head;

public:
	TermsLIST();
	~TermsLIST();

	TermsListNode* getHead();

	// insert
	void insert(MemberQueueNode* popNode);

	// search
	TermsListNode* search(char type);

	// delete
	void del_List(char type);

};
