#pragma once
#include "TermsBST.h"

class TermsListNode
{
private:

	char type;
	int cnt;
	TermsListNode*	next;
	TermsBST* BSTptr;

public:
	TermsListNode()
	{
		cnt=0;
		next=nullptr;
	}
	~TermsListNode() {}

	char getType() { return type; }
	int getCnt() { return cnt; }
	TermsListNode*	getNext()		 { return next; }
	TermsBST* getBSTptr() { return BSTptr; }

	void setType(char type) { this->type=type; }
	void setNext(TermsListNode* next)	 { this->next = next; }
	void setBSTptr(TermsBST* BSTptr) { this->BSTptr=BSTptr; }

	void cntUp(void) { cnt++; }
	void cntDown(void) { cnt--; }
};