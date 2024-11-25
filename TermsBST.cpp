#include "TermsBST.h"
#include "TermsList.h"

TermsBST::TermsBST() : root(nullptr)
{

}
TermsBST::~TermsBST()
{

}


TermsBSTNode* TermsBST::getRoot()
{
	return root;
}

void TermsBST::setRoot(TermsBSTNode* root)
{
	this->root=root;
}

// insert
void TermsBST::insert(TermsBSTNode* newNode)
{
	TermsBSTNode* pp=nullptr;
	TermsBSTNode* p=root;
	
	while(p)
	{
		pp=p;
	
		if(strcmp(newNode->getEndDate(), p->getEndDate())<0) //newNode end_date is smaller
		{
			p=p->getLeft();
		}
		else
		{
			p=p->getRight();
		}
	}

	p=newNode;

	if(root!=nullptr)
	{
		if(strcmp(p->getEndDate(), pp->getEndDate())<0) //newNode end_date is smaller
		{
			pp->setLeft(p); //set left child
		}
		else
		{
			pp->setRight(p); //set right child
		}
	}
	else //no node
	{
		root=p;
	}

}

// print
void TermsBST::print(TermsBSTNode* curNode, ofstream& flog)
{
	if(curNode!=nullptr)
	{
		print(curNode->getLeft(), flog); //left child visit
		flog<<curNode->getName()<<"/"<<curNode->getAge()<<"/"<<curNode->getCollectDate()<<"/"<<curNode->getEndDate()<<endl;
		print(curNode->getRight(), flog); //right child visit
	}	
}

// delete
bool TermsBST::del_Name(char* name, char* end_date)
{
	TermsBSTNode* p = root, *q=nullptr;

	//find same name and same end_date node
	while(p) //find node
	{

		if(strcmp(name,p->getName())==0 && strcmp(end_date, p->getEndDate())==0)
		{
			break;
		}

		q=p;
		
		if(strcmp(end_date,p->getEndDate())<0) //end_date is smaller
		{
			p=p->getLeft();
		}
		else //end_date is greater
		{
			p=p->getRight();
		}
	}

	if(p==0) //search fail
	{
		return false;
	}

	if(p->getLeft()==nullptr && p->getRight()==nullptr) //p is leaf node
	{
		if(q==0) //one node tree
		{
			root=nullptr;
		}
		else if(q->getLeft()==p)
		{
			q->setLeft(nullptr); //delete
		}
		else
		{
			q->setRight(nullptr); //delete
		}

		delete p; //delete node
		return true;
	}

	if(p->getLeft()==nullptr) //p has only right child
	{
		if(q==0)
		{
			root=p->getRight(); //delete
		}
		else if(q->getLeft()==p)
		{
			q->setLeft(p->getRight()); //delete
		}
		else
		{
			q->setRight(p->getRight()); //delete
		}

		delete p; //delete node
		return true;
	}

	if(p->getRight()==nullptr) //p has only left child
	{
		if(q==0)
		{
			root=p->getLeft(); //delete
		}
		else if(q->getLeft()==p)
		{
			q->setLeft(p->getLeft()); //delete
		}
		else
		{
			q->setRight(p->getLeft()); //delete
		}

		delete p; //delete node
		return true;
	}

	//p has left and right child
	TermsBSTNode *prevprev=p, *prev=p->getRight(), *curr=(p->getRight())->getLeft();

	//find smallest node in right subtree
	while(curr)
	{
		prevprev=prev;
		prev=curr;
		curr=curr->getLeft();
	}

	p->setName(prev->getName());
	p->setAge(prev->getAge());
	p->setCollectDate(prev->getCollectDate());
	p->setEndDate(prev->getEndDate());

	if(prevprev==p)
	{
		prevprev->setRight(prev->getRight());		
	}
	else
	{
		prevprev->setLeft(prev->getRight());
	}

	delete prev;
	return true;
}

void TermsBST::del_Date(TermsBSTNode* curNode, char* end_date, NameBST* nameBST, TermsLIST* termsList)
{
	if(curNode!=nullptr)
	{
		del_Date(curNode->getLeft(), end_date, nameBST, termsList); //left child visit
		del_Date(curNode->getRight(), end_date, nameBST, termsList); //right child visit
		if(strcmp(curNode->getEndDate(),end_date)<0)
		{
			NameBSTNode* findNode = nameBST->search(nameBST->getRoot(), curNode->getName());

			termsList->del_List(findNode->getType()); //count down in TermsLIST
			nameBST->del_Name(curNode->getName()); //delete node in NameBST

			if(curNode->getLeft()==nullptr && curNode->getRight()==nullptr) //delete node in TermsBST
			{
				del_Name(curNode->getName(), curNode->getEndDate());
			}
			else
			{
				del_Name(curNode->getName(), curNode->getEndDate());
			}
		}
	}
}
