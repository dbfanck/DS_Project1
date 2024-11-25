#include <iostream>
#include "MemberQueueNode.h"
#include "TermsList.h"
#include "TermsBST.h"

using namespace std;

TermsLIST::TermsLIST(): head(nullptr)
{

}
TermsLIST::~TermsLIST()
{

}

TermsListNode* TermsLIST::getHead()
{
	return head;
}

// insert
void TermsLIST::insert(MemberQueueNode* popNode)
{
	if(head==nullptr) //no node
	{
		TermsListNode* newListNode = new TermsListNode; //make node
		newListNode->setType(popNode->getType()); //set type
		newListNode->cntUp(); //count up
		head=newListNode; //head

		TermsBSTNode* newBSTNode = new TermsBSTNode(popNode); //make node
		TermsBST* newBST = new TermsBST;
		newBST->insert(newBSTNode); //make BST
		newListNode->setBSTptr(newBST);

		return;
	}

	TermsListNode* curNode=head;

	while(curNode)
	{
		if(curNode->getType()==popNode->getType()) //exist node
		{
			break;
		}
		curNode=curNode->getNext();
	}

	if(curNode!=nullptr) //exist
	{
		curNode->cntUp(); //count up

		TermsBSTNode* newBSTNode = new TermsBSTNode(popNode); //make BST node
		TermsBST* BSTptr=curNode->getBSTptr();
		BSTptr->insert(newBSTNode); //insert node
	}
	else
	{
		TermsListNode* newListNode= new TermsListNode; //make List node
		newListNode->setType(popNode->getType()); //set type
		newListNode->cntUp(); //count up

		curNode=head;
		while(curNode->getNext())
		{
			curNode=curNode->getNext();
		}

		curNode->setNext(newListNode);

		TermsBSTNode* newBSTNode = new TermsBSTNode(popNode); //make BST node
		TermsBST* newBST = new TermsBST;
		newBST->insert(newBSTNode); //make BST
		newListNode->setBSTptr(newBST);
	}

}

// search
TermsListNode* TermsLIST::search(char type)
{
	TermsListNode* curNode = head;
	
	while(curNode)
	{
		if(curNode->getType()==type)
		{
			break;
		}

		curNode=curNode->getNext();
	}

	return curNode;
}

// delete
void TermsLIST::del_List(char type)
{
	TermsListNode* prevNode = nullptr, *curNode = head;

	while(curNode)
	{
		if(curNode->getType()==type)
		{
			break;
		}

		prevNode=curNode;
		curNode=curNode->getNext();
	}

	curNode->cntDown(); //count down

	if(curNode->getCnt()==0) //count is zero
	{
		if(curNode==head)
		{
			head=curNode->getNext();
		}
		else
		{
			prevNode->setNext(curNode->getNext());
		}
	}
}
